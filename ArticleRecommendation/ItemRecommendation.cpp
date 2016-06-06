#include "ItemRecommendation.h"
#define   Endline   16980
#define   Startline   16971

////extern function////
vector<WeightArticle> getTopN_I(vector<WeightArticle>& base, ALGO mode, int top_n)
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

void ItemRecommendSolution::loadAnswerFromFile(string fileName)
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

ItemRecommendSolution::ItemRecommendSolution(vector<User*>& userList, vector<Article*>& articleList)
{
	m_userList = userList;
	m_articleList = articleList;
}

void ItemRecommendSolution::getSolution()
{
	double accu = 0.0;
	cout<<"Begin to get item recommendation"<<endl;
	
	for(int i = 0; i < m_userList.size(); i++)
	{
		for(int k = 0; k < m_userList[i]->alternativeList.size(); k++) //alte
		{
			for(int o = 0; o < m_userList[i]->pastArticleList.size(); o++) //past
			{
				m_userList[i]->alternativeList[k].weight[ITEM] += 
					ItemSimMatrix[m_userList[i]->alternativeList[k].id - 1][m_userList[i]->pastArticleList[o] - 1];
			}

			if(m_userList[i]->alternativeList[k].weight[ITEM] > m_userList[i]->maxWeght[ITEM])
					m_userList[i]->maxWeght[ITEM] = m_userList[i]->alternativeList[k].weight[ITEM];
		}
		m_userList[i]->maxWeght[ITEM] = (m_userList[i]->maxWeght[ITEM] == 0.0 ? 1.0 : m_userList[i]->maxWeght[ITEM]);

		//figure accuracy
		/*vector<WeightArticle> v = getTopN_I(m_userList[i]->alternativeList, ITEM, TOP_N);

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

	/*accu /= m_userList.size();
	cout << "Item recommendation accuracy: " << accu << endl;*/

	cout << "Item recommendation completed." << endl;
}


void ItemRecommendSolution::getItemSimilarity()
{
	cout << "begin to put item similarity into file simItem.txt" << endl;
	ofstream ou("simItem.txt", ios::app);
	if(ou.fail())
	{
		cout << "ERROR: fail to open simItem.txt..." << endl;
		return;
	}
	vector<int> sameLike;
	double weight = 0.0;
	for(int i = Startline; i < m_articleList.size(); i++)
	{
		for(int k = i + 1; k < m_articleList.size(); k++)
		{
			sameLike.clear();
			weight = 0.0;
			
			//same
			for(int m = 0; m < m_articleList[k]->users.size(); m++)
			{
				for(int n = 0; n < m_articleList[i]->users.size(); n++)
				{
					if(m_articleList[k]->users[m] == m_articleList[i]->users[n])
						sameLike.push_back(m_articleList[k]->users[m]);
				}
			}

			//weight
			if(sameLike.size() != 0)
			{
				for(int l = 0; l < sameLike.size(); l++)
					weight += 1 / log(1 + m_userList[sameLike[l] - 1]->pastArticleList.size());
				weight /= sqrt((double)m_articleList[i]->users.size() * m_articleList[k]->users.size());
				ou << i + 1 << " " << k + 1 << " " << weight << "\n";
			}
		}
		if(i == Endline)
			break;
	}

	ou.close();
	cout << "got item similarity" << endl;
}

void ItemRecommendSolution::getInItemSim()
{
	//initial
	int articleNum = m_articleList.size();
	ItemSimMatrix.resize(articleNum + 1);
	for (int i = 0; i < articleNum + 1; i++)
	{
		ItemSimMatrix[i].resize(articleNum + 1, 0.0);
	}

	//getInput
	ifstream in("simItem.txt");
	if(in.fail())
	{
		cout << "ERROR: fail to open simItem.txt..." << endl;
		return;
	}

	string str("");
	int fi = 0, se = 0;
	
	while(!in.eof())
	{
		getline(in, str, ' ');
		fi = atoi(str.c_str());
		str = "";
		getline(in, str, ' ');
		se = atoi(str.c_str());
		str = "";
		getline(in, str, '\n');
		ItemSimMatrix[fi - 1][se - 1] = atof(str.c_str());
	}
	/*
	for(int k = 0; k < 1; k++)
		for(int i = 0; i < ItemSimMatrix[k].size(); i++)
		{
			if(ItemSimMatrix[k][i] != 0.0)
				cout << ItemSimMatrix[k][i] << " ";
		}
		*/
}