#include "ArticleRecommendSystem.h"
#include "ItemRecommendation.h"
#include "PersonalizedRecommendation.h"
#include "SocialRecommendation.h"

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
		cout << "Load " << dir << " failed." << endl;
		return false;
	}
	
	int id_count = 0;
	User *p_user;
	while (!file.eof())
	{
		int id_s, article_s;
		string temp; //temp string for convert to int

		//split each line by getline() in the file
		getline(file, temp, ',');
		id_s = stoi(temp);
		getline(file, temp);
		article_s = stoi(temp);

		//compare new with old to decide if get next user
		if (id_s != id_count)
		{
			id_count = id_s;
			p_user = new User(id_count);
			userList.push_back(p_user);
			p_user->addPastArticle(article_s);
		}
		else
		{
			p_user->addPastArticle(article_s);
		}
	}

	file.close();
	cout << "Load " << dir << " succesfully." << endl;
	return true;
}

bool ArticleRecommendSystem::loadArticleInfo(string dir)
{
	ifstream file(dir);

	if (!file.is_open())
	{
		cout << "Load " << dir << " failed." << endl;
		return false;
	}

	int id_count = 0;
	Article *p_article;
	while (!file.eof())
	{
		int id_s;
		string title_s, abstract_s;
		string temp; //temp string for convert to int

		getline(file, temp, '"');
		id_s = stoi(temp);
		getline(file, title_s, '"');
		getline(file, temp, '"'); //to skip useless char
		getline(file, abstract_s);
		abstract_s.erase(abstract_s.end()-1);//to get the last string in a safer way

		if (id_s != id_count)
		{
			id_count = id_s;
			p_article = new Article(id_count);
			articleList.push_back(p_article);
			p_article->title = title_s;
			p_article->abstra = abstract_s;
		}
		else
		{
			p_article->title = title_s;
			p_article->abstra = abstract_s;
		}
	}
	
	file.close();
	cout << "Load " << dir << " succesfully." << endl;
	return true;
}

bool ArticleRecommendSystem::loadAlternativeInfo(string dir)
{
	ifstream file(dir);

	if (!file.is_open())
	{
		cout << "Load " << dir << " failed." << endl;
		return false;
	}
	
	while (!file.eof())
	{
		int id_s, article_s;
		string temp; //temp string for convert to int

		//split each line by getline() in the file
		getline(file, temp, ',');
		id_s = stoi(temp);
		getline(file, temp);
		article_s = stoi(temp);

		userList[id_s-1]->addAlternative(article_s);
	}

	file.close();
	cout << "Load " << dir << " succesfully." << endl;
	return true;
}

bool ArticleRecommendSystem::writeRecommendInfo(string dir, ALGO mode)
{
	ofstream file(dir);

	if (!file.is_open())
	{
		cout << "load " << dir << " failed." << endl;
		return false;
	}

	//getSocialRecommendation();

	int n = userList.size();
	for (int i = 0; i < n; i++)
	{
		vector<WeightArticle> v = getTopN(userList[i]->alternativeList, mode, TOP_N);
		file << userList[i]->id;
		for (int j = 0; j < TOP_N; j++)
		{
			if (j == 0)
			{
				file << ',';
			}
			else
			{
				file << ';';
			}
			file << v[j].id;
		}
		file << '\n';
	}

	file.close();
	cout << "Write " << dir << " succesfully." << endl;
	return true;
}

bool ArticleRecommendSystem::generateRandomTrainInfo(string trainDir,
	string testDir, string ansDir, const int RECNUM, const int ALTERNUM)
{
	//in(train) and out(answer) are both OutStream
	ofstream trainStream(trainDir), testStream(testDir), answerStream(ansDir);

	if (!trainStream.is_open())
	{
		cout << "load " << trainDir << " failed." << endl;
		return false;
	}
	if (!testStream.is_open())
	{
		cout << "load " << testDir << " failed." << endl;
		return false;
	}
	if (!answerStream.is_open())
	{
		cout << "load " << ansDir << " failed." << endl;
		return false;
	}

	srand((unsigned int)time(NULL));

	int n = userList.size();
	for (int i = 0; i < n; i++)
	{
		//copy past article list
		vector<int> list = userList[i]->pastArticleList;
		vector<int> vec;
		vec.assign(list.begin(), list.end());

		//swap randomly to generate a random list
		int m = vec.size();
		for (int j = 0; j < m; j++)
		{
			int pos = rand() % m;
			if (j != pos)
			{
				swap(vec[j], vec[pos]);
			}
		}

		//divide into two parts: train(0~RECNUM-1) and answer(RECNUM~size)
		////answer
		answerStream << userList[i]->id;
		for (int j = 0; j < RECNUM; j++)
		{
			answerStream << '\t' << vec[j];
		}
		answerStream << '\n';

		////train
		for (int j = RECNUM; j < m; j++)
		{
			trainStream << userList[i]->id << ',' << vec[j] << '\n';
		}

		////test
		unordered_set<int> s;
		for (int j = 0; j < RECNUM; j++)
		{
			s.insert(vec[j]);
		}
		//const int articleNum = articleList.size();
		const int articleNum = ARTICLE_NUM;
		while(s.size() <= ALTERNUM)
		{
			s.insert((rand() % articleNum) + 1); //because article's id begin with 1
		}
		for (unordered_set<int>::iterator it = s.begin(); it != s.end(); it++)
		{
			testStream << userList[i]->id << ',' << *it << '\n';
		}
	}
	
	trainStream.close();
	testStream.close();
	answerStream.close();
	return true;
}

void ArticleRecommendSystem::getPersonalizedRecommendation()
{
	PersonalRecommendSolution *p = new PersonalRecommendSolution(userList, articleList);
	p->readKeyWordFromFile("IF_IDF.txt");
	p->recommendArticle();
}

void ArticleRecommendSystem::getSocialRecommendation()
{
	//SocialRecommendSolution *s = new SocialRecommendSolution(userList, articleList.size());
	SocialRecommendSolution *s = new SocialRecommendSolution(userList, 16980);
	s->getSolution();
}

void ArticleRecommendSystem::getItemRecommendation()
{
}

void ArticleRecommendSystem::showUserList()
{
	int n = userList.size();
	for (int i = 0; i < n; i++)
	{
		userList[i]->showUser();
		cout << endl;
	}
}

void ArticleRecommendSystem::showArticleList()
{
	int n = articleList.size();
	for (int i = 0; i < n; i++)
	{
		articleList[i]->showArticle();
		cout << endl;
	}
}

////extern function////

vector<WeightArticle> getTopN(vector<WeightArticle>& base, ALGO mode, int top_n)
{
	vector<WeightArticle> v(top_n + 1); // + 1 to reserve a temp position
	
	int n = base.size();
	for (int i = 0; i < n; i++)
	{
		v[top_n] = base[i];
		int j = top_n;
		while ((j > 0) && (v[j-1].weight[mode] < v[j].weight[mode]))
		{
			swap(v[j-1], v[j]);
			j--;
		}
	}

	v.erase(v.end()-1); // erase the temp
	return v;
}
