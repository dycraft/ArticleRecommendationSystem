#pragma once

#include "stdafx.h"

class Article
{
public:
	int id;
	string title;
	string abstra;

public:
	Article();
	Article(int id);
	~Article();

	//debug method
	void showArticle();
};

