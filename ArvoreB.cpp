#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ArvoreB.h"

//Construtor da arvore B
ArvoreB::ArvoreB(int ordem)
{
	NoArvB* raiz = NULL;

	this->raiz = new NoArvB;
	this->raiz->keys = new vector<unsigned long long >;
	this->raiz->isFolha = 1;
	this->raiz->nodesNumber = 0;
	this->raiz->nosFilhos = new vector<NoArvB*>;

	this->ordem = ordem;
}

//Função para o ajuste da arvore durante a inserção
void ArvoreB::AjustarArvore(NoArvB* pai, unsigned long long  i, int ordem) 
{
	int j;	
	NoArvB* z = new NoArvB;	
	NoArvB* y = pai->nosFilhos->at(i);
	z->isFolha = y->isFolha;
	z->nodesNumber = ceil((double)ordem / 2) - 1;
	
	for (j = 0; j < (int)ceil((double)ordem / 2) - 1; j++) 
		z->keys->push_back(y->keys->at(static_cast<unsigned __int64>(j) + (ordem / 2)));
	
	
	if (!y->isFolha) 
		for (j = 0; j < (int)((ordem + 1) / 2); j++) 
			z->nosFilhos->push_back(y->nosFilhos->at(static_cast<unsigned __int64>(j) + (ordem / 2)));
	
	y->nodesNumber = ceil(ordem / 2) - 1;
		
	for (j = pai->nodesNumber; j >= i + 1; j--)
		pai->nosFilhos->push_back(pai->nosFilhos->at(j));	
	
	pai->nosFilhos->push_back(z);
	
	pai->keys->push_back(y->keys->at(static_cast<unsigned __int64>((ordem / 2)) - 1));
	pai->nodesNumber++;
}

//Função auxiliar para balanceamento da árvore
void ArvoreB::InserirAux(NoArvB* no, unsigned long long  chave, int ordem) 
{	
	int i = no->nodesNumber - 1;
	
	if (no->isFolha) 
	{
				
		while (i >= 0 && (no->keys->at(i) > chave) > 0)
		{
			no->keys->push_back(no->keys->at(i));
			i--;
		}
		
		no->keys->push_back(chave);
		no->nodesNumber++;
	}	
	else 
	{		
		while (i >= 0 && (no->keys->at(i) > chave) > 0)
			i--;

		i++;
				
		if (no->nosFilhos->at(i)->nodesNumber == ordem - 1)
		{	
			AjustarArvore(no, i, ordem);
			
			if ((no->keys->at(i) < chave) < 0)
				i = i + 1;
		}
				
		InserirAux(no->nosFilhos->at(i), chave, ordem);
	}
}

//Função para inserir uma chave na arvore
void ArvoreB::Inserir(unsigned long long  chave) {

	NoArvB* r = this->raiz;
	
	if (this->raiz->nodesNumber == 0) {
		this->raiz->keys->push_back(chave);
		this->raiz->nodesNumber++;
	}
	else 
	{		
		if (r->nodesNumber == this->ordem - 1) 
		{
			NoArvB* s = new NoArvB();
			this->raiz = s;
			s->isFolha = 0;
			s->nodesNumber = 0;
			s->nosFilhos->push_back(r);

			AjustarArvore(s, 0, this->ordem);
			InserirAux(s, chave, this->ordem);
		}
		else 
			InserirAux(r, chave, this->ordem);
	}
}