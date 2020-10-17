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

int main()
{
	int N = 10; //numero de linhas aleatorias a serem trabalhadas
	srand(time(NULL));

	ifstream arquivo;
	arquivo.open("Data/small-teste.csv");

	vector<Book*>* vBooks = new vector<Book*>();
	Lista<int> authorsIds;
	int cont = 0;

	regex regex("\s*(\"[^\"]*\")");

	/*test.erase(0, 1);
	test.erase(test.size() - 1);*/

	if (arquivo.is_open())
	{
		// Guarda tamanho do arquivo em bytes
		arquivo.seekg(0, arquivo.end);
		int tamanhoDoArquivo = arquivo.tellg();
		arquivo.seekg(0, arquivo.beg);

		//while (!arquivo.eof())
		for (int i = 0; i < N; i++)
		{
			//Pega a linha correspondente a um byte aleatorio
			int byteAleatorio = rand() % (tamanhoDoArquivo);
			arquivo.seekg(byteAleatorio);

			string str;
			getline(arquivo, str); //Tirei o "While(getline) pq o número de vezes que ele vai ler linhas aleatórias vai ser definido pelo N
			
				Book* book = new Book();
				stringstream ss(str);

				sregex_iterator iterator(str.begin(), str.end(),regex);
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

				book->authors = formatadorDeString(0, 1, 2, registro);
				book->bestsellersRank = registro->at(1);				
				book->categories = formatadorDeString(2, 1, 2, registro);
				book->edition = registro->at(3);
				book->id = registro->at(4);
				book->isbn10 = registro->at(5);
				book->isbn13 = registro->at(6);
				book->ratingAvg = registro->at(7);
				book->ratingCount = registro->at(8);
				book->title = registro->at(9);

				vBooks->push_back(book);
			

			PrintListOfBook(vBooks);
		}
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