#include <iostream>
#include <ctime>
#include "Bubblesort.h"
using namespace std;

Bubblesort::Bubblesort()
{

}

//
//void BubbleSort(ListaEncadeada Lista, int n)
//{
//	const clock_t t0 = clock();
//	for (int i = 0; i < n - 1; i++)
//	{
//		for (int j = 0; j < n - i - 1; j++)
//		{
//			//numeroDeComparacoes++;
//			if (Lista.at(j) > Lista.at(j + 1))
//			{
//				//numeroDeTrocas++;
//				int aux = vec.at(j);
//				vec.at(j) = vec.at(j + 1);
//				vec.at(j + 1) = aux;
//			}
//
//		}
//	}
//
//	cout << "Tempo BubblerSort: " << float(clock() - t0) / CLOCKS_PER_SEC << endl;
//}