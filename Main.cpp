#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>
#include "No.h"
#include "Lista.h"
#include "Book.h"
#include "Bubblesort.h"
#include "Quicksort.h"

using namespace std;

template <typename T>
void PrintListOfBook(vector<T*>& books)
{
	for (int i = 0; i < books.size(); i++)
	{
		Book* book = books.at(i);
		for (int j = 0; j < book->authors->size(); j++)
			cout << "authors: " << book->authors->at(j) << endl;
		cout << "bestsellersRank: " << book->bestsellersRank << endl;
		for (int k = 0; k < book->categories->size(); k++)
			cout << "categories: " << book->categories->at(k) << endl;
		cout << "edition: " << book->edition << endl;
		cout << "id: " << book->id << endl;
		cout << "isbn10: " << book->isbn10 << endl;
		cout << "isbn13: " << book->isbn13 << endl;
		cout << "ratingAvg: " << book->ratingAvg << endl;
		cout << "ratingCount: " << book->ratingCount << endl;
		cout << "title: " << book->title << endl;
	}
}

template <typename T>
void PrintBookTitles(vector<T*>& books)
{
	for (int i = 0; i < books.size(); i++)
	{
		Book* book = books.at(i);
		cout << book->title << endl;
	}
	cout << endl;
}

vector<int>* split(const string& s, char delimiter) {
	vector<int>* tokens = new vector<int>;
	string token;
	istringstream tokenStream(s);
	while (getline(tokenStream, token, delimiter)) {
		tokens->push_back(stoi(token));
	}
	return tokens;
}

int main()
{
	srand(time(NULL));

	ifstream entrada;
	entrada.open("Data/entrada.txt");
	int numeroDeEntradas;
	entrada >> numeroDeEntradas;
	vector<int> valoresDeN;

	string str;
	string x;
	getline(entrada, x);
	while (getline(entrada, str)) {
		valoresDeN.push_back(stoi(str));
	}

	ifstream arquivo;
	arquivo.open("Data/small-teste.csv");

	Lista<int> authorsIds;
	int cont = 0;

	regex regex("\s*(\"[^\"]*\")");

	if (arquivo.is_open())
	{
		//// Guarda tamanho do arquivo em bytes
		arquivo.seekg(0, arquivo.end);
		int tamanhoDoArquivo = arquivo.tellg();
		arquivo.seekg(0, arquivo.beg);
		for (int k = 0; k < valoresDeN.size(); k++)
		{
		vector<vector<Book*>*> listaDeVetores;
			for (unsigned j = 0; j < 5; j++) // 5 � o numero de amostras que ser�o geradas aleatoriamente para cada N
			{
				vector<Book*>* vet = new vector<Book*>();

				for (int i = 0; i < valoresDeN.at(k); i++) // i < x, em que x � o tamanho da amostra aleat�ria a ser gerada
				{
					// Pega a linha correspondente a um byte aleatorio
					srand(time(NULL) + rand());
					int byteAleatorio = rand() % (tamanhoDoArquivo - 500); // esse desconto no tamanhoDoArquivo evita com que a a linha aleat�ria seja a �ltima, o que causaria erro j� que n�o h� linha seguinte � �ltima
					arquivo.seekg(byteAleatorio);

					//Primeiro d� um getline para ir pro in�cio da linha seguinte � linha aleat�ria em que caiu, e ent�o d� o getline pra pegar a linha que nos interessa
					string dump;
					string str;
					getline(arquivo, dump);
					getline(arquivo, str); //Tirei o "While(getline) pq o n�mero de vezes que ele vai ler linhas aleat�rias vai ser definido pelo N

					Book* book = new Book();
					stringstream ss(str);

					sregex_iterator iterator(str.begin(), str.end(), regex);
					vector<string>* registro = new vector<string>;
					sregex_iterator end;

					while (iterator != end)
					{
						for (unsigned i = 0; i < iterator->size() - 1; i++)
						{
							string input;
							getline((stringstream)(*iterator)[i], input);
							input = input.substr(1, input.size() - 2);
							registro->push_back(input);
						}
						iterator++;
					}

					string text = registro->at(0) = registro->at(0).substr(1, registro->at(0).size() - 2);
					stringstream iss(text);
					vector<int>* authorsIds = split(text, ',');
					text = registro->at(2) = registro->at(2).substr(1, registro->at(2).size() - 2);
					vector<int>* categories = split(text, ',');

					book->authors = authorsIds;
					book->bestsellersRank = registro->at(1);
					book->categories = categories;
					book->edition = registro->at(3);
					book->id = registro->at(4);
					book->isbn10 = registro->at(5);
					book->isbn13 = registro->at(6);
					book->ratingAvg = registro->at(7);
					book->ratingCount = registro->at(8);
					book->title = registro->at(9);

					vet->push_back(book);
				}
				listaDeVetores.push_back(vet);
			}


			PrintBookTitles(*listaDeVetores.at(0));

			/*Bubblesort bs;
			for (int i = 0; i < listaDeVetores.size(); i++)
			{
				vector<Book*>* vectorAtual = listaDeVetores.at(i);
				cout << "i: " << i << endl;

				bs.BubbleSort(*vectorAtual, vectorAtual->size());
			}*/


			Quicksort quick;
			for (int i = 0; i < listaDeVetores.size(); i++)
			{
				vector<Book*>* vectorAtual = listaDeVetores.at(i);
				cout << "i: " << i << endl;

				quick.Execute(*vectorAtual, 0, vectorAtual->size());
			}

			
			PrintBookTitles(*listaDeVetores.at(0));
		}
		arquivo.seekg(0, arquivo.beg);
		arquivo.close();
	}
	else
	{
		cerr << "Erro ao abrir arquivo!" << endl;
		exit(1);
	}

	cout << "Programa encerrado com sucesso!" << endl;

	return 0;
}