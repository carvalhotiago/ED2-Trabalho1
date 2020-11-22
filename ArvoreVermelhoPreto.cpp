#include "ArvoreVermelhoPreto.h"
#include "NoArvVermPreto.h"
#include <cstddef>

#define PRETO 0
#define VERMELHO 1

void ArvoreVermelhoPreto::RotacaoDireita(NoArvVermPreto** raiz, NoArvVermPreto* y)
{
	NoArvVermPreto* x = y->esq;
	y->esq = x->dir;
	if (x->dir != NULL)
		x->dir->pai = y;
	x->pai = y->pai;
	if (x->pai == NULL)
		(*raiz) = x;
	else if (y == y->pai->esq)
		y->pai->esq = x;
	else y->pai->dir = x;
	x->dir = y;
	y->pai = x;
}

void ArvoreVermelhoPreto::RotacaoEsquerda(NoArvVermPreto** raiz, NoArvVermPreto* x)
{
	//y stored pointer of right child of x
	NoArvVermPreto* y = x->dir;

	//store y's esq subtree's pointer as x's dir child
	x->dir = y->esq;

	//update pai pointer of x's dir
	if (x->dir != NULL)
		x->dir->pai = x;

	//update y's pai pointer
	y->pai = x->pai;

	// if x's pai is null make y as root of tree
	if (x->pai == NULL)
		(*raiz) = y;

	// store y at the place of x
	else if (x == x->pai->esq)
		x->pai->esq = y;
	else    x->pai->dir = y;

	// make x as esq child of y
	y->esq = x;

	//update pai pointer of x
	x->pai = y;
}

// Utility function to insert newly node in RedBlack tree
void ArvoreVermelhoPreto::Insert(NoArvVermPreto** raiz, int info)
{
	// Allocate memory for new node
	NoArvVermPreto* z = new NoArvVermPreto;
	z->info = info;
	z->esq = z->dir = z->pai = NULL;

	//if root is null make z as root
	if (raiz == NULL)
	{
		z->cor = PRETO;
		(*raiz) = z;
	}
	else
	{
		NoArvVermPreto* y = NULL;
		NoArvVermPreto* x = (*raiz);

		// Follow standard BST insert steps to first insert the node
		while (x != NULL)
		{
			y = x;
			if (z->info < x->info)
				x = x->esq;
			else
				x = x->dir;
		}
		z->pai = y;
		if (z->info > y->info)
			y->dir = z;
		else
			y->esq = z;
		z->cor = VERMELHO;

		// call insertFixUp to fix reb-black tree's property if it
		// is voilated due to insertion.
		InsertAux(raiz, z);
	}
}

NoArvVermPreto* ArvoreVermelhoPreto::Busca(int data) 
{
	NoArvVermPreto *temp = raiz;
	if (temp == nullptr)
		return NULL;

	while (temp) {
		if (data == temp->info) 
			return temp;
		else if (data < temp->info)
			temp = temp->esq;
		else 
			temp = temp->dir;
	}

	return NULL;
}

void ArvoreVermelhoPreto::InsertAux(NoArvVermPreto** root, NoArvVermPreto* z)
{
	// iterate until z is not the root and z's pai cor is red
	while (z != *root && z != (*root)->esq && z != (*root)->dir && z->pai->cor == 'R')
	{
		NoArvVermPreto* y;

		// Find uncle and store uncle in y
		if (z->pai && z->pai->pai && z->pai == z->pai->pai->esq)
			y = z->pai->pai->dir;
		else
			y = z->pai->pai->esq;

		// If uncle is RED, do following
		// (i)  Change cor of pai and uncle as BLACK
		// (ii) Change cor of grandpai as RED
		// (iii) Move z to grandpai
		if (!y)
			z = z->pai->pai;
		else if (y->cor == VERMELHO)
		{
			y->cor = PRETO;
			z->pai->cor = PRETO;
			z->pai->pai->cor = VERMELHO;
			z = z->pai->pai;
		}

		// Uncle is BLACK, there are four cases (LL, LR, RL and RR)
		else
		{
			// esq-esq (LL) case, do following
			// (i)  Swap cor of pai and grandpai
			// (ii) dir Rotate Grandpai
			if (z->pai == z->pai->pai->esq &&
				z == z->pai->esq)
			{
				char ch = z->pai->cor;
				z->pai->cor = z->pai->pai->cor;
				z->pai->pai->cor = ch;
				RotacaoDireita(root, z->pai->pai);
			}

			// esq-dir (LR) case, do following
			// (i)  Swap cor of current node  and grandpai
			// (ii) esq Rotate pai
			// (iii) dir Rotate Grand pai
			if (z->pai && z->pai->pai && z->pai == z->pai->pai->esq &&
				z == z->pai->dir)
			{
				char ch = z->cor;
				z->cor = z->pai->pai->cor;
				z->pai->pai->cor = ch;
				RotacaoEsquerda(root, z->pai);
				RotacaoDireita(root, z->pai->pai);
			}

			// dir-dir (RR) case, do following
			// (i)  Swap cor of pai and grandpai
			// (ii) esq Rotate Grandpai
			if (z->pai && z->pai->pai &&
				z->pai == z->pai->pai->dir &&
				z == z->pai->dir)
			{
				char ch = z->pai->cor;
				z->pai->cor = z->pai->pai->cor;
				z->pai->pai->cor = ch;
				RotacaoEsquerda(root, z->pai->pai);
			}

			// dir-esq (RL) case, do following
			// (i)  Swap cor of current node  and grandpai
			// (ii) dir Rotate pai
			// (iii) esq Rotate Grand pai
			if (z->pai && z->pai->pai && z->pai == z->pai->pai->dir &&
				z == z->pai->esq)
			{
				char ch = z->cor;
				z->cor = z->pai->pai->cor;
				z->pai->pai->cor = ch;
				RotacaoDireita(root, z->pai);
				RotacaoEsquerda(root, z->pai->pai);
			}
		}
	}
	(*root)->cor = PRETO; //keep root always black
}