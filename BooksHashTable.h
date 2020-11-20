#pragma once
#include <vector>
#include "Book.h"

using namespace std;

class BooksHashTable
{
private:
	int numeroDeColisoes;
	int tableSize;

public:
	BooksHashTable(int size);
	~BooksHashTable();
	int HashFunction(int key);
	void Insert(Book* book);
	Book* Lookup(int key);
	int GetNumeroDeColisoes();
	void PrintHashTable();

	vector<vector<Book*>*> hashTable;
};

