#include "stdafx.h"
#include "ArticleRecommendSystem.h"

int main()
{
	ArticleRecommendSystem *a = new ArticleRecommendSystem();

	a->loadUserTrainInfo("user-info-train.txt");
	a->loadAlternativeInfo("user-info-test.txt");
	//a->loadArticleInfo("raw-data.txt");

	a->getSocialRecommendation();

	a->writeRecommendInfo("SocialRecommend.txt");
	
	return 0;
}
