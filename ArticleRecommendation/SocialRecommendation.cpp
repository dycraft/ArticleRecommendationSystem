#include "SocialRecommendation.h"

////extern function////
vector<WeightArticle> getTopN_S(vector<WeightArticle>& base, ALGO mode, int top_n)
{
	vector<WeightArticle> v(top_n + 1); // + 1 to reserve a temp position
	
	int n = base.size();
	for (int i = 0; i < n; i++)
	{
		v[top_n] = base[i];
		int j = top_n;
		while ((j > 0) && (v[j-1].weight[mode] <= v[j].weight[mode]))
		{
			swap(v[j-1], v[j]);
			j--;
		}
	}

	v.erase(v.end()-1); // erase the temp
	return v;
}

void SocialRecommendSolution::loadAnswerFromFile(string fileName)
{
	ifstream inAn(fileName);
	if(inAn.fail())
	{
		cout << "ERROR: fail open answer.txt..." << endl;
		return;
	}

	vector<int> an;
	char p[10] = {0};
	int startPos = 0;

	while(!inAn.eof())
	{
		an.clear();
		string str("");
		getline(inAn, str);
		while(1 && str != "")
		{
			int pos = str.find('\t', startPos + 1);
			if(pos != string::npos)
			{
				if(startPos != 0)
				{
					str.copy(p, pos - startPos - 1, startPos + 1);
					string str1(p, pos - startPos - 1);
					an.push_back(atoi(str1.c_str()));
				}
				startPos = pos;
			}
			else
			{
				str.copy(p, str.length() - startPos - 1, startPos + 1);
				string str1(p, str.length() - startPos - 1);
				an.push_back(atoi(str1.c_str()));
				break;
			}

		}
		m_answer.push_back(an);
		startPos = 0;
	}
}

/*******************************************************************/
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
	double accu = 0.0;
	cout << "Begin to get social recommendation." << endl;

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
	
	/*
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
	*/

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
			if(userList[i]->alternativeList[j].weight[SOCIAL] > userList[i]->maxWeght[SOCIAL])
				userList[i]->maxWeght[SOCIAL] = userList[i]->alternativeList[j].weight[SOCIAL];
		}

		userList[i]->maxWeght[SOCIAL] = (userList[i]->maxWeght[SOCIAL] == 0.0 ? 1.0 : userList[i]->maxWeght[SOCIAL]);
		
		//figure accuracy
		/*vector<WeightArticle> v = getTopN_S(userList[i]->alternativeList, SOCIAL, TOP_N);

		int commom = 0;
		for(int k = 0; k < m_answer[i].size(); k++)
		{
			for(int j = 0; j < m_answer[i].size(); j++)
			{
				if(v[k].id == m_answer[i][j])
					commom++;
			}
		}

		accu += (double)commom / m_answer[i].size();*/
	}

	/*accu /= userList.size();
	cout << "Socail recommendation accuracy: " << accu << endl;*/

	cout << "Social recommendation completed." << endl;
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
