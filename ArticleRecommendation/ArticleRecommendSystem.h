#pragma once

#include "stdafx.h"
#include "User.h"
#include "Article.h"

class ArticleRecommendSystem
{
public:
	vector<User*> userList;
	vector<Article*> articleList;

public:
	ArticleRecommendSystem();
	~ArticleRecommendSystem();

	//File I/O
	bool loadUserTrainInfo(string dir);

	bool loadArticleInfo(string dir);

	////only can be invoked after loadUserTrainInfo()
	bool loadAlternativeInfo(string dir);

	//recommendation Algorithms
	void getPersonalizedRecommendation();
	void getSocialRecommendation();
	void getItemRecommendation();

	//debug test method
	void showUserList();
	void showArticleList();
};

/*
1. Personalized recommendation: recommend things based on the indi-
vidual's past behavior
2. Social recommendation: recommend things based on the past behavior
of similar users
3. Item recommendation: recommend things based on the item itself
*/
