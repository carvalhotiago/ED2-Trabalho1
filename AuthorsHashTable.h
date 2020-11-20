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

	vector<vector<Author*>*> hashTable;
};

