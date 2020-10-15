#include <iostream>
#include <fstream>
#include <string>


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
	return 0;
}