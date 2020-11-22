#pragma once
#include "NoArvVermPreto.h"

class ArvoreVermelhoPreto
{
public:
	NoArvVermPreto* raiz;
	void RotacaoDireita(NoArvVermPreto** raiz, NoArvVermPreto* y);
	void RotacaoEsquerda(NoArvVermPreto** raiz, NoArvVermPreto* x);
	void Insert(NoArvVermPreto** raiz, int info);
	NoArvVermPreto* Busca(int data);
	void InsertAux(NoArvVermPreto** root, NoArvVermPreto* z);
};

