#include "stdafx.h"
#include "ArticleRecommendSystem.h"
#include"BPNN_Recommendation.h"

/*ldy*//*
int main()
{
	ArticleRecommendSystem *a = new ArticleRecommendSystem();
	
	a->loadArticleInfo("raw-data.txt");
	a->loadUserTrainInfo("user-info-train.txt");
	a->loadAlternativeInfo("user-info-test.txt");
		
	a->getSocialRecommendation();
	
	a->writeRecommendInfo("SocialRecommend.txt", SOCIAL);
	
	return 0;
}*/

/*yj*//*
int main()
{
	ArticleRecommendSystem *a = new ArticleRecommendSystem();

	a->loadArticleInfo("raw-data.txt");
	a->loadUserTrainInfo("user-info-train.txt");
	a->loadAlternativeInfo("user-info-test.txt");

	a->getPersonalizedRecommendation();

	a->writeRecommendInfo("PersonalRecommend.txt", PERSONAL);
}*/

/*fkj*//*
int main()
{
	ArticleRecommendSystem *a = new ArticleRecommendSystem();
	
	a->loadArticleInfo("raw-data.txt");
	a->loadUserTrainInfo("user-info-train.txt");
	a->loadAlternativeInfo("user-info-test.txt");
		
	a->getItemRecommendation();
	
	a->writeRecommendInfo("ItemRecommend.txt", ITEM);
	
	return 0;
}*/

/*final*/
int main()
{
    /*
	ArticleRecommendSystem *a = new ArticleRecommendSystem();

	a->loadArticleInfo("raw-data.txt");
	a->loadUserTrainInfo("user-info-train.txt");
	a->generateRandomTrainInfo("train1.txt", "test1.txt", "answer1.txt");

	delete a;
	
	*/
	
	ArticleRecommendSystem *ar = new ArticleRecommendSystem();
	ar->loadArticleInfo("raw-data.txt");
	ar->loadUserTrainInfo("train1.txt");
	ar->loadAlternativeInfo("test1.txt");
	
	ar->getSocialRecommendation();
	ar->getPersonalizedRecommendation();
	ar->getItemRecommendation();

	ar->getBPNNRecommendation();
	//ar->writeRecommendInfo("MixRecommend.txt", FINAL);
	
}