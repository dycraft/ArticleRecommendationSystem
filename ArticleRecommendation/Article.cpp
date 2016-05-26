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

void Article::showArticle()
{
	cout << "ArticleId: " << id << "\n";
	cout << "Title:\n" << title << "\n";
	cout << "Abstract:\n" << abstra << "\n";
}
