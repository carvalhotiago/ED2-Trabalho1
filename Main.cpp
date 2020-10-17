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
	ifstream arquivo;
	arquivo.open("Data/teste.txt");

	vector<Book*>* vBooks = new vector<Book*>();
	int cont = 0;

	regex regex("\s*(\"[^\"]*\")");

	/*test.erase(0, 1);
	test.erase(test.size() - 1);*/

	if (arquivo.is_open())
	{
		while (!arquivo.eof())
		{
			string str;
			while (getline(arquivo, str))
			{
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

				book->authors = stringToIntArray(formatadorDeString(0, 1, 2, registro));
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
			}

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