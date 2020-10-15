#include <iostream>
#include <fstream>
#include <string>
#include "No.h"
#include "Lista.h"

using namespace std;

int main()
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

	int x = 2;
	int* px = &x;
	Lista<int>* inteiros = new Lista<int>();
	inteiros->Insere(px);


	return 0;
}