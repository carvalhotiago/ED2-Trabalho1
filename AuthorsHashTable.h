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
	int m1;
	int m2;

public:
	AuthorsHashTable(int size);
	~AuthorsHashTable();
	bool Insert(Author* author);
	Author* Lookup(int id);

	int HashFunction(int id, int i);
	int HashFunction1(int key);
	int HashFunction2(int key);
	
	void SetAuthorsName(int id, string nome);
	int GetNumeroDeColisoes();
	void PrintAutores(vector<Author*>* autores);
	vector<Author*>* GetListaDeAutoresOrdenadaPorAppearances();
	vector<Author*>* QuickSort(vector<Author*>* autores, int inicio, int fim);
	int GetSomaAsciiDosCaracteres(string name);

	vector<Author*>* hashTable = new vector<Author*>();
};

