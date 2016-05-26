#include "ArticleRecommendSystem.h"

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
			p_article->setArticleTitle(title_s);
			p_article->setArticleAbstract(abstract_s);
		}
		else
		{
			p_article->setArticleTitle(title_s);
			p_article->setArticleAbstract(abstract_s);
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
	int u = 0;
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

void ArticleRecommendSystem::getPersonalizedRecommendation()
{
}

void ArticleRecommendSystem::getSocialRecommendation()
{
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
