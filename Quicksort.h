#pragma once
#include "Book.h"
#include<vector>

class Quicksort {
public:
	void QuickSort(vector<Book*>& books, int inicio, int fim);
	void Execute(vector<Book*>& books, int inicio, int fim);
};