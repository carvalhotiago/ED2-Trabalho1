#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>
#include "No.h"
#include "Lista.h"
#include "Book.h"

using namespace std;

template <typename T>
void PrintListOfBook(vector<T*>* books)
{
	for (int i = 0; i < books->size() - 1; i++)
	{
		//Book* book = books->at(i);
		////for (unsigned j = 0; j < books->at(i)->authors->size(); j++)
		//cout << "authors: " << book->authors->at(0) << endl;
		//cout << "bestsellersRank: " << book->bestsellersRank << endl;
		//cout << "categories: " << book->categories << endl;
		//cout << "edition: " << book->edition << endl;
		//cout << "id: " << book->id << endl;
		//cout << "isbn10: " << book->isbn10 << endl;
		//cout << "isbn13: " << book->isbn13 << endl;
		//cout << "ratingAvg: " << book->ratingAvg << endl;
		//cout << "ratingCount: " << book->ratingCount << endl;
		//cout << "title: " << book->title << endl;
	}
}

vector<int>* formatadorDeString(int indice, int inicio, int fim, vector<string>* registro)
{
	string text = registro->at(indice) = registro->at(indice).substr(inicio, registro->at(fim).size() - fim);

	stringstream iss(text);

	int number;
	vector<int> myNumbers;
	while (iss >> number)
		myNumbers.push_back(number);

	return &myNumbers;
}

vector<int> split(const string& s, char delimiter) {
	vector<int> tokens;
	string token;
	istringstream tokenStream(s);
	while (getline(tokenStream, token, delimiter)) {
		tokens.push_back(stoi(token));
	}
	return tokens;
}

int main()
{
	int N = 10; //numero de linhas aleatorias a serem capturadas
	srand(time(NULL));

	ifstream entrada;
	entrada.open("entrada.txt");
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
	arquivo.open("Data/teste.txt");

	vector<Book*>* vBooks1 = new vector<Book*>();
	vector<Book*>* vBooks2 = new vector<Book*>();
	vector<Book*>* vBooks3 = new vector<Book*>();
	vector<Book*>* vBooks4 = new vector<Book*>();
	vector<Book*>* vBooks5 = new vector<Book*>();

	Lista<int> authorsIds;
	int cont = 0;

	regex regex("\s*(\"[^\"]*\")");

	if (arquivo.is_open())
	{
		//// Guarda tamanho do arquivo em bytes
		arquivo.seekg(0, arquivo.end);
		int tamanhoDoArquivo = arquivo.tellg();
		arquivo.seekg(0, arquivo.beg);

		//while (!arquivo.eof())
		for (unsigned j = 0; j < 5; j++)
		{
			for (int i = 0; i < valoresDeN.at(0); i++) // falta fazer a lógica para diferentes valores de N
			{
				// Pega a linha correspondente a um byte aleatorio
				srand(time(NULL) + rand());
				int byteAleatorio = rand() % (tamanhoDoArquivo);
				arquivo.seekg(byteAleatorio);

				//Primeiro dá um getline para ir pro início da linha seguinte à linha aleatória em que caiu, e então dá o getline pra pegar a linha que nos interessa
				string dump;
				string str;
				getline(arquivo, dump);
				getline(arquivo, str); //Tirei o "While(getline) pq o número de vezes que ele vai ler linhas aleatórias vai ser definido pelo N

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
				vector<int> authorsIds = split(text, ',');
				text = registro->at(2) = registro->at(2).substr(1, registro->at(2).size() - 2);
				vector<int> categories = split(text, ',');

				book->authors = &authorsIds;
				book->bestsellersRank = registro->at(1);
				book->categories = &categories;
				book->edition = registro->at(3);
				book->id = registro->at(4);
				book->isbn10 = registro->at(5);
				book->isbn13 = registro->at(6);
				book->ratingAvg = registro->at(7);
				book->ratingCount = registro->at(8);
				book->title = registro->at(9);

				switch (j)
				{
				case 0:
					vBooks1->push_back(book);
					break;
				case 1:
					vBooks2->push_back(book);
					break;
				case 2:
					vBooks3->push_back(book);
					break;
				case 3:
					vBooks4->push_back(book);
					break;
				case 4:
					vBooks5->push_back(book);
					break;
				default:
					break;
				}

				//Book* book = books->at(i);
				cout << "authors: ";
				for (unsigned j = 0; j < book->authors->size(); j++)
					cout << book->authors->at(j) << endl;;
				cout << "bestsellersRank: " << book->bestsellersRank << endl;
				cout << "categories: ";
				for (unsigned k = 0; k < book->authors->size(); k++)
					cout << book->categories->at(k) << endl;
				cout << "edition: " << book->edition << endl;
				cout << "id: " << book->id << endl;
				cout << "isbn10: " << book->isbn10 << endl;
				cout << "isbn13: " << book->isbn13 << endl;
				cout << "ratingAvg: " << book->ratingAvg << endl;
				cout << "ratingCount: " << book->ratingCount << endl;
				cout << "title: " << book->title << endl;
			}

			arquivo.seekg(0, arquivo.beg);			
		}

		cout << "tamanho dos vetores: " << vBooks1->size() << endl;
		cout << "tamanho dos vetores: " << vBooks2->size() << endl;
		cout << "tamanho dos vetores: " << vBooks3->size() << endl;
		cout << "tamanho dos vetores: " << vBooks4->size() << endl;
		cout << "tamanho dos vetores: " << vBooks5->size() << endl;

		//PrintListOfBook(vBooks);
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