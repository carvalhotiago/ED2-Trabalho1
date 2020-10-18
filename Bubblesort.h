#ifndef BUBBLESORT_H
#define BUBBLESORT_H
#include "Book.h"
#include<vector>

class Bubblesort {
private:
	int numeroDeComparacoes;
public:
	Bubblesort();
	void BubbleSort(vector<Book*>& books, int n);
};

#endif