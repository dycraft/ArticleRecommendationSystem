#include "stdafx.h"
#include "ArticleRecommendSystem.h"

int main()
{
	ArticleRecommendSystem *a = new ArticleRecommendSystem();
	if (a->loadArticleInfo("raw-data.txt"))
		a->showArticleList();

	return 0;
}
