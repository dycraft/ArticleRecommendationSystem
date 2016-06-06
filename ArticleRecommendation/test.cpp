#include "stdafx.h"
#include "ArticleRecommendSystem.h"
#include"BPNN_Recommendation.h"

/*final*/
int main()
{
	/*ArticleRecommendSystem *a = new ArticleRecommendSystem();

	a->loadArticleInfo("Data\\raw-data.txt");
	a->loadUserTrainInfo("Data\\user-info-train.txt");
	a->generateRandomTrainInfo("TestData\\train1.txt",
		"TestData\\test1.txt", "TestData\\answer1.txt");

	delete a;*/
	
	
	ArticleRecommendSystem *ar = new ArticleRecommendSystem();
	ar->loadArticleInfo("Data\\raw-data.txt");
	ar->loadUserTrainInfo("TestData\\train1.txt");
	ar->loadAlternativeInfo("TestData\\test1.txt");
	
	ar->getSocialRecommendation();
	ar->getPersonalizedRecommendation();
	ar->getItemRecommendation();

	ar->writeRecommendInfo("RecommendList\\SocialRecommend.txt", SOCIAL);
	ar->writeRecommendInfo("RecommendList\\PersonalizedRecommend.txt", PERSONAL);
	ar->writeRecommendInfo("RecommendList\\ItemRecommend.txt", ITEM);

	ar->getBPNNRecommendation();
	ar->writeRecommendInfo("RecommendList\\MixRecommend.txt", FINAL);
	
}