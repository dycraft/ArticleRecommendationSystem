#include "User.h"

User::User():
	id(0)
{
}

User::User(int id):
	id(id)
{
}


User::~User()
{
}

void User::addPastArticle(int id_a)
{
	pastArticleList.push_back(id_a);
}

void User::addAlternative(int id_a)
{
	alternativeList.push_back(WeightArticle(id_a));
}

void User::showUser()
{
	cout << "UserId: " << id << "\n";

	int n = pastArticleList.size();
	cout << "PastArticle:" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << pastArticleList[i] << ',';
	}
	cout << endl;

	int m = alternativeList.size();
	cout << "AlternativeArticle:" << endl;
	for (int i = 0; i < m; i++)
	{
		cout << alternativeList[i].id << ',';
	}
	cout << endl;
}

/*int cmp_WeightArticle(const void * a, const void * b)
{
	return (*(WeightArticle *)b).weight - (*(WeightArticle *)a).weight;
}*/
