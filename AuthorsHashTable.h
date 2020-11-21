#pragma once
#include <vector>
#include <string>
#include "Author.h"

using namespace std;

class AuthorsHashTable
{
private:
	int numeroDeColisoes;
	int tableSize;

public:
	AuthorsHashTable(int size);
	~AuthorsHashTable();
	int HashFunction(string name);
	void Insert(Author* author);
	Author* Lookup(string key);
	int GetNumeroDeColisoes();
	void PrintHashTable();
	vector<Author*>* GetListaDeAutores();
	vector<Author*>* GetListaDeAutoresOrdenadaPorAppearances();
	vector<Author*>* QuickSort(vector<Author*>* autores, int inicio, int fim);
	void PrintListaDeAutores(vector<Author*>* autores);

	vector<vector<Author*>*> hashTable;
};

