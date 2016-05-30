#include "PersonalizedRecommendation.h"
#define BeginPos 0
#define EndPos 17000
#define probleLine 6524  //English with Chinese

UserItermSimilarSolution::UserItermSimilarSolution(vector<User*>& userList, vector<Article*>& articleList)
{
	m_userList = userList;
	m_articleList = articleList;
	m_isInitial = true;

	//ReadIn stopWords
	m_stopWords = "";
	ifstream inFile("stopWords.txt");
	if(inFile.fail())
	{
		cout << "Error: fail open stopWords..." << endl;
		return;
	}

	while(!inFile.eof())
	{
		string str("");
		getline(inFile, str);
		m_stopWords += str;
	}
	inFile.close();
}

void UserItermSimilarSolution::KeyWordByIF_IDF()
{
	if(!m_isInitial)
	{
		cout << "(In UseItermSimilarSolution)Error: please initial first..." << endl;
		return;
	}

	//IF-IDF
	//first just add TF
	hash_map<string, double> kywd;
	for(int k = BeginPos; k < m_articleList.size(); k++)
	{
		if(k != probleLine - 1)
			continue;

		kywd.clear();
		m_articleList[k]->keyRepeatMax = 0;
		//title
		for(int i = 0; i < m_articleList[k]->title.size(); i++)
		{
			string keywd("");
			while(isalpha(m_articleList[k]->title[i]) && i < m_articleList[k]->title.size())
			{
				keywd += m_articleList[k]->title[i];
				i++;
			}

			//to lower
			transform(keywd.begin(), keywd.end(), keywd.begin(), tolower);

			//if already find
			if(kywd.find(keywd) != kywd.end())
			{
				kywd[keywd]++;
				m_articleList[k]->keyWords[keywd] = kywd[keywd];  //ensure TF >= 2
				if(kywd[keywd] > m_articleList[k]->keyRepeatMax)
					m_articleList[k]->keyRepeatMax = kywd[keywd];
				continue;
			}

			//is not stopWords and length > 3
			if(keywd.size() > 3  && keywd.size() < 30 && m_stopWords.find(keywd) == string::npos)
			{
				//add keyWord not figure yet 
				kywd[keywd] = 1.0;
			}
		}

		//abstract
		for(int i = 0; i < m_articleList[k]->abstra.size(); i++)
		{
			string keywd("");
			while(m_articleList[k]->abstra[i] < 255 && m_articleList[k]->abstra[i] > 0 && 
				isalpha(m_articleList[k]->abstra[i]) && i < m_articleList[k]->abstra.size())
			{
				keywd += m_articleList[k]->abstra[i];
				i++;
			}

			//to lower
			transform(keywd.begin(), keywd.end(), keywd.begin(), tolower);

			//if already find
			if(kywd.find(keywd) != kywd.end())
			{
				kywd[keywd]++;
				m_articleList[k]->keyWords[keywd] = kywd[keywd];  //ensure TF >= 2
				if(kywd[keywd] > m_articleList[k]->keyRepeatMax)
					m_articleList[k]->keyRepeatMax = kywd[keywd];
				continue;
			}

			//is not stopWords and length > 3
			if(keywd.size() > 3 && keywd.size() < 30 && m_stopWords.find(keywd) == string::npos)
			{
				//add keyWord not figure yet 
				kywd[keywd] = 1.0;
			}
		}	

		if(k == EndPos)
			break;
	}

	//next add IDF
	for(int k = BeginPos; k < m_articleList.size(); k++)
	{
		for(hash_map<string ,double>::iterator iter = m_articleList[k]->keyWords.begin(); iter != m_articleList[k]->keyWords.end(); iter++)
		{
			double df = 1.0;
			for(int i = 0; i < m_articleList.size(); i++)
			{
				if(i != k && (m_articleList[i]->title.find(iter->first) != string::npos || 
					m_articleList[i]->abstra.find(iter->first) != string::npos))
				{
					df++;
				}
			}

			iter->second = (iter->second / m_articleList[k]->keyRepeatMax) * log(m_articleList.size() / df);
		}

		if(k == EndPos)
			break;
	}

}

//string is num or not(first char is num) 
bool ismun(string strinfo)  
{    
	if(strinfo.empty())   
    {  
        return false;  
    }

	else if(strinfo[0] - '0' > 9 || strinfo[0] - '0' < 0)
	{
		return false;
	}
    return true;  
}  

void UserItermSimilarSolution::readKeyWordFromFile(string fileName)
{
	ifstream inFile(fileName);
	if(inFile.fail())
	{
		cout << "Error: fail open file IF_IDF..." << endl;
		return;
	}

	int id = -1;
	char p[50] = {0};
	while(!inFile.eof())
	{
		string str("");
		getline(inFile, str);
		if(ismun(str))
		{
			id = atoi(str.c_str());
		}
		else
		{
			int pos = str.find(' ');
			if(pos != string::npos)
			{
				str.copy(p, pos, 0);
				string str1(p, pos);
				str.copy(p, str.length() - 1 - pos, pos + 1);
				string str2(p, str.length() - 1 - pos);
				m_articleList[id - 1]->keyWords[str1] = atof(str2.c_str());
			}
		}
	}

	inFile.close();
}

//sort by weight
bool copare(const WeightArticle& first,const WeightArticle& second)
{                                                 
	return first.weight > second.weight;
}

void UserItermSimilarSolution::recommendArticle()
{
	for(int useIndex = 0; useIndex < m_userList.size(); useIndex++)
	{
		for(int k = 0; k < m_userList[useIndex]->alternativeList.size(); k++)  //alternative article
		{
			for(hash_map<string, double>::iterator iter = m_articleList[m_userList[useIndex]->alternativeList[k].id - 1]->keyWords.begin(); iter != m_articleList[m_userList[useIndex]->alternativeList[k].id - 1]->keyWords.end(); iter++) //key words
			{
				for(int i = 0; i < m_userList[useIndex]->pastArticleList.size(); i++)  //past article
				{
					hash_map<string, double>::iterator iter1 = m_articleList[m_userList[useIndex]->pastArticleList[i] - 1]->keyWords.find(iter->first);
					if(iter1 != m_articleList[m_userList[useIndex]->pastArticleList[i] - 1]->keyWords.end())
					{
						m_userList[useIndex]->alternativeList[k].weight += iter->second * iter1->second;
					}
				}
			}
		}
	}

	for(int useIndex = 0; useIndex < m_userList.size(); useIndex++)
	{
		//sort and print TOP_N
		sort(m_userList[useIndex]->alternativeList.begin(), m_userList[useIndex]->alternativeList.end(), copare);
		/*
		cout << "UseId: " << useIndex + 1 << " Top " << TOP_N << ": " << endl;
		for(int k = 0; k < TOP_N; k++)
		{
			cout << setprecision(9) << "id: " << m_userList[0]->alternativeList[k].id << " weight: " << m_userList[0]->alternativeList[k].weight << endl;
		}
		*/
	}
}


/**********************************************************************************************
*sava data in file for fast speed
***********************************************************************************************/
void UserItermSimilarSolution::SaveIF_IDF_ToFile()
{
	ofstream out("IF_IDF1.txt", ios::app);
	if(out.fail())
	{
		cout << "Error: fail to open IF_IDF.txt" << endl;
	}

	for(int k = BeginPos; k < m_articleList.size(); k++)
	{
		if(k != probleLine - 1)
			continue;

		out << m_articleList[k]->id << string("\n");
		for(hash_map<string, double>::iterator iter = m_articleList[k]->keyWords.begin(); iter != m_articleList[k]->keyWords.end(); iter++)
			out << iter->first << string(" ") << iter->second << string("\n");

		if(k == EndPos)
			break;
	}

	out.close();
}

/**********************************************************************************************
*Debug Method
***********************************************************************************************/
void UserItermSimilarSolution::showStopWords()
{
	if(m_isInitial)
		cout << m_stopWords;
}

void UserItermSimilarSolution::showKeyWordWeight()
{
	for(int k = 0; k < m_articleList.size(); k++)
	{
		cout << "id: " << m_articleList[k]->id << endl;
		for(hash_map<string, double>::iterator iter = m_articleList[k]->keyWords.begin(); iter != m_articleList[k]->keyWords.end(); iter++)
		{
			cout << iter->first << " " << iter->second << endl;
		}
	}
}

void UserItermSimilarSolution::testReco()
{
	for(int k = 0; k < m_userList[0]->alternativeList.size(); k++)
	{
		cout << m_userList[0]->id << " " << m_userList[0]->alternativeList[k].id << endl;
	}

	cout << "......................." << endl;
	for(int k = 0; k < m_userList[0]->pastArticleList.size(); k++)
	{
		cout << m_userList[0]->id << " " << m_userList[0]->pastArticleList[k] << endl;
	}

	cout << "......................." << endl;
	for(int k = 0; k < m_userList[0]->alternativeList.size(); k++)
	{
		for(int j = 0; j < m_userList[0]->pastArticleList.size(); j++)
		{
			if(m_userList[0]->alternativeList[k].id == m_userList[0]->pastArticleList[j])
				cout << m_userList[0]->alternativeList[k].id;
		}
	}
}