#pragma once
#include "Book.h"
#include<vector>

class Quicksort {
public:
	void QuickSort(vector<Book*>& books, int inicio, int fim);
	long Execute(vector<Book*>& books, int inicio, int fim);
	int numComparacoes;
};