#include "stdafx.h"
#include "ArticleRecommendSystem.h"
#include "PersonalizedRecommendation.h"

int main()
{
	ArticleRecommendSystem *a = new ArticleRecommendSystem();
	if(!a->loadArticleInfo("raw-data.txt"))
		cout << "Error: fail open raw-data.txt" << endl; 
	if (a->loadUserTrainInfo("user-info-train.txt"))
	{
		if (!a->loadAlternativeInfo("user-info-test.txt"))
			cout << "Error: fail open user-info-test.txt" << endl;
	}
	else
		cout << "Error: fail open user-info-train.txt" << endl;

	UserItermSimilarSolution *u = new UserItermSimilarSolution(a->userList, a->articleList);
	//u->showStopWords();
	//u->KeyWordByIF_IDF();
	//u->SaveIF_IDF_ToFile();
	u->readKeyWordFromFile("IF_IDF.txt");
	//u->showKeyWordWeight();
	u->recommendArticle();
	
	//cout << "Finish..." << endl;
	//getchar();

	return 0;
}
