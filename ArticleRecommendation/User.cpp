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

int User::getUserId()
{
	return id;
}

int User::getArticleNum()
{
	return pastArticleList.size();
}

void User::setUserId(int id_new)
{
	id = id_new;
}

void User::addPastArticle(int id_a)
{
	pastArticleList.push_back(id_a);
}

void User::addAlternative(int id_a)
{
	alternativeList.push_back(id_a);
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
		cout << alternativeList[i] << ',';
	}
	cout << endl;
}
