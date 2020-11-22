#include "ArvoreVermelhoPreto.h"
#include "NoArvVermPreto.h"
#include <cstddef>

#define PRETO 0
#define VERMELHO 1

void ArvoreVermelhoPreto::TrocaCorDoNo(NoArvVermPreto* no)
{
	//Troca a cor do nó
	if (no->cor == 0)
		no->cor = 1;
	else
		no->cor = 0;

	//Troca a cor do nó a direita
	if (no->dir->cor == 0)
		no->dir->cor = 1;
	else
		no->dir->cor = 0;

	//Troca a cor do nó a esquerda
	if (no->esq->cor == 0)
		no->esq->cor = 1;
	else
		no->esq->cor = 0;
}

NoArvVermPreto* ArvoreVermelhoPreto::RotacaoDireita(NoArvVermPreto* no)
{
	NoArvVermPreto* noAux = no->esq;

	no->esq = noAux->dir;
	noAux->dir = no;
	noAux->cor = no->cor;
	no->cor = VERMELHO;

	return noAux;
}

NoArvVermPreto* ArvoreVermelhoPreto::RotacaoEsquerda(NoArvVermPreto* no)
{
	NoArvVermPreto* noAux = no->dir;

	no->dir = noAux->esq;
	noAux->esq = no;
	noAux->cor = no->cor;
	no->cor = VERMELHO;

	return noAux;
}

NoArvVermPreto* ArvoreVermelhoPreto::Insert(NoArvVermPreto* no, int value)
{
	if (no->info == 0)
	{
		NoArvVermPreto* noAux = new NoArvVermPreto();

		noAux->info = value;
		noAux->dir = NULL;
		noAux->esq = NULL;
		noAux->cor = VERMELHO;

		return noAux;
	}

	if (value < no->info)
		no->esq = Insert(no->esq, value);
	else
		no->dir = Insert(no->dir, value);

	//Rotações
	if (no->esq->cor == PRETO && no->dir->cor == VERMELHO)
		no = RotacaoEsquerda(no);

	if (no->esq->cor == VERMELHO && no->esq->esq->cor == VERMELHO)
		no = RotacaoDireita(no);

	if (no->dir->cor == VERMELHO && no->esq->cor == VERMELHO)
		TrocaCorDoNo(no);

	return no;
}

void ArvoreVermelhoPreto::InsertRaiz(NoArvVermPreto* no, int value)
{
	int aux;

	raiz = Insert(no, value);

	if (raiz != NULL)
		raiz->cor = PRETO;
}


void ArvoreVermelhoPreto::BalancearArvore(NoArvVermPreto* no)
{
	if (no->dir->cor == VERMELHO)
		no = RotacaoEsquerda(no);

	if (no->esq != NULL && no->esq->cor == VERMELHO && no->esq->esq->cor == VERMELHO)
		no = RotacaoDireita(no);

	if (no->dir->cor == VERMELHO && no->esq->cor == VERMELHO)
		TrocaCorDoNo(no);
}