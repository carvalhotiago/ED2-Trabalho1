#include <iostream>
#include "Quicksort.h"

using namespace std;

void Quicksort::Swap(string* vetorA, string* vetorB)
{
	string temp = *vetorA;
	*vetorA = *vetorB;
	*vetorB = temp;
}

int Quicksort::DivisaoQuickSort(vector<Book*>& books, int inicio, int size)
{
	int pivo = books.size();
	int i = (inicio - 1);

	for (int j = inicio; j <= size - 1; j++)
	{
		if (books.at(j)->title < books.at(static_cast<long long>(j) + 1)->title)
		{
			i = i + 1;
			Swap(&books.at(i)->title, &books.at(j)->title);
		}
	}
	Swap(&books.at(static_cast<long long>(i) + 1)->title, &books.at(books.size() - 1)->title);
	
	return (i + 1);
}

void Quicksort::QuickSort(vector<Book*>& books, int inicio, int fim)
{
	if (inicio < fim)
	{
		int indiceParticao = DivisaoQuickSort(books, inicio, fim);

		QuickSort(books, inicio, indiceParticao - 1);
		QuickSort(books, indiceParticao + 1, fim);
	}
}