#pragma once
//implement by Li Da-Yang

#include "stdafx.h"
#include "User.h"
// only based on user

#define TOP_USER_N 10

class SocialRecommendSolution
{
private:
	const int userNum;
	const int articleNum;

	vector<User*> userList; //a reference of param:userList
	vector<vector<double>> userSimMatrix; //store the user similarity
	vector<vector<int>> m_answer;

public:
	SocialRecommendSolution(vector<User*>& userList, int articleNum);
	~SocialRecommendSolution();

	void loadAnswerFromFile(string fileName);
	void getSolution();
};

extern double getUserSimilarity(const User *a, const User *b);
