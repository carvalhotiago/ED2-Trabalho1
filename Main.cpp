#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>
#include "No.h"
#include "Lista.h"
#include "Book.h"
#include "Bubblesort.h"
#include "Quicksort.h"

using namespace std;

template <typename T>
void PrintListOfBook(vector<T*>& books)
{
	for (int i = 0; i < books.size(); i++)
	{
		Book* book = books.at(i);
		for (int j = 0; j < book->authors->size(); j++)
			cout << "authors: " << book->authors->at(j) << endl;
		cout << "bestsellersRank: " << book->bestsellersRank << endl;
		for (int k = 0; k < book->categories->size(); k++)
			cout << "categories: " << book->categories->at(k) << endl;
		cout << "edition: " << book->edition << endl;
		cout << "id: " << book->id << endl;
		cout << "isbn10: " << book->isbn10 << endl;
		cout << "isbn13: " << book->isbn13 << endl;
		cout << "ratingAvg: " << book->ratingAvg << endl;
		cout << "ratingCount: " << book->ratingCount << endl;
		cout << "title: " << book->title << endl;
	}
}

//Printa o t�tulo de cada livro de uma lista de livros
template <typename T>
void PrintBookTitles(vector<T*>& books)
{
	for (int i = 0; i < books.size(); i++)
	{
		Book* book = books.at(i);
		cout << book->title << endl;
	}
	cout << endl;
}

//Divide uma string contendo uma lista de inteiros em um vector de inteiros, delimitados pelo segundo par�metro (delimiter)
vector<int>* split(const string& s, char delimiter) {
	vector<int>* tokens = new vector<int>;
	string token;
	istringstream tokenStream(s);
	while (getline(tokenStream, token, delimiter)) {
		tokens->push_back(stoi(token));
	}
	return tokens;
}

int main()
{
	//Setta a semente para o valor do tempo atual
	srand(time(0));

	//Abre o arquivo de entrada com informa��es dos n�meros N
	ifstream entrada;
	entrada.open("Data/entrada.txt");

	//Primeiro par�metro do arquivo de entrada
	int numeroDeEntradas;
	entrada >> numeroDeEntradas;

	//L� e armazena os valores de N (tamanho das amostras) do arquivo de entrada
	vector<int> valoresDeN;
	string str;
	string linhaIgnorada;
	getline(entrada, linhaIgnorada);
	while (getline(entrada, str)) {
		valoresDeN.push_back(stoi(str));
	}
	entrada.close();

	//L� dataset
	ifstream arquivo;
	arquivo.open("Data/dataset_simp_sem_descricao.csv");

	//Express�o regular para captura dos grupos de informa��es das linhas
	regex regex("\s*(\"[^\"]*\")");

	if (arquivo.is_open())
	{
		// Guarda tamanho do arquivo em bytes
		arquivo.seekg(0, arquivo.end);
		unsigned int tamanhoDoArquivo = arquivo.tellg();
		arquivo.seekg(0, arquivo.beg);

		// Para cada um dos valores de N passados
		for (int k = 0; k < valoresDeN.size(); k++)
		{
			//Estrutura que ir� armazenar os 5 vetores de livros preenchidos aleatoriamente
			vector<vector<Book*>*> listaDeVetores;

			// Gera 5 amostras de entradas aleat�rias do dataset
			for (unsigned j = 0; j < 5; j++)
			{
				//Estrutura que ir� armazenar cada vetor de livros gerado
				vector<Book*>* vet = new vector<Book*>();

				//Cada uma das 5 amostras geradas ter� o mesmo tamanho, que � um dos Ns passados
				for (int i = 0; i < valoresDeN.at(k); i++)
				{
					// Pega a linha correspondente a um byte aleatorio
					unsigned int byteAleatorio = (rand() * rand()) % (tamanhoDoArquivo - 5000); // esse desconto no tamanhoDoArquivo evita com que a a linha aleat�ria seja a �ltima, o que causaria erro j� que n�o h� linha seguinte � �ltima
					arquivo.seekg(byteAleatorio);
					cout << "byteAleatorio " << byteAleatorio << endl;

					//Primeiro d� um getline para ir pro in�cio da linha seguinte � linha aleat�ria em que caiu, e ent�o d� o getline pra pegar a linha que nos interessa
					string dump;
					string str;
					getline(arquivo, dump);
					getline(arquivo, str);

					Book* book = new Book();
					stringstream ss(str);

					//Itera sobre a linha recuperada, capturando os grupos de informa��o atrav�s de RegEx
					sregex_iterator iterator(str.begin(), str.end(), regex);
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

					//Parsea as informa��es e popula um objeto Book que ser� adicionado ao vetor de tamanho N
					string text = registro->at(0) = registro->at(0).substr(1, registro->at(0).size() - 2);
					stringstream iss(text);
					vector<int>* authorsIds = split(text, ',');
					text = registro->at(2) = registro->at(2).substr(1, registro->at(2).size() - 2);
					vector<int>* categories = split(text, ',');

					book->authors = authorsIds;
					book->bestsellersRank = registro->at(1);
					book->categories = categories;
					book->edition = registro->at(3);
					book->id = registro->at(4);
					book->isbn10 = registro->at(5);
					book->isbn13 = registro->at(6);
					book->ratingAvg = registro->at(7);
					book->ratingCount = registro->at(8);
					book->title = registro->at(9);

					vet->push_back(book);
					arquivo.seekg(0, arquivo.beg);
				}

				//Ao terminar de gerar o vetor com N livros aleat�rios, o coloca na lista que vai guardar as 5 amostras
				listaDeVetores.push_back(vet);
			}


			//PrintBookTitles(*listaDeVetores.at(4));

			//Chama o algoritmo de ordena��o BubbleSort para cada um dos vetores da lista de amostras
			/*Bubblesort bs;
			for (int i = 0; i < listaDeVetores.size(); i++)
			{
				vector<Book*>* vectorAtual = listaDeVetores.at(i);
				cout << "i: " << i << endl;

				bs.BubbleSort(*vectorAtual, vectorAtual->size());
			}*/

			//Chama o algoritmo de ordena��o QuickSort para cada um dos vetores da lista de amostras
			Quicksort quick;
			for (int i = 0; i < listaDeVetores.size(); i++)
			{
				vector<Book*>* vectorAtual = listaDeVetores.at(i);
				cout << "i: " << i << endl;

				quick.Execute(*vectorAtual, 0, vectorAtual->size());
			}

			
			//PrintBookTitles(*listaDeVetores.at(4));
		}
		arquivo.seekg(0, arquivo.beg);
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