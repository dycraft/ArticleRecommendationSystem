#pragma once

#include "stdafx.h"

class Article
{
public:
	int id;
	string title;
	string abstra;
	hash_map<string, double> keyWords;
	int keyRepeatMax;

public:
	Article();
	Article(int id);
	~Article();

	//debug method
	void showArticle();
};

