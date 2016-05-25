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
	return articlelist.size();
}

void User::setUserId(int id_new)
{
	id = id_new;
}

void User::addArticle(int id_a)
{
	articlelist.push_back(id_a);
}

void User::showUser()
{
	cout << "UserId: " << id << "\n";

	int n = articlelist.size();
	for (int j = 0; j < n; j++)
	{
		cout << "|- " << articlelist[j] << "\n";
	}
	cout << endl;
}
