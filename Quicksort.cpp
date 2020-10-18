#include <iostream>
#include "Quicksort.h"

using namespace std;

void Quicksort::QuickSort(vector<Book*>& books, int inicio, int fim)
{
	int i = inicio;
	int j = fim - 1;
	string pivot = books.at((inicio + fim) / 2)->title;
	string aux;

	while (i <= j)
	{
		while (books.at(i)->title < pivot && i < fim)		
			i++;
		
		while (books.at(j)->title > pivot && j > inicio)
			j--;
		
		if (i <= j)
		{
			aux = books.at(i)->title;
			books.at(i)->title = books.at(j)->title;
			books.at(j)->title = aux;
			i++;
			j--;
		}
	}
	if (j > inicio)
		QuickSort(books, inicio, j + 1);
	if (i < fim)
		QuickSort(books, i, fim);
}