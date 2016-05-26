#pragma once

#include "stdafx.h"
#include "User.h"
// only based on user

#define TOP_USER_N 10

class UserSimilaritySolution
{
private:
	int userNum;
	int articleNum;
	vector<User*> userList;

	vector<vector<double>> userSimMatrix;

public:
	UserSimilaritySolution(vector<User*>& userList, int articleNum);
	~UserSimilaritySolution();

	void getSolution();
};

extern double getUserSimilarity(const User *a, const User *b);
