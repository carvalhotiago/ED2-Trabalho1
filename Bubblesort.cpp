#include <iostream>
#include <ctime>
#include "Bubblesort.h"
using namespace std;

Bubblesort::Bubblesort()
{
	numeroDeComparacoes = 0;
}


void Bubblesort::BubbleSort(vector<Book*> &books, int n)
{
	const clock_t t0 = clock();
	for (int i = 0; i < n - 1; i++)
	{
		for (long j = 0; j < n - i - 1; j++)
		{
			numeroDeComparacoes++;
			if (books.at(j)->title > books.at(static_cast<long long>(j)+1)->title)
			{
				//numeroDeTrocas++;
				string aux = books.at(j)->title;
				books.at(j)->title = books.at(static_cast<long long>(j)+1)->title;
				books.at(static_cast<long long>(j)+1)->title = aux;
			}

		}
	}

	cout << "Tempo BubblerSort: " << float(clock() - t0) / CLOCKS_PER_SEC << endl;
}