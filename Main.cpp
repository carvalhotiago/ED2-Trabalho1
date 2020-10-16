#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
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
	}
}

int main()
{
	ifstream arquivo;
	arquivo.open("Data/authors-small.csv");	
	
	vector<Book*>* vBooks = new vector<Book*>();
	Lista<int> authorsIds;
	int cont = 0;

	if (arquivo.is_open())
	{
		while (!arquivo.eof())
		{
			string str;
			while (getline(arquivo, str))
			{
				Book* book = new Book();
				stringstream ss(str);
				getline(ss, book->authors,',');
				getline(ss, book->bestsellersRank, ',');
				getline(ss, book->categories ,',');
				getline(ss, book->edition,',');
				getline(ss, book->id,',');
				getline(ss, book->isbn10,',');
				getline(ss, book->isbn13, ',');
				getline(ss, book->ratingAvg, ',');
				getline(ss, book->ratingCount, ',');
				getline(ss, book->title, ',');
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