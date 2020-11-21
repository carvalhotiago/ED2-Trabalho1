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

bool BooksHashTable::Insert(Book* book)
{
	string x = book->isbn10.substr(0, 6);
	int key = tableSize-1;
	try
	{
		key = stoi(x); //nao peguei o isbn10 inteiro pq as vezes nao cabe em INT
	}
	catch (const std::exception& ex) //devido ao formato do dataset ser diferente, pode ser que o campo isbn10 venha vazio pois no novo formato ele corresponde ao campo dimension-y e nao eh sempre que esse campo vem preenchido
	{
		cout << ex.what() << '\n';
	}
	int hash = HashFunction(key);
	vector<Book*>* row = this->hashTable.at(hash);

	if (VerificaLivroRepetido(book, row)) {
		row->push_back(book);
		return true;
	}

	return false;
}

bool BooksHashTable::VerificaLivroRepetido(Book* book, vector<Book*>* row)
{
	auto it = find(row->begin(), row->end(), book);
	if (it != row->end())
	{
		cout << "Livro repetido! Buscando outro... " << endl;
		return false;
	}
	return true;	
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


