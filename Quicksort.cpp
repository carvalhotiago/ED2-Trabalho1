#include <iostream>
#include "Quicksort.h"

using namespace std;

void Quicksort::Swap(int* vetorA, int* vetorB) {
	int temp = *vetorA;
	*vetorA = *vetorB;
	*vetorB = temp;
}

int Quicksort::DivisaoQuickSort(int vetor[], int inicio, int size)
{
	int pivo = vetor[size];
	int i = (inicio - 1);

	for (int j = inicio; j <= size - 1; j++)
	{
		if (vetor[j] < pivo)
		{
			i = i + 1;
			Swap(&vetor[i], &vetor[j]);
		}
	}
	Swap(&vetor[i + 1], &vetor[size]);

	return (i + 1);
}

void Quicksort::QuickSort(int vetor[], int inicio, int fim)
{
	if (inicio < fim)
	{
		int indiceParticao = DivisaoQuickSort(vetor, inicio, fim);

		QuickSort(vetor, inicio, indiceParticao - 1);
		QuickSort(vetor, indiceParticao + 1, fim);
	}
}