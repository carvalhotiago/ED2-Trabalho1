#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "No.h"
#include "Lista.h"
#include "Book.h"

using namespace std;

int main()
{
	ifstream arquivo;
	arquivo.open("Data/authors-small.csv");
	
	Lista<Book> *books = new Lista<Book>;
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
			}			

			if (cont < 1)
			{
				books->PrintListOfBook(*books);
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

	int x = 2;
	int* px = &x;
	Lista<int>* inteiros = new Lista<int>();
	inteiros->Insere(px);


	return 0;
}