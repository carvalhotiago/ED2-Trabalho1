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
#include <chrono>
#include "ArvoreVermelhoPreto.h"
#include "ArvoreB.h"
typedef std::chrono::high_resolution_clock Clock;

using namespace std;

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

int main()
{
	auto t1 = Clock::now();

	//Setta a semente para o valor do tempo atual
	srand(time(0));

	//Abre arquivo de saida, que irá armazenar estatísticas do desempenho de toda a execução
	ofstream saidaBusca;
	saidaBusca.open("saidaBusca.txt");
	if (saidaBusca.is_open())
		cout << "Arquivo saida insercao aberto com sucesso." << endl;
	else
		cout << "Erro no arquivo saida insercao." << endl;

	//Abre arquivo de saida, que irá armazenar estatísticas do desempenho de toda a execução
	ofstream saidaInsercao;
	saidaInsercao.open("saidaInsercao.txt");
	if (saidaInsercao.is_open())
		cout << "Arquivo saida busca aberto com sucesso." << endl;
	else
		cout << "Erro no arquivo saida busca." << endl;

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

	if (arquivo.is_open())
	{
		// Guarda tamanho do arquivo em bytes
		arquivo.seekg(0, arquivo.end);
		unsigned int tamanhoDoArquivo = arquivo.tellg();
		arquivo.seekg(0, arquivo.beg);
		//Arvore vermelho e preto
		ArvoreVermelhoPreto* arv = new ArvoreVermelhoPreto;
		vector<string> *nosArvoreVermPreto = new vector<string>;
		//Arvore B
		//ArvoreB *arvoreB = new ArvoreB(2); 

		for (int i = 0; i < N; i++)
		{
			auto now = Clock::now();
			long diff = chrono::duration_cast<std::chrono::seconds>(now - t1).count();		

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

			//Seção referente à árvores	
			string idLivro = book->id;

			stringstream idBookInt(idLivro);
			unsigned long long idBook = 0;
			idBookInt >> idBook;

			//arvoreB->Insert(idBook);
			arv->Inserir(idLivro);
			nosArvoreVermPreto->push_back(idLivro);		

			delete book;
			delete registro;
		}	

		for (int i = 0; i < nosArvoreVermPreto->size(); i++)
			arv->BuscaNaArvore(nosArvoreVermPreto->at(i));

		saidaBusca << "Estatisticas da busca em arvore vermelho-preto: " << endl;
		saidaBusca << "Total de comparacoes feitas nas busca = " << arv->numComparacoesBusca << endl;
		saidaBusca << "Total de trocas nas busca = " << arv->numTrocasBusca << endl;
				
		saidaInsercao << "Estatisticas da insercao em arvore vermelho-preto: " << endl;
		saidaInsercao << "Total de rotacoes = " << arv->numRotacoes << endl;
		saidaInsercao << "Total de trocas de cor = " << arv->numTrocasDeCor <<endl;

		arquivo.seekg(0, arquivo.beg);
		arquivo.close();
	}
	else
	{
		cerr << "Erro ao abrir arquivo!" << endl;
		exit(1);
	}

	auto t2 = Clock::now();
	long tempo = chrono::duration_cast<std::chrono::seconds>(t2 - t1).count();

	saidaInsercao << "Execucao com N = " << N << endl;
	saidaInsercao << "Tempo total: " << tempo << "(s)\n";

	saidaBusca << "Execucao com N = " << N << endl;
	saidaBusca << "Tempo total: " << tempo << "(s)\n";

	saidaInsercao.close();
	cout << "Programa encerrado com sucesso!" << endl;

	return 0;
}