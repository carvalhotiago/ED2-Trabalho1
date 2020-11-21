#pragma once
#include "NoArvVermPreto.h"

class ArvoreVermelhoPreto
{
public:
	void TrocaCorDoNo(NoArvVermPreto* no);
	int CorDoNo(NoArvVermPreto* no);
	NoArvVermPreto* RotacaoDireita(NoArvVermPreto* no);
	NoArvVermPreto* RotacaoEsquerda(NoArvVermPreto* no);
	NoArvVermPreto* Insert(NoArvVermPreto* no, int value);
	void InsertRaiz(NoArvVermPreto* no, int value);
	void BalancearArvore(NoArvVermPreto* no);
	NoArvVermPreto* raiz;
};

