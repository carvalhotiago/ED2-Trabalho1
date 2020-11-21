#pragma once
#include "NoArvB.h"
class ArvoreB
{
public:
	NoArvB* raiz;
	int ordem;
	ArvoreB* criar_arvore(int ordem);
	NoArvB* aloca_no(int ordem);
	void repartir_filho(NoArvB* pai, int i, int ordem);
	void insere_arvore_naocheia(NoArvB* no, char* chave, int NRR, int ordem);
	void inserir_btree(ArvoreB* arv, char* chave, int NRR);
	void libera_arvore(ArvoreB* arv, NoArvB* raiz);
};

