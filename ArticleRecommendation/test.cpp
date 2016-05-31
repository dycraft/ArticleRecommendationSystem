#include "stdafx.h"
#include "ArticleRecommendSystem.h"

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
int main()
{
	ArticleRecommendSystem *a = new ArticleRecommendSystem();

	a->loadUserTrainInfo("user-info-train.txt");
	a->loadAlternativeInfo("user-info-test.txt");
	a->loadArticleInfo("raw-data.txt");

	a->getPersonalizedRecommendation();

	a->writeRecommendInfo("PersonalRecommend.txt", PERSONAL);
}

/*fkj*//*
int main()
{

}*/
