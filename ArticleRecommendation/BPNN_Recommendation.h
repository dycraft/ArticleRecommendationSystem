#pragma once 

#include "stdafx.h"
#include "User.h"
#include "Article.h"

class BPNN_Recommendation
{
public:
	vector<User*> m_userList;
	vector<Article*> m_articleList;
	vector<vector<int>> m_answer;
	double m_accuracy; 
	double m_x, m_y;

public:
	BPNN_Recommendation(vector<User*>& userList, vector<Article*>& articleList); //get UserList And ArticleList
	BPNN_Recommendation(){m_answer.clear(); m_x = m_y = m_accuracy = 0.0;};
	~BPNN_Recommendation(){}

	void loadAnswerFromFile(string fileName);
	
	void trainingXY();
	void recommendArticle();

	void training();
	void recommendArticleByBP();
	//write m_x m_y into file
	void WriteXYintoFile();
	//read m_x m_y into file
	void ReadXYintoFile(string fileName);

	//Debug method
	void showAnswer();
	void printNNInput(vector<vector<double>>& input);
	void printNNOutput(vector<vector<double>>& output);
};