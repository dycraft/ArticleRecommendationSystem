#include "ArticleRecommendSystem.h"



ArticleRecommendSystem::ArticleRecommendSystem()
{
}


ArticleRecommendSystem::~ArticleRecommendSystem()
{
}

bool ArticleRecommendSystem::loadUserTrainInfo(string dir)
{
	ifstream file(dir);
	
	if (!file.is_open())
	{
		cout << "load " << dir << "failed." << endl;
		return false;
	}
	
	int id_count = 0;
	while (!file.eof())
	{
		User *p_user;

		int id_s, article_s;
		string line;
		getline(file, line);
		//stringstream line_stream;
		//line_stream.str(line);
		fscanf(file, "%d,%d", &id_s, &article_s);

		line_stream >> id_s >> article_s;

		if (id_s != id_count)
		{
			id_count = id_s;
			p_user = new User(id_count);
			userlist.push_back(p_user);
			p_user->addArticle(article_s);
		}
		else
		{
			p_user->addArticle(article_s);
		}
	}
	
	file.close();
	return true;
}

bool ArticleRecommendSystem::loadArticalInfo(string dir)
{
	fstream file(dir, 'r');

	if (!file.is_open())
	{
		cout << "load " << dir << "failed." << endl;
		return false;
	}

	

	file.close();
	return true;
}

void ArticleRecommendSystem::showUserList()
{
	int n = userlist.size();
	for (int i = 0; i < n; i++)
	{
		userlist[i]->showUser();
	}
}
