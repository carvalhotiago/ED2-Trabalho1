#pragma once
#include "NoArvB.h"

class ArvoreB
{
public:
	int ordem;
	NoArvB* raiz;
	ArvoreB(int ordem);
	void Inserir(unsigned long long chave);
	void InserirAux(NoArvB* no, unsigned long long chave, int ordem);
	void AjustarArvore(NoArvB* pai, unsigned long long i, int ordem);
};

