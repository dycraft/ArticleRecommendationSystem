#include "stdafx.h"
#include "ArticleRecommendSystem.h"
#include"BPNN_Recommendation.h"

void test_geneTrain()
{
	ArticleRecommendSystem *a = new ArticleRecommendSystem();

	a->loadArticleInfo("Data\\raw-data.txt");
	a->loadUserTrainInfo("Data\\user-info-train.txt");
	a->generateRandomTrainInfo("TestData\\train1.txt",
		"TestData\\test1.txt", "TestData\\answer1.txt");
}

void test_run()
{
	ArticleRecommendSystem *ar = new ArticleRecommendSystem();
	ar->loadArticleInfo("Data\\raw-data.txt");
	ar->loadUserTrainInfo("Data\\user-info-train.txt");
	ar->loadAlternativeInfo("Data\\user-info-test.txt");

	ar->getSocialRecommendation();
	ar->getPersonalizedRecommendation();
	ar->getItemRecommendation();

	ar->writeRecommendInfo("RecommendList\\SocialRecommend.txt", SOCIAL);
	ar->writeRecommendInfo("RecommendList\\PersonalizedRecommend.txt", PERSONAL);
	ar->writeRecommendInfo("RecommendList\\ItemRecommend.txt", ITEM);

	ar->getBPNNRecommendation();
	ar->writeRecommendInfo("RecommendList\\MixedRecommend.txt", FINAL);
}

int main()
{
	//test_geneTrain();
	test_run();
}