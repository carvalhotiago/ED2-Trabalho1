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
	//pegando apenas os 6 primeiros digitos do campo isbn, que ja sao suficientes para fazer o hash
	string x = book->isbn10.substr(0, 6);

	//caso nao seja possivel fazer a conversao do isbn10 por algum motivo, o valor padrao de Key fara com que o elemento seja alocado na ultima entrada da tabela
	int key = tableSize-1;
	try
	{
		key = stoi(x);
	}
	catch (const std::exception& ex) 
	{
		cout << ex.what() << '\n';
	}

	int hash = HashFunction(key);

	//como estamos trabalhando com enderecamento aberto com listas encadeadas, cada hashing nos fornece uma outra lista de entradas que possuem o mesmo hash
	vector<Book*>* row = this->hashTable.at(hash);

	//se for repetido, retorna false e nao insere
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
		if (row->size() > 1)		//Se uma linha tem mais de 1 registro, eh pq houve colisao
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


