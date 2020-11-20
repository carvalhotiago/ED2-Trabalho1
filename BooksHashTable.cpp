#include "BooksHashTable.h"
#include <iostream>

using namespace std;

BooksHashTable::BooksHashTable(int size)
{
	hashTable.resize(size);
	for (int i = 0; i < size; i++)
	{
		hashTable.at(i) = new vector<Book*>();
	}
	tableSize = size;
	numeroDeColisoes = 0;
}

int BooksHashTable::HashFunction(int key)
{
	return key % tableSize;
}

void BooksHashTable::Insert(Book* book)
{
	int key = stoi(book->isbn10.substr(0, 7)); //nao peguei o isbn10 inteiro pq as vezes nao cabe em INT
	int hash = HashFunction(key);
	vector<Book*>* row = this->hashTable.at(hash);
	row->push_back(book);
}

int BooksHashTable::GetNumeroDeColisoes()
{
	int numeroDeColisoes = 0;
	for (vector<Book*>* row : this->hashTable)
	{
		if (row->size() > 1)		//Se uma linha tem mais de 1 registro, eh pq houve colis�o
			numeroDeColisoes += row->size() - 1;
	}
	return numeroDeColisoes;
}

void BooksHashTable::PrintHashTable()
{
	cout << "---PRINTANDO TABELA HASH BOOKS\n";
	for (int i = 0; i < this->hashTable.size(); i++) {
		vector<Book*>* row = hashTable.at(i);
		cout << "\n[" << i << "]: ";
		for (int j = 0; j < row->size(); j++) {
			cout << row->at(j)->isbn10 << " ";
		}
	}
}

