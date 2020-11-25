#pragma once
#include "NoArvB.h"
class ArvoreB
{
public:
	int ordem;
	NoArvB* raiz;
	ArvoreB(int ordem);
	void Insert(ArvoreB* arv, unsigned long long chave);
	void InsertKey(NoArvB* no, unsigned long long chave, int ordem);
	void Insert(unsigned long long chave);
	void ReparteArvoreNoFilho(NoArvB* pai, unsigned long long i, int ordem);
};

