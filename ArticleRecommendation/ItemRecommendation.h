#pragma once
//implement by Fan Kang-Jing

#include "stdafx.h"
#include "User.h"
#include "Article.h"


class ItemRecommendSolution
{
public:
	vector<User*> m_userList;
	vector<Article*> m_articleList;
	vector<vector<double>> ItemSimMatrix; //store the item similarity
	vector<vector<int>> m_answer;

public:
	ItemRecommendSolution(vector<User*>& userList, vector<Article*>& articleList);     //get UserList And ArticleList
	~ItemRecommendSolution(){}

	void getItemSimilarity();			//calculate the similarity between items
	void getSolution();

	void loadAnswerFromFile(string fileName);
	void getInItemSim();
};