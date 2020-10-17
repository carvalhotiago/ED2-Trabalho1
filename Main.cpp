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

int main()
{
	ifstream arquivo;
	arquivo.open("Data/teste.txt");

	vector<Book*>* vBooks = new vector<Book*>();
	Lista<int> authorsIds;
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

				sregex_iterator iterator(str.begin(), str.end(), regex);
				vector<string>* teste = new vector<string>;
				sregex_iterator end;

				while (iterator != end)
				{
					for (unsigned i = 0; i < iterator->size(); i++)
					{
						string a;
						getline((stringstream)(*iterator)[i], a);
						teste->push_back(a);
					}
					iterator++;
				}

				book->authors = teste->at(0);
				book->bestsellersRank = teste->at(1);
				book->categories = teste->at(2);
				book->edition = teste->at(3);
				book->id = teste->at(4);
				book->isbn10 = teste->at(5);
				book->isbn13 = teste->at(6);
				book->ratingAvg = teste->at(7);
				book->ratingCount = teste->at(8);
				book->title = teste->at(9);

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