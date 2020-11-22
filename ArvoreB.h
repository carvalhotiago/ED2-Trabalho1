#pragma once
#include "NoArvB.h"
class ArvoreB
{
public:
	NoArvB* raiz;
	int ordem;
	ArvoreB* CriaArvore(int ordem);
	NoArvB* AlocaNo(int ordem);
	void ReparteArvoreNoFilho(NoArvB* pai, int i, int ordem);
	void InsertKey(NoArvB* no, int chave, int ordem);
	void Insert(ArvoreB* arv, int chave);
};

