#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "No.h"
#include "Lista.h"
#include "Book.h"

using namespace std;

//template <typename T>
//void PrintListOfBook(vector<T*> *books)
//{
//	cout << "authors: " << books->at(1).authors << endl;
//}

int main()
{
	ifstream arquivo;
	arquivo.open("Data/authors-small.csv");
	
	Lista<Book> *books = new Lista<Book>;
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
				books->Insere(book);
				vBooks->push_back(book);
			}			

			for (int i = 0; i < vBooks->size(); i++)
			{
				cout << "authors: " << vBooks->at(i)->authors << endl;
				cout << "bestsellersRank: " << vBooks->at(i)->bestsellersRank << endl;
			}
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