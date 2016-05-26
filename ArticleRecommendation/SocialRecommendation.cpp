#include "SocialRecommendation.h"

UserSimilaritySolution::UserSimilaritySolution(vector<User*>& _userList, int _articleNum) :
	userNum(userList.size()),
	articleNum(_articleNum)
{
	userList = _userList;

	userSimMatrix.resize(userNum + 1);
	for (int i = 0; i < userNum; i++)
	{
		userSimMatrix[i].resize(userNum + 1, 0.0);
	}
}


UserSimilaritySolution::~UserSimilaritySolution()
{
}

void UserSimilaritySolution::getSolution()
{
	//make a item-user inverse table
	vector<list<int>> inverseTable(articleNum);

	int n = userList.size();
	for (int i = 0; i < n; i++)
	{
		int m = userList[i]->pastArticleList.size();
		for (int j = 0; j < m; j++)
		{
			inverseTable[userList[i]->pastArticleList[j]].push_back(userList[i]->id);
		}
	}

	//todo
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
