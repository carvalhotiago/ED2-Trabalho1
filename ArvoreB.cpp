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

	this->trocas = 0;
	this->comparacoes = 0;

	this->ordem = ordem;
}

//Função para o ajuste da arvore durante a inserção
void ArvoreB::AjustarArvore(NoArvB* pai, unsigned long long indiceAux, int ordem) 
{
	int aux;	
	NoArvB* noAux1 = new NoArvB;	
	NoArvB* noAux2 = pai->nosFilhos->at(indiceAux);
	noAux1->isFolha = noAux2->isFolha;
	noAux1->nodesNumber = ceil((double)ordem / 2) - 1;

	trocas++;
	for (aux = 0; aux < (int)ceil((double)ordem / 2) - 1; aux++) 
		noAux1->keys->push_back(noAux2->keys->at(static_cast<unsigned __int64>(aux) + (ordem / 2)));
	
	
	if (!noAux2->isFolha)
		for (aux = 0; aux < (int)((ordem + 1) / 2); aux++) 
			noAux1->nosFilhos->push_back(noAux2->nosFilhos->at(static_cast<unsigned __int64>(aux) + (ordem / 2)));

	trocas++;	
	noAux2->nodesNumber = ceil(ordem / 2) - 1;
		
	trocas++;
	for (aux = pai->nodesNumber; aux >= indiceAux + 1; aux--)
		pai->nosFilhos->push_back(pai->nosFilhos->at(aux));	
	
	trocas++;
	pai->nosFilhos->push_back(noAux1);
	
	trocas++;
	pai->keys->push_back(noAux2->keys->at(static_cast<unsigned __int64>((ordem / 2)) - 1));
	pai->nodesNumber++;
}

//Função auxiliar para balanceamento da árvore
void ArvoreB::InserirAux(NoArvB* no, unsigned long long  chave, int ordem) 
{	
	int contadorAux = no->nodesNumber - 1;
	
	if (no->isFolha) 
	{
				
		while (contadorAux >= 0 && (no->keys->at(contadorAux) > chave) > 0)
		{
			comparacoes++;
			no->keys->push_back(no->keys->at(contadorAux));
			contadorAux--;
		}
		
		no->keys->push_back(chave);
		no->nodesNumber++;
	}	
	else 
	{		
		while (contadorAux >= 0 && (no->keys->at(contadorAux) > chave) > 0)
		{
			comparacoes++;
			contadorAux--;
		}

		contadorAux++;

		comparacoes++;
		if (no->nosFilhos->at(contadorAux)->nodesNumber == ordem - 1)
		{	
			AjustarArvore(no, contadorAux, ordem);

			comparacoes++;
			if ((no->keys->at(contadorAux) < chave) < 0)
				contadorAux += 1;
		}
				
		InserirAux(no->nosFilhos->at(contadorAux), chave, ordem);
	}
}

//Função para inserir uma chave na arvore
void ArvoreB::Inserir(unsigned long long  chave) {

	NoArvB* noAux = this->raiz;
	
	if (this->raiz->nodesNumber == 0) {
		this->raiz->keys->push_back(chave);
		this->raiz->nodesNumber++;
	}
	else 
	{		
		comparacoes++;
		if (noAux->nodesNumber == this->ordem - 1)
		{
			NoArvB* noNovo = new NoArvB();
			this->raiz = noNovo;
			noNovo->isFolha = 0;
			noNovo->nodesNumber = 0;
			noNovo->nosFilhos->push_back(noAux);

			AjustarArvore(noNovo, 0, this->ordem);
			InserirAux(noNovo, chave, this->ordem);
		}
		else 
			InserirAux(noAux, chave, this->ordem);
	}
}