# Article Recommendation System

Generally Speaking, there are 4 main approaches for recommendations.
+ Personalized recommendation: recommend things based on the individual's past behavior
+ Social recommendation: recommend things based on the past behavior of similar users
+ Item recommendation: recommend things based on the item itself
+ A combination of the three approaches above

We choose the combination approach.

## Data
#### Training Data
The training data consists of 2 les which contains 5551 users and 16980 articles in all.

+ **user-info-train.txt**: This file provides the collection history of users. Each line with a <user id, article id> pair format corresponds to a record of a specic user. Take the rst line (1,496) for instance, it indicates that user with id number 1 has collected article with id number 496. For each user, at least 5 articles and at most 202 articles are collected.

+ **raw-data.txt**: This file contains raw content for each article including article title and abstract. Each line is in the form of (article id, "article title", "article abstract").

#### Test Data
The test data consists of the same 5551 users as in the training data. For each user, 251 candidate articles are provides for prediction. Among these 251 articles, at least 5 articles have been collected by the user, others are sampled randomly. The test file is:

+ **user-info-test.txt**: The form of this le is the same with **user-info-train.txt**.

## Reference

0. [RecSys API Doc](http://recsys.baidu.com/recsys/doc?tpl=index&doc=similarity)

0. [UserCF and ItemCF](https://www.zybuluo.com/xtccc/note/200979)

0. [BPNN](https://github.com/AzoresCabbage/BP_NeuronNetwork)

## Project Environment

+ VS 2015 (v140)
+ Language: C++

## Contribution

+ Li Da-Yang
+ Yang Jing
+ Fan Kang-Jing
