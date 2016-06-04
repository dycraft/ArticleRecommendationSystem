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

	bool writeRecommendInfo(string dir, ALGO mode = FINAL);

	////only can be invoked after loadUserTrainInfo()
	bool generateRandomTrainInfo(string trainDir, string testDir, string ansDir, const int RECNUM = 5, const int ALTERNUM = 251);

	//recommendation Algorithms
	void getPersonalizedRecommendation();
	void getSocialRecommendation();
	void getItemRecommendation();

	void getBPNNRecommendation();

	//debug test method
	void showUserList();
	void showArticleList();
};

extern vector<WeightArticle> getTopN(vector<WeightArticle> &base, ALGO mode = FINAL, int top_n = TOP_N);

//5551 - 16980

/*
1. Personalized recommendation: recommend things based on the indi-
vidual's past behavior
2. Social recommendation: recommend things based on the past behavior
of similar users
3. Item recommendation: recommend things based on the item itself
*/
