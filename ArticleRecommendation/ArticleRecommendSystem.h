#pragma once

#include "stdafx.h"
#include "User.h"
#include "Article.h"

class ArticleRecommendSystem
{
private:
	vector<User*> userlist;
	vector<Article*> articlelist;

public:
	ArticleRecommendSystem();
	~ArticleRecommendSystem();

	bool loadUserTrainInfo(string dir);
	bool loadArticleInfo(string dir);

	//debug test method
	void showUserList();
	void showArticleList();
};

