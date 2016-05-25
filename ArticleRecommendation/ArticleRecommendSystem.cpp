#include "ArticleRecommendSystem.h"



ArticleRecommendSystem::ArticleRecommendSystem()
{
}


ArticleRecommendSystem::~ArticleRecommendSystem()
{
}

bool ArticleRecommendSystem::loadUserTrainInfo(string dir)
{
	//file i/o by C
	FILE *file;
	file = fopen(dir.c_str(), "r");

	if (file == NULL)
	{
		cout << "load " << dir << "failed." << endl;
		return false;
	}

	int id_count = 0;
	User *p_user;
	while (!feof(file))
	{
		int id_s, article_s;
		fscanf(file, "%d,%d", &id_s, &article_s); //todo

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

	fclose(file);
	return true;
}

bool ArticleRecommendSystem::loadArticleInfo(string dir)
{
	//file i/o by C
	FILE *file;
	file = fopen(dir.c_str(), "r");

	if (file == NULL)
	{
		cout << "load " << dir << "failed." << endl;
		return false;
	}

	int id_count = 0;
	Article *p_article;
	while (!feof(file))
	{
		int id_s;
		char title_s[1000], abstract_s[1000];
		fscanf(file, "%d,\"%s\",\"%s\"", &id_s, &title_s, &abstract_s); //todo

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
	}

	fclose(file);
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
