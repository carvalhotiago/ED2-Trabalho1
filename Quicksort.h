#pragma once


class Quicksort {
public:
	void Swap(int* vetorA, int* vetorB);
	int DivisaoQuickSort(int vetor[], int inicio, int size);
	void QuickSort(int vetor[], int inicio, int fim);
};