#include "Article.h"



Article::Article():
	id(0)
{
}

Article::Article(int id):
	id(id)
{
}


Article::~Article()
{
}

int Article::getArticleId()
{
	return id;
}

string Article::getArticleTitle()
{
	return title;
}

string Article::getArticleAbstract()
{
	return abstra;
}

void Article::setArticleId(int id_new)
{
	id = id_new;
}

void Article::setArticleTitle(string title_new)
{
	title = title_new;
}

void Article::setArticleAbstract(string abstract_new)
{
	abstra = abstract_new;
}

void Article::showArticle()
{
	cout << "ArticleId: " << id << "\n";
	cout << "Title: " << title << "\n";
	cout << "Abstract: " << abstra << "\n";
}
