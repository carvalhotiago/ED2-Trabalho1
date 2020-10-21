#pragma once
#include<vector>

class ShellSort
{
public:
	ShellSort();
	long Shellsort(vector<Book*>& books, int n);
	int numeroDeComparacoes;
	int numeroDeCopiasRegistro;
};

