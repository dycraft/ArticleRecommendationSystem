#include "stdafx.h"
#include "ArticleRecommendSystem.h"

int main()
{
	ArticleRecommendSystem *a = new ArticleRecommendSystem();
	if (a->loadUserTrainInfo("user-info-train.txt"))
		a->showUserList();

	getchar();
	return 0;
}
