#include "AuthorsHashTable.h"
#include <iostream>

using namespace std;

AuthorsHashTable::AuthorsHashTable(int m1)
{
	this->tableSize = m1;
	this->m1 = m1;
	this->m2 = m1-1;

	hashTable->resize(m1);

	for (int i = 0; i < tableSize; i++)
	{
		hashTable->at(i) = new Author("vazio");
	}
	numeroDeColisoes = 0;
}

int AuthorsHashTable::GetSomaAsciiDosCaracteres(string name)
{
	int soma = 0;
	for (int i = 0; i < name.size(); i++)
		soma = soma + name.at(i);
	return soma;
}

int AuthorsHashTable::HashFunction(string nome, int i)
{
	int key = GetSomaAsciiDosCaracteres(nome);	
	return (HashFunction1(key) + i * HashFunction2(key)) % this->m1;
}

int AuthorsHashTable::HashFunction1(int key)
{
	return key % this->m1;
}

int AuthorsHashTable::HashFunction2(int key)
{
	return 1 + (key % this->m2);
}

bool AuthorsHashTable::Insert(Author* author)
{
	int i = 0;	//numero de tentativas de inserção
	int hash = HashFunction(author->authorName, i);

	//elemento encontrado na posicao cauculada
	auto autorAux = this->hashTable->at(hash);

	if (author->authorName == "Desconhecido")
		cout << "desc\n";
	
	//Se autorAux tem o mesmo nome, esse autor ja foi inserido, entao apenas incrementamos sua ocorrencia e retornamos
	if (autorAux->authorName == author->authorName) {
		this->hashTable->at(hash)->appearances += 1;
		return true;
	}

	//Enquanto nao encontrar posicao vazia, ocorrem colisoes
	while (autorAux->authorName != "vazio" && i < this->tableSize - 1)
	{
		this->numeroDeColisoes++;
		i++;
		hash = HashFunction(author->authorName, i);
		autorAux = hashTable->at(hash);
	}

	this->hashTable->at(hash) = author;
	return true;

}

Author* AuthorsHashTable::Lookup(string name)
{
	int i = 0;	//numero de tentativas
	int hash = HashFunction(name, i);

	//elemento encontrado na posicao calculada
	auto autorAux = this->hashTable->at(hash);

	//Se autorAux tem o mesmo nome, esse autor ja foi inserido, entao apenas incrementamos sua ocorrencia e retornamos
	if (autorAux->authorName == name) {
		return autorAux;
	}

	//Enquanto nao encontrar posicao vazia, ocorrem colisoes
	while (autorAux->authorName != name && i < this->tableSize - 1)
	{
		i++;
		hash = HashFunction(name, i);
		autorAux = hashTable->at(hash);
	}

	if (autorAux->authorName == name)
		return autorAux;
	return nullptr;

}

int AuthorsHashTable::GetNumeroDeColisoes()
{
	return this->numeroDeColisoes;
}

void AuthorsHashTable::PrintAutores(vector<Author*>* autores)
{	
	for (int i = autores->size()-1; i >= 0; i--)
	{
		auto author = autores->at(i);
		cout << i << ": " << author->authorName << " - " << author->appearances << endl;
	}
}



vector<Author*>* AuthorsHashTable::GetListaDeAutoresOrdenadaPorAppearances()
{
	auto autoresOrdenados = QuickSort(this->hashTable, 0, tableSize);
	return autoresOrdenados;
}

vector<Author*>* AuthorsHashTable::QuickSort(vector<Author*>* autores, int inicio, int fim)
{
	int i = inicio;
	int j = fim - 1;
	int pivot = autores->at((inicio + fim) / 2)->appearances;
	int aux;
	string auxStr;

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
			auxStr = autores->at(i)->authorName;

			autores->at(i)->appearances = autores->at(j)->appearances;
			autores->at(i)->authorName = autores->at(j)->authorName;

			autores->at(j)->appearances = aux;
			autores->at(j)->authorName = auxStr;


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

	return autores;
}




