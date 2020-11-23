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
#include "BooksHashTable.h"
#include "AuthorsHashTable.h"
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;

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

//Printa o título de cada livro de uma lista de livros
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

//Divide uma string contendo uma lista de inteiros em um vector de inteiros, delimitados pelo segundo parâmetro (delimiter)
vector<int>* split(const string& s, char delimiter) {
	vector<int>* tokens = new vector<int>;
	string token;
	istringstream tokenStream(s);
	while (getline(tokenStream, token, delimiter)) {
		tokens->push_back(stoi(token));
	}
	return tokens;
}

Author* GetAuthorById(int id)
{
	string linha;
	string idAutor;
	string nomeAutor;

	vector<Author>* listaTeste = new vector<Author>;

	ifstream autores;
	autores.open("Data/authors-grande.csv");

	if (autores.is_open())
	{
		getline(autores, linha);

		while (getline(autores, linha))
		{
			stringstream ss(linha);
			getline(ss, idAutor, ',');
			getline(ss, nomeAutor, ',');

			idAutor = idAutor.substr(1, idAutor.size() - 2);
			nomeAutor = nomeAutor.substr(1, nomeAutor.size() - 2);

			long convertedId = atol(idAutor.c_str());

			Author* author = new Author(nomeAutor);
			author->authorName = nomeAutor;

			listaTeste->push_back(*author);

			if (id == convertedId)
				return author;
		}
		return new Author("Desconhecido");
	}
	else
	{
		cout << "Erro ao abrir o arquivo!" << endl;
	}
}

vector<Author*> GetAuthorsFromBook(Book* book)
{
	vector<Author*> autores;

	for (int i = 0; i < book->authors->size(); i++)
	{
		Author* autor = GetAuthorById(book->authors->at(i));
		autores.push_back(autor);
	}

	return autores;
}

int main()
{
	auto t1 = Clock::now();

	//Setta a semente para o valor do tempo atual
	srand(time(0));

	//Abre arquivo de saida, que irá armazenar estatísticas do desempenho de toda a execução
	ofstream saida;
	saida.open("saida.txt");
	if (saida.is_open())
		cout << "Arquivo saida aberto com sucesso." << endl;
	else
		cout << "Erro no arquivo saida." << endl;

	//Abre o arquivo de entrada com informações dos números N
	ifstream entrada;
	entrada.open("Data/entrada.txt");

	//Numero de livros que serao lidos
	int N;
	entrada >> N;

	entrada.close();

	//Lê dataset
	ifstream arquivo;
	arquivo.open("Data/dataset_simp_sem_descricao.csv");

	//Expressão regular para captura dos grupos de informações das linhas
	regex regex("\s*(\"[^\"]*\")");

	BooksHashTable* booksHashTable = new BooksHashTable(N * 1.3);
	AuthorsHashTable* authorsHashTable = new AuthorsHashTable(N * 1.3);

	if (arquivo.is_open())
	{
		// Guarda tamanho do arquivo em bytes
		arquivo.seekg(0, arquivo.end);
		unsigned int tamanhoDoArquivo = arquivo.tellg();
		arquivo.seekg(0, arquivo.beg);

		for (int i = 0; i < N; i++)
		{
			if (i % 1000 == 0) cout << "Gerando amostra " << i << endl;

			// Pega a linha correspondente a um byte aleatorio
			int byteAleatorio = (rand() * rand()) % (tamanhoDoArquivo - 10000000);
			//cout << byteAleatorio << " ";
			arquivo.seekg(byteAleatorio);
			//cout << "byteAleatorio " << byteAleatorio << endl;

			//Primeiro dá um getline para ir pro início da linha seguinte à linha aleatória em que caiu, e então dá o getline pra pegar a linha que nos interessa
			string dump;
			string str;
			getline(arquivo, dump);
			getline(arquivo, str);

			//Existem casos de string que quebram a linha na propriedade título e quebram o código na hora de armazenar os valores na variável book, por isso
			//estamos utilizando apenas strings que começam ou terminam com aspas para garantir que não leremos algum resto de quebra de linha de um título nesse estado
			while (str.empty() || str.back() != '"' || str.at(0) != '"')
			{
				getline(arquivo, str);
			}

			Book* book = new Book();
			stringstream ss(str);

			//Itera sobre a linha recuperada, capturando os grupos de informação através de RegEx
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

			if (registro->at(0) != "")
			{
				string text = registro->at(0) = registro->at(0).substr(1, registro->at(0).size() - 2);
				stringstream iss(text);
				vector<int>* authorsIds = split(text, ',');
				book->authors = authorsIds;
			}

			if (registro->at(2) != "")
			{
				string text = registro->at(2) = registro->at(2).substr(1, registro->at(2).size() - 2);
				vector<int>* categories = split(text, ',');
				book->categories = categories;
			}

			book->bestsellersRank = registro->at(1);
			book->edition = registro->at(3);
			book->id = registro->at(4);
			book->isbn10 = registro->at(5);
			book->isbn13 = registro->at(6);
			book->ratingAvg = registro->at(7);
			book->ratingCount = registro->at(8);
			book->title = registro->at(9);

			arquivo.seekg(0, arquivo.beg);

			if (booksHashTable->Insert(book)) {
				vector<Author*> autores = GetAuthorsFromBook(book);
				for (Author* autor : autores)
				{
					authorsHashTable->Insert(autor);
				}
			}
			else
				i--; //essa iteracao nao foi valida pois o livro lido eh repetido, entao le outro
		}

		//booksHashTable->PrintHashTable();
		cout << "\n->GetNumeroDeColisoes(): " << booksHashTable->GetNumeroDeColisoes() << "\n\n";

		authorsHashTable->PrintAutores(authorsHashTable->GetListaDeAutoresOrdenadaPorAppearances());

		arquivo.seekg(0, arquivo.beg);
		arquivo.close();
	}
	else
	{
		cerr << "Erro ao abrir arquivo!" << endl;
		exit(1);
	}


	auto t2 = Clock::now();
	long tempo = chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

	saida << tempo;

	saida.close();
	cout << "Programa encerrado com sucesso!" << endl;

	return 0;
}