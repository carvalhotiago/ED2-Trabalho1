#include <iostream>
#include "Quicksort.h"
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;

using namespace std;

//Algoritmo QuickSort
void Quicksort::QuickSort(vector<Book*>& books, int inicio, int fim)
{
	int i = inicio;
	int j = fim - 1;
	string pivot = books.at((inicio + fim) / 2)->title;
	string aux;

	while (i <= j)
	{
		numComparacoes++;
		while (books.at(i)->title < pivot && i < fim){
			numComparacoes++;
			i++;
		}
		
		while (books.at(j)->title > pivot && j > inicio){
			numComparacoes++;
			j--;
		}
		
		if (i <= j)
		{
			numComparacoes++;
			numCopiasRegistros++;
			aux = books.at(i)->title;
			books.at(i)->title = books.at(j)->title;
			books.at(j)->title = aux;
			i++;
			j--;
		}
	}
	if (j > inicio){
		numComparacoes++;
		QuickSort(books, inicio, j + 1);
	}
	if (i < fim) {
		numComparacoes++;
		QuickSort(books, i, fim);
	}
}

//Algortimo de execução do QuickSort
long Quicksort::Execute(vector<Book*>& books, int inicio, int fim)
{
	numComparacoes = 0;
	numCopiasRegistros = 0;
	auto t1 = Clock::now();
	this->QuickSort(books, inicio, fim);
	auto t2 = Clock::now();

	long tempo = chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	cout << "Tempo Quicksort: " << tempo << " microseconds" << endl;
	return tempo;
}
