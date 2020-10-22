#include <ctime>
#include <chrono>
#include <vector>
#include <iostream>
#include "Book.h"
#include "ShellSort.h"
typedef std::chrono::high_resolution_clock Clock;

using namespace std;

ShellSort::ShellSort()
{
	numeroDeComparacoes = 0;
	numeroDeCopiasRegistro = 0;
}

//Algoritmo de execução do ShellSort
long ShellSort::Shellsort(vector<Book*>& books, int n)
{
	const clock_t t0 = clock();
	auto t1 = Clock::now();
	for (int passo = n / 2; passo > 0; passo /= 2)
	{
		for (int i = passo; i < n; i++)
		{
			string aux = books.at(i)->title;
			int j;

			for (j = i; j >= passo && books.at(j - passo)->title > aux; j -= passo, numeroDeComparacoes++)
			{
				numeroDeCopiasRegistro++;
				books.at(j)->title = books.at(j - passo)->title;
			}
			books.at(j)->title = aux;
		}
	}

	auto t2 = Clock::now();
	long tempo = chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	cout << "Tempo ShellSort: " << tempo << " microseconds" << endl;
	return tempo;
}