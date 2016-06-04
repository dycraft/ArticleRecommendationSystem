#include"BPNN_Recommendation.h"

double x = 0.3, y = 0.4, z = 0.3;
double change = 0.01;      
double accuracy = 0.8;
double accuracyCurr = 0.0;

BPNN_Recommendation::BPNN_Recommendation(vector<User*>& userList, vector<Article*>& articleList)
{
	m_userList = userList;
	m_articleList = articleList;
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
bool copare(const WeightArticle& first,const WeightArticle& second)
{                                                 
	return first.weight[FINAL] > second.weight[FINAL];
}

void BPNN_Recommendation::trainingx(double& x)
{
	vector<int> answer;

	while(accuracyCurr < accuracy)
	{
		int k = 0;
		for(k = 0; k < m_userList[0]->alternativeList.size(); k++)
		{
			m_userList[0]->alternativeList[k].weight[FINAL] = x * m_userList[0]->alternativeList[k].weight[SOCIAL] +
				y * m_userList[0]->alternativeList[k].weight[PERSONAL] + z * m_userList[k]->alternativeList[k].weight[ITEM];
		}

		sort(m_userList[0]->alternativeList.begin(), m_userList[0]->alternativeList.end(), copare);

		int commom = 0;
		for(k = 0; k < TOP_N; k++)              //TOP_N 5
		{
			for(int i = 0; i < answer.size(); i++)
			{
				if(m_userList[0]->alternativeList[k].id == answer[i])
					commom++;
			}
		}

		accuracyCurr = commom / TOP_N;
		
	}
}

void BPNN_Recommendation::trainingy(double& y)
{
	vector<int> answer;
}

void BPNN_Recommendation::training()
{

}
      