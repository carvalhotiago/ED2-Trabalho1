#include "BooksHashTable.h"

BooksHashTable::BooksHashTable(int size)
{
	booksHashTable.resize(size);
	tableSize = size;
	numeroDeColisoes = 0;
}

int BooksHashTable::HashFunction(int key)
{
	return key % tableSize;
}

void BooksHashTable::Insert(Book* book)
{
	int key = stoi(book->isbn10);
	int hash = HashFunction(key);
	vector<Book*>* row = this->booksHashTable.at(hash);
	row->push_back(book);
}

int BooksHashTable::GetNumeroDeColisoes()
{
	int numeroDeColisoes = 0;
	for (vector<Book*>* row : this->booksHashTable)
	{
		if (row->size() > 1)		//Se uma linha tem mais de 1 registro, eh pq houve colis�o
			numeroDeColisoes += row->size() - 1;
	}
}

