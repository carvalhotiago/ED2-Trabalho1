#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "ArvoreVermelhoPreto.h"

using namespace std;

ArvoreVermelhoPreto::ArvoreVermelhoPreto()
{
	raiz = nullptr;
	numRotacoes = 0;
	numTrocasDeCor = 0;
	numTrocasBusca = 0;
	numComparacoesBusca = 0;
}


//Insere um novo no na arvore baseado na string com a chave do livro
void ArvoreVermelhoPreto::Inserir(string id) {

	stringstream idBookInt(id);
	unsigned long long idBook = 0;
	idBookInt >> idBook;

	if (raiz == nullptr)
	{
		raiz = new NoArvVermPreto();
		raiz->info = idBook;
		raiz->pai = nullptr;
		raiz->cor = "PRETO";
	}
	else
	{
		NoArvVermPreto* noAux = raiz;
		NoArvVermPreto* noInsert = new NoArvVermPreto();

		noInsert->info = idBook;

		while (noAux != nullptr)
		{
			if (noAux->info > idBook)
			{
				if (noAux->esq == nullptr)
				{
					noAux->esq = noInsert;
					noInsert->cor = "VERMELHO";
					noInsert->pai = noAux;
					break;
				}
				else
					noAux = noAux->esq;
			}
			else
			{
				if (noAux->dir == nullptr)
				{
					noAux->dir = noInsert;
					noInsert->cor = "VERMELHO";
					noInsert->pai = noAux;
					break;
				}
				else
					noAux = noAux->dir;
			}
		}

		InserirAux(noInsert);
	}
}

//Função auxiliar para balanceamento da árvore durante a inserção
void ArvoreVermelhoPreto::InserirAux(NoArvVermPreto* no)
{
	while (no->pai->cor == "VERMELHO")
	{
		NoArvVermPreto* noAvo = no->pai->pai;
		NoArvVermPreto* noAux = raiz;

		if (no->pai == noAvo->esq)
		{
			if (noAvo->dir)
				noAux = noAvo->dir;
			if (noAux->cor == "VERMELHO")
			{
				no->pai->cor = "PRETO";
				noAux->cor = "PRETO";
				noAvo->cor = "VERMELHO";
				numTrocasDeCor++;
				if (noAvo->info != raiz->info)
					no = noAvo;
				else
					break;
			}
			else if (no == noAvo->esq->dir) {
				RotacaoEsquerda(no->pai);
				numRotacoes++;
			}
			else 
			{
				no->pai->cor = "PRETO";
				noAvo->cor = "VERMELHO";
				numTrocasDeCor++;
				RotacaoDireita(noAvo);
				numRotacoes++;
				if (noAvo->info != raiz->info)
					no = noAvo;
				else
					break;
			}
		}
		else
		{
			if (noAvo->esq)
				noAux = noAvo->esq;

			if (noAux->cor == "VERMELHO")
			{
				no->pai->cor = "PRETO";
				noAux->cor = "PRETO";
				noAvo->cor = "VERMELHO";
				numTrocasDeCor++;
				if (noAvo->info != raiz->info)
					no = noAvo;
				else
					break;
			}
			else if ((noAvo->dir) && no == noAvo->dir->esq)
			{
				RotacaoDireita(no->pai);
				numRotacoes++;
			}
			else
			{
				no->pai->cor = "PRETO";
				noAvo->cor = "VERMELHO";
				numTrocasDeCor++;
				RotacaoEsquerda(noAvo);
				numRotacoes++;
				if (noAvo->info != raiz->info)
					no = noAvo;
				else
					break;
			}
		}
	}

	raiz->cor = "PRETO";
}

//Função para realizar a busca dentro da árvore
NoArvVermPreto* ArvoreVermelhoPreto::BuscaNaArvore(string id)
{
	stringstream idBookInt(id);
	unsigned long long idBook = 0;
	idBookInt >> idBook;

	NoArvVermPreto* noAux = raiz;
	if (noAux == nullptr)
		return nullptr;

	while (noAux)
	{
		numComparacoesBusca++;
		if (idBook == noAux->info)
			return noAux;
		else
		{
			numComparacoesBusca++;
			if (idBook < noAux->info)
				noAux = noAux->esq;
			else
				noAux = noAux->dir;
		}

		numTrocasBusca++;
	}

	return nullptr;
}

//Função que faz a rotação a esquerda durante o balanceamento
void ArvoreVermelhoPreto::RotacaoEsquerda(NoArvVermPreto* no)
{
	NoArvVermPreto* noAux = new NoArvVermPreto();

	if (no->dir->esq)
		noAux->dir = no->dir->esq;

	noAux->esq = no->esq;
	noAux->info = no->info;
	noAux->cor = no->cor;
	
	no->info = no->dir->info;
	no->cor = no->dir->cor;
	no->esq = noAux;

	if (noAux->esq)
		noAux->esq->pai = noAux;
	if (noAux->dir)
		noAux->dir->pai = noAux;

	noAux->pai = no;

	if (no->dir->dir)
		no->dir = no->dir->dir;
	else
		no->dir = nullptr;

	if (no->dir)
		no->dir->pai = no;
}

//Função que faz a rotação a direita durante o balanceamento
void ArvoreVermelhoPreto::RotacaoDireita(NoArvVermPreto* no)
{
	NoArvVermPreto* noAux = new NoArvVermPreto();

	if (no->esq->dir)
		noAux->esq = no->esq->dir;

	noAux->dir = no->dir;
	noAux->info = no->info;
	noAux->cor = no->cor;

	no->info = no->esq->info;
	no->cor = no->esq->cor;
	no->dir = noAux;

	if (noAux->esq)
		noAux->esq->pai = noAux;
	if (noAux->dir)
		noAux->dir->pai = noAux;

	noAux->pai = no;

	if (no->esq->esq)
		no->esq = no->esq->esq;
	else
		no->esq = nullptr;

	if (no->esq)
		no->esq->pai = no;
}