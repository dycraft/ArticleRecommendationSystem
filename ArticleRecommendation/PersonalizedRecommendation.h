#pragma once
//implement by Yang Jing

#include "stdafx.h"
#include "User.h"
#include "Article.h"

class PersonalRecommendSolution
{
private:
	vector<User*> m_userList;
	vector<Article*> m_articleList;
	bool m_isInitial;               //make Sure initial first£¬IF-IDF next
	string m_stopWords;
	vector<vector<int>> m_answer;

public:
	PersonalRecommendSolution(vector<User*>& userList, vector<Article*>& articleList);     //get UserList And ArticleList
	~PersonalRecommendSolution(){}

	void KeyWordByIF_IDF();   //IF-IDF
	void readKeyWordFromFile(string fileName);
	void recommendArticle();  //recommend

	//sava data in file for fast speed
	void SaveIF_IDF_ToFile();

	void loadAnswerFromFile(string fileName);
	//Debug method
	void showStopWords();
	void showKeyWordWeight();
	void testReco();
};
