#ifndef BUBBLESORT_H
#define BUBBLESORT_H
#include "Book.h"
#include<vector>

class Bubblesort {
public:
	int numeroDeComparacoes;
	int numeroDeCopiasRegistro;
	Bubblesort();
	long BubbleSort(vector<Book*>& books, int n);
};

#endif