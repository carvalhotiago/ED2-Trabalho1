#include <iostream>
#include <fstream>
#include <string>
#include "No.h"
#include "Lista.h"


using namespace std;
template <typename T>

void main()
{
	ifstream arquivo;
	arquivo.open("Data/authors-small.csv");

	if (arquivo.is_open())
	{
		while (!arquivo.eof())
		{
			string str;
			getline(arquivo, str);
			cout << str << endl;
		}
		arquivo.close();
	}
	else
	{
		cerr << "Erro ao abrir arquivo!" << endl;
		exit(1);
	}

	cout << "Programa encerrado com sucesso!" << endl;

	int x = 3, y = 5, z = 9;
	Lista<int>* inteiros = new Lista<int>();
	inteiros->Insere(x);
	inteiros->Insere(y);
	inteiros->Insere(z);
}