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
			userlist.push_back(p_user);
			p_user->addArticle(article_s);
		}
		else
		{
			p_user->addArticle(article_s);
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
			articlelist.push_back(p_article);
			p_article->setArticleTitle(title_s);
			p_article->setArticleAbstract(abstract_s);
		}
		else
		{
			p_article->setArticleTitle(title_s);
			p_article->setArticleAbstract(abstract_s);
		}
		cout << id_count << endl;
	}

	file.close();
	return true;
}

void ArticleRecommendSystem::showUserList()
{
	int n = userlist.size();
	for (int i = 0; i < n; i++)
	{
		userlist[i]->showUser();
	}
}

void ArticleRecommendSystem::showArticleList()
{
	int n = articlelist.size();
	for (int i = 0; i < n; i++)
	{
		articlelist[i]->showArticle();
		cout << endl;
	}
}
