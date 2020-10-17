#pragma once
#include <string>
#include <vector>

using namespace std;

class Book
{
public:
    Book();
    vector<int>* authors;
    string bestsellersRank;
    string categories;
    string edition;
    string id;
    string isbn10;
    string isbn13;
    string ratingAvg;
    string ratingCount;
    string title;
};

