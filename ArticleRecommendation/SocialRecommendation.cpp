#include "SocialRecommendation.h"

SocialRecommendSolution::SocialRecommendSolution(vector<User*>& _userList, int _articleNum) :
	userNum(_userList.size()),
	articleNum(_articleNum)
{
	userList = _userList;

	userSimMatrix.resize(userNum + 1);
	for (int i = 0; i < userNum + 1; i++)
	{
		userSimMatrix[i].resize(userNum + 1, 0.0);
	}
}


SocialRecommendSolution::~SocialRecommendSolution()
{
}

void SocialRecommendSolution::getSolution()
{
	//make a item-user inverse table
	vector<list<int>> inverseTable(articleNum + 1);

	int n = userList.size();
	for (int i = 0; i < n; i++)
	{
		int m = userList[i]->pastArticleList.size();
		for (int j = 0; j < m; j++)
		{
			inverseTable[userList[i]->pastArticleList[j]].push_back(userList[i]->id);
		}
	}

	//utilize inversion to count cap between two users
	for (int i = 0; i < userNum; i++)
	{
		list<int>::iterator it1 = inverseTable[i].begin();
		while (it1 != inverseTable[i].end())
		{
			list<int>::iterator it2 = it1;
			it2++;
			while (it2 != inverseTable[i].end())
			{
				userSimMatrix[*it1][*it2]++;
				userSimMatrix[*it2][*it1]++;
				it2++;
			}
			it1++;
		}
	}
	
	//standardiztion
	for (int i = 0; i < userNum; i++)
	{
		int len1 = userList[i]->pastArticleList.size();
		for (int j = 0; j < i; j++)
		{
			int len2 = userList[j]->pastArticleList.size();
			userSimMatrix[userList[i]->id][userList[j]->id] /= sqrt(len1*len2);
			userSimMatrix[userList[j]->id][userList[i]->id] = userSimMatrix[userList[i]->id][userList[j]->id];
		}
	}

	//get recommendation weight
	for (int i = 0; i < userNum; i++)
	{
		vector<double> ItemWeight(articleNum+1, 0.0); //article'id begin with 1 not 0
		for (int j = 0; j < userNum; j++)
		{
			int n = userList[j]->pastArticleList.size();
			for (int k = 0; k < n; k++)
			{
				ItemWeight[userList[j]->pastArticleList[k]] += userSimMatrix[userList[i]->id][userList[j]->id];
			}
		}

		int n = userList[i]->alternativeList.size();
		for (int j = 0; j < n; j++)
		{
			userList[i]->alternativeList[j].weight[SOCIAL] = ItemWeight[userList[i]->alternativeList[j].id];
		}
	}
}

double getUserSimilarity(User * a, User * b)
{
	int len1 = a->pastArticleList.size();
	int len2 = b->pastArticleList.size();
	int n = len1 * len2;
	int m = 0;

	for (int i = 0; i < len1; i++)
	{
		for (int j = 0; j < len2; j++)
		{
			if (a->pastArticleList[i] == b->pastArticleList[j])
			{
				m++;
				break;
			}
		}
	}

	return (m*1.0) / sqrt(n);
}
