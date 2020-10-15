#include <fstream>
#include <string>
#include <iostream>
#include "Source.h"
#include <cstdlib>
#include <stdlib.h>
#include "Quicksort.h"

using namespace std;


int WriteFile();
int ReadFile();

//int main()
//{
//	//int x = WriteFile();
//	//int y = ReadFile();
//	//int* vet = new int[5];
//
//	int balance[5] = { 5,4,3,2,1 };
//	int* p = balance;
//
//	Quicksort* quicksort = new Quicksort();
//	quicksort->QuickSort(p, 0, 4);
//
//	for (int i = 0; i < 5; i++) {
//		cout << balance[i];
//	}
//
//	return 0;
//}

int ReadFile()
{
	ifstream arquivo;
	arquivo.open("authors-small.csv");

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
	return 0;
}

int WriteFile()
{
	ofstream arquivo;
	arquivo.open("teste.txt");

	if (arquivo.is_open())
	{
		arquivo << "ED II" << endl;
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
