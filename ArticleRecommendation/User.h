#pragma once

#include "stdafx.h"

class User
{
private:
	int id;
	vector<int> articlelist;

public:
	User();
	User(int id);
	~User();

	//access method
	int getUserId();
	int getArticleNum();

	//operator method
	void setUserId(int id_new);
	void addArticle(int id_a);

	//debug method
	void showUser();
};

