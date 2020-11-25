#pragma once
#include "NoArvB.h"

class ArvoreB
{
public:
	NoArvB* raiz;
	int ordem;
	int trocas;
	int comparacoes;
	ArvoreB(int ordem);
	void Inserir(unsigned long long chave);
	void InserirAux(NoArvB* no, unsigned long long chave, int ordem);
	void AjustarArvore(NoArvB* pai, unsigned long long indiceAux, int ordem);
};

