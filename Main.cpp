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
	for (int i = 0; i < books->size(); i++)
	{
		cout << "authors: " << books->at(i)->authors << endl;
		cout << "bestsellersRank: " << books->at(i)->bestsellersRank << endl;
		cout << "categories: " << books->at(i)->categories << endl;
		cout << "edition: " << books->at(i)->edition << endl;
		cout << "id: " << books->at(i)->id << endl;
		cout << "isbn10: " << books->at(i)->isbn10 << endl;
		cout << "isbn13: " << books->at(i)->isbn13 << endl;
		cout << "ratingAvg: " << books->at(i)->ratingAvg << endl;
		cout << "ratingCount: " << books->at(i)->ratingCount << endl;
		cout << "title: " << books->at(i)->title << endl;
	}
}

string formatadorDeString(int indice, int inicio, int fim, vector<string> *registro)
{
	string text = registro->at(0) = registro->at(0).substr(1, registro->at(0).size() - 2);
	return text;
}

vector<int>* stringToIntArray(string str) {
	vector<int> *array = new vector<int>;
	for (int i = 0; i < str.length(); i++) {
		array->push_back(str[i] - '0');
	}
	return array;
}


int main()
{
	int N; //numero de linhas aleatorias a serem capturadas
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
	arquivo.open("Data/small-teste.csv");

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
		// Guarda tamanho do arquivo em bytes
		arquivo.seekg(0, arquivo.end);
		int tamanhoDoArquivo = arquivo.tellg();
		arquivo.seekg(0, arquivo.beg);

		//Colocar os 5 grupos de conjuntos aleatórios dentro de um vetor só, pra depois repartir esse vetor em 5 vetores de tamanhos iguais
		for (int j = 0; j < 5; j++)
		{
			for (int i = 0; i < valoresDeN.at(0); i++) // falta fazer a lógica para diferentes valores de N
			{
				//Pega a linha correspondente a um byte aleatorio
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

				book->authors = stringToIntArray(formatadorDeString(0, 1, 2, registro));
				book->bestsellersRank = registro->at(1);				
				book->categories = registro->at(2);
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

				arquivo.seekg(0, arquivo.beg);
			}

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