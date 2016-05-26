#pragma once

#include "stdafx.h"

class User
{
private:
	int id;
	vector<int> pastArticleList;
	vector<int> alternativeList;

public:
	User();
	User(int id);
	~User();

	//access method
	int getUserId();
	int getArticleNum();

	//operator method
	void setUserId(int id_new);
	void addPastArticle(int id_a);
	void addAlternative(int id_a);

	//debug method
	void showUser();
};

