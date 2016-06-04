#pragma once 

#include "stdafx.h"
#include "User.h"
#include "Article.h"

class BPNN_Recommendation
{
public:
	vector<User*> m_userList;
	vector<Article*> m_articleList;
	vector<double> m_x, m_y, m_z;             //mix percentage

public:
	BPNN_Recommendation(vector<User*>& userList, vector<Article*>& articleList); //get UserList And ArticleList
	~BPNN_Recommendation(){}

	void makeChange(double& change, char mode);
	void changex(double& x);
	void changey(double& y);

	void trainingx(double& x);
	void trainingy(double& y);
	void training();
};