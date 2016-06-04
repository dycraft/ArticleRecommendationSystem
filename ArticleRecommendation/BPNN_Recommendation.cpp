#include"BPNN_Recommendation.h"

extern double x = 0.3, y = 0.4, z = 0.3;
extern double change = 0.01;      
extern double accuracy = 0.8;
extern double accuracyCurr = 0.0;

BPNN_Recommendation::BPNN_Recommendation(vector<User*>& userList, vector<Article*>& articleList)
{
	m_userList = userList;
	m_articleList = articleList;
	m_answer.clear();
}

void BPNN_Recommendation::loadAnswerFromFile(string fileName)
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
		while(1)
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
	}

}

void BPNN_Recommendation::makeChange(double& change, char mode)
{
	if(mode == '-')
		change = -change;
	else
		change = change;
}

void BPNN_Recommendation::changex(double& x)
{
	x += change;
}

void BPNN_Recommendation::changey(double& y)
{
	y += change;
}

//sort by weight
bool compare(const WeightArticle& first,const WeightArticle& second)
{                                                 
	return first.weight[FINAL] > second.weight[FINAL];
}

void BPNN_Recommendation::trainingx(double& x)
{
	while(accuracyCurr < accuracy)
	{
		int k = 0;
		for(int index = 0; index < m_userList.size(); index++)
		{
			for(k = 0; k < m_userList[index]->alternativeList.size(); k++)
			{
				m_userList[0]->alternativeList[k].weight[FINAL] = x * m_userList[0]->alternativeList[k].weight[SOCIAL] +
					y * m_userList[0]->alternativeList[k].weight[PERSONAL] + z * m_userList[k]->alternativeList[k].weight[ITEM];
			}

			sort(m_userList[index]->alternativeList.begin(), m_userList[index]->alternativeList.end(), compare);

			int commom = 0;
			for(k = 0; k < TOP_N; k++)              //TOP_N 5
			{
				for(int i = 0; i < m_answer[index].size(); i++)
				{
					if(m_userList[index]->alternativeList[k].id == m_answer[index][i])
						commom++;
				}
			}

			accuracyCurr += commom / TOP_N;
		}
		
		accuracyCurr = accuracyCurr / m_userList.size();
	}
}

void BPNN_Recommendation::trainingy(double& y)
{
	vector<int> answer;
}

void BPNN_Recommendation::training()
{

}

/************************************************************************
*Debug method
*************************************************************************/

void BPNN_Recommendation::showAnswer()
{
	for(int k = 0; k < m_answer.size(); k++)
	{
		for(int j = 0; j < m_answer[k].size(); j++)
			cout << m_answer[k][j] << " ";
		cout << endl;

		if(k == 3)
			break;
	}
}