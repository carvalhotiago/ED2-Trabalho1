#include <iostream>
#include <ctime>
#include "Bubblesort.h"
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;


using namespace std;

Bubblesort::Bubblesort()
{
	numeroDeComparacoes = 0;
	numeroDeCopiasRegistro = 0;
}


long Bubblesort::BubbleSort(vector<Book*> &books, int n)
{
	numeroDeComparacoes = 0;
	numeroDeCopiasRegistro = 0;
	auto t1 = Clock::now();
	for (int i = 0; i < n - 1; i++)
	{
		numeroDeComparacoes++;
		for (long j = 0; j < n - i - 1; j++)
		{
			numeroDeComparacoes++;
			if (books.at(j)->title > books.at(static_cast<long long>(j)+1)->title)
			{
				numeroDeComparacoes++;
				numeroDeCopiasRegistro++;
				string aux = books.at(j)->title;
				books.at(j)->title = books.at(static_cast<long long>(j)+1)->title;
				books.at(static_cast<long long>(j)+1)->title = aux;
			}

		}
	}

	auto t2 = Clock::now();
	long tempo = chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
	cout << "Tempo BubbleSort: " << tempo << " milliseconds" << endl;
	return tempo;
}