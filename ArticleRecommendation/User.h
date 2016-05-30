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
	double weight;

	WeightArticle() :id(0), weight(0.0) {}
	WeightArticle(int _id) :id(_id), weight(0.0) {}
	WeightArticle(const WeightArticle& w) :id(w.id), weight(w.weight) {}
};

//cmp function for qsort, high-weight goes before low-weight
extern int cmp_WeightArticle(const void *a, const void *b);
