#pragma once
#include "Book.h"
#include<vector>

class Quicksort {
public:
	void Swap(string* vetorA, string* vetorB);
	int DivisaoQuickSort(vector<Book*>& books, int inicio, int size);
	void QuickSort(vector<Book*>& books, int inicio, int fim);
};