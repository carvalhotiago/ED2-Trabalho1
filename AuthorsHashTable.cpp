#include "AuthorsHashTable.h"
#include <iostream>

using namespace std;

AuthorsHashTable::AuthorsHashTable(int size)
{
	hashTable.resize(size);
	for (int i = 0; i < size; i++)
	{
		hashTable.at(i) = new vector<Author*>();
	}
	tableSize = size;
	numeroDeColisoes = 0;
}

int AuthorsHashTable::HashFunction(string name)
{
	int soma = 0;
	for (int i = 0; i < name.size(); i++)
		soma = soma + name.at(i);
	return soma % tableSize;
}

void AuthorsHashTable::Insert(Author* author)
{
	int hash = HashFunction(author->authorName);
	auto row = this->hashTable.at(hash);
	row->push_back(author);
}

Author* AuthorsHashTable::Lookup(string name)
{
	int hash = HashFunction(name);
	auto row = this->hashTable.at(hash);

	if (row->empty()) return nullptr;

	Author* author;
	for (int i = 0; i < row->size(); i++)
	{
		author = row->at(i);
		if (author->authorName == name)
			return author;		
	}
	return nullptr;

}

int AuthorsHashTable::GetNumeroDeColisoes()
{
	int numeroDeColisoes = 0;
	for (vector<Author*>* row : this->hashTable)
	{
		if (row->size() > 1)		//Se uma linha tem mais de 1 registro, eh pq houve colisao
			numeroDeColisoes += row->size() - 1;
	}
	return numeroDeColisoes;
}

vector<Author*>* AuthorsHashTable::GetListaDeAutores()
{
	vector<Author*>* autores = new vector<Author*>();
	for (int i = 0; i < this->tableSize; i++)
	{
		vector<Author*>* row = this->hashTable.at(i);
		for (int j = 0; j < row->size(); j++)
		{
			autores->push_back(row->at(j));
		}
	}

	return autores;
}

vector<Author*>* AuthorsHashTable::GetListaDeAutoresOrdenadaPorAppearances()
{
	auto autores = GetListaDeAutores();
	auto autoresOrdenados = QuickSort(autores, 0, autores->size());
}

vector<Author*>* AuthorsHashTable::QuickSort(vector<Author*>* autores, int inicio, int fim)
{
	int i = inicio;
	int j = fim - 1;
	int pivot = autores->at((inicio + fim) / 2)->appearances;
	int aux;

	while (i <= j)
	{
		while (autores->at(i)->appearances < pivot && i < fim) {
			i++;
		}

		while (autores->at(j)->appearances > pivot && j > inicio) {
			j--;
		}

		if (i <= j)
		{
			aux = autores->at(i)->appearances;
			autores->at(i)->appearances = autores->at(j)->appearances;
			autores->at(j)->appearances = aux;
			i++;
			j--;
		}
	}
	if (j > inicio) {
		QuickSort(autores, inicio, j + 1);
	}
	if (i < fim) {
		QuickSort(autores, i, fim);
	}
}
