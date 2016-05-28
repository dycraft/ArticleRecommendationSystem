#include "ArticleRecommendSystem.h"
#include "ItemRecommendation.h"
#include "PersonalizedRecommendation.h"
#include "SocialRecommendation.h"

ArticleRecommendSystem::ArticleRecommendSystem()
{
}


ArticleRecommendSystem::~ArticleRecommendSystem()
{
}

bool ArticleRecommendSystem::loadUserTrainInfo(string dir)
{
	ifstream file(dir);

	if (!file.is_open())
	{
		cout << "load " << dir << "failed." << endl;
		return false;
	}
	
	int id_count = 0;
	User *p_user;
	while (!file.eof())
	{
		int id_s, article_s;
		string temp; //temp string for convert to int

		//split each line by getline() in the file
		getline(file, temp, ',');
		id_s = stoi(temp);
		getline(file, temp);
		article_s = stoi(temp);

		//compare new with old to decide if get next user
		if (id_s != id_count)
		{
			id_count = id_s;
			p_user = new User(id_count);
			userList.push_back(p_user);
			p_user->addPastArticle(article_s);
		}
		else
		{
			p_user->addPastArticle(article_s);
		}
	}

	file.close();
	return true;
}

bool ArticleRecommendSystem::loadArticleInfo(string dir)
{
	ifstream file(dir);

	if (!file.is_open())
	{
		cout << "load " << dir << "failed." << endl;
		return false;
	}

	int id_count = 0;
	Article *p_article;
	while (!file.eof())
	{
		int id_s;
		string title_s, abstract_s;
		string temp; //temp string for convert to int

		getline(file, temp, '"');
		id_s = stoi(temp);
		getline(file, title_s, '"');
		getline(file, temp, '"'); //to skip useless char
		getline(file, abstract_s);
		abstract_s.erase(abstract_s.end()-1);//to get the last string in a safer way

		if (id_s != id_count)
		{
			id_count = id_s;
			p_article = new Article(id_count);
			articleList.push_back(p_article);
			p_article->title = title_s;
			p_article->abstra = abstract_s;
		}
		else
		{
			p_article->title = title_s;
			p_article->abstra = abstract_s;
		}
	}
	
	file.close();
	return true;
}

bool ArticleRecommendSystem::loadAlternativeInfo(string dir)
{
	ifstream file(dir);

	if (!file.is_open())
	{
		cout << "load " << dir << "failed." << endl;
		return false;
	}
	
	while (!file.eof())
	{
		int id_s, article_s;
		string temp; //temp string for convert to int

		//split each line by getline() in the file
		getline(file, temp, ',');
		id_s = stoi(temp);
		getline(file, temp);
		article_s = stoi(temp);

		userList[id_s-1]->addAlternative(article_s);
	}

	file.close();
	return true;
}

bool ArticleRecommendSystem::writeRecommendInfo(string dir)
{
	ofstream file(dir);

	if (!file.is_open())
	{
		cout << "load " << dir << "failed." << endl;
		return false;
	}

	//getSocialRecommendation();

	int n = userList.size();
	for (int i = 0; i < n; i++)
	{
		vector<WeightArticle> v = getTopN(userList[i]->alternativeList, TOP_N);
		file << userList[i]->id;
		for (int j = 0; j < TOP_N; j++)
		{
			if (j == 0)
			{
				file << ',';
			}
			else
			{
				file << ';';
			}
			file << v[j].id;
		}
		file << '\n';
	}

	file.close();
	return true;
}

void ArticleRecommendSystem::getPersonalizedRecommendation()
{
}

void ArticleRecommendSystem::getSocialRecommendation()
{
	//SocialRecommendSolution *s = new SocialRecommendSolution(userList, articleList.size());
	SocialRecommendSolution *s = new SocialRecommendSolution(userList, 16980);
	s->getSolution();
}

void ArticleRecommendSystem::getItemRecommendation()
{
}

void ArticleRecommendSystem::showUserList()
{
	int n = userList.size();
	for (int i = 0; i < n; i++)
	{
		userList[i]->showUser();
		cout << endl;
	}
}

void ArticleRecommendSystem::showArticleList()
{
	int n = articleList.size();
	for (int i = 0; i < n; i++)
	{
		articleList[i]->showArticle();
		cout << endl;
	}
}

////extern function////

vector<WeightArticle> getTopN(vector<WeightArticle>& base, int top_n)
{
	vector<WeightArticle> v(top_n + 1); // + 1 to reserve a temp position
	
	int n = base.size();
	for (int i = 0; i < n; i++)
	{
		v[top_n] = base[i];
		int j = top_n;
		while ((j > 0) && (v[j-1].weight < v[j].weight))
		{
			swap(v[j-1], v[j]);
			j--;
		}
	}

	v.erase(v.end()-1); // erase the temp
	return v;
}
