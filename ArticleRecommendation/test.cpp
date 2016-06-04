#include "stdafx.h"
#include "ArticleRecommendSystem.h"
#include"BPNN_Recommendation.h"

/*ldy*/
/*int main()
{
	ArticleRecommendSystem *a = new ArticleRecommendSystem();
	
	a->loadUserTrainInfo("user-info-train.txt");
	a->loadAlternativeInfo("user-info-test.txt");
	//a->loadArticleInfo("raw-data.txt");
		
	a->getSocialRecommendation();
	
	a->writeRecommendInfo("SocialRecommend.txt", SOCIAL);
	
	return 0;
}*/

/*yj*/
/*int main()
{
	ArticleRecommendSystem *a = new ArticleRecommendSystem();

	a->loadUserTrainInfo("user-info-train.txt");
	a->loadAlternativeInfo("user-info-test.txt");
	a->loadArticleInfo("raw-data.txt");

	a->getPersonalizedRecommendation();

	a->writeRecommendInfo("PersonalRecommend.txt", PERSONAL);
}*/

/*fkj*//*
int main()
{

}*/

int main()
{
	/*
	ArticleRecommendSystem *a = new ArticleRecommendSystem();

	a->loadUserTrainInfo("user-info-train.txt");
	a->generateRandomTrainInfo("train1.txt", "test1.txt", "answer1.txt");

	delete a;

	ArticleRecommendSystem *ar = new ArticleRecommendSystem();
	ar->loadUserTrainInfo("train1.txt");
	ar->loadAlternativeInfo("test1.txt");
	//ar->loadArticleInfo("raw-data.txt");

	//a->getSocialRecommendation();
	//a->getPersonalizedRecommendation();

	//a->getBPNNRecommendation();
	*/
	
	BPNN_Recommendation *bp = new BPNN_Recommendation();
	bp->loadAnswerFromFile("answer1.txt");
	bp->showAnswer();
}
