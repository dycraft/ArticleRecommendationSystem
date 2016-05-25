#pragma once

#include "stdafx.h"

class Article
{
private:
	int id;
	string title;
	string abstra;

public:
	Article();
	Article(int id);
	~Article();

	//access method
	int getArticleId();
	string getArticleTitle();
	string getArticleAbstract();

	//operator method
	void setArticleId(int id_new);
	void setArticleTitle(string title_new);
	void setArticleAbstract(string abstract_new);

	//debug method
	void showArticle();
};

