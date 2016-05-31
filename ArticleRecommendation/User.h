#pragma once

#include "stdafx.h"

struct WeightArticle;

class User
{
public:
	int id;
	vector<int> pastArticleList; //int equals WeightArticle but weight = 1 or 0
	vector<WeightArticle> alternativeList;

public:
	User();
	User(int id);
	~User();

	//operator method
	void addPastArticle(int id_a);
	void addAlternative(int id_a);

	//debug method
	void showUser();
};

struct WeightArticle
{
	int id;
	double weight[ALGO_NUM]; //include mixed-final

	WeightArticle() :id(0)
	{
		for (int i = 0; i < ALGO_NUM; i++)
		{
			weight[i] = 0.0;
		}
	}

	WeightArticle(int _id) :id(_id)
	{
		for (int i = 0; i < ALGO_NUM; i++)
		{
			weight[i] = 0.0;
		}
	}

	WeightArticle(const WeightArticle& w) :id(w.id)
	{
		for (int i = 0; i < ALGO_NUM; i++)
		{
			weight[i] = w.weight[i];
		}
	}
};

//cmp function for qsort, high-weight goes before low-weight
//extern int cmp_WeightArticle(const void *a, const void *b);
