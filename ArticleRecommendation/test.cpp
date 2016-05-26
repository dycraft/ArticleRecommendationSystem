#include "stdafx.h"
#include "ArticleRecommendSystem.h"

int main()
{
	ArticleRecommendSystem *a = new ArticleRecommendSystem();
	if (a->loadUserTrainInfo("user-info-train.txt"))
		if (a->loadAlternativeInfo("user-info-test.txt"))
			a->showUserList();
	
	return 0;
}
