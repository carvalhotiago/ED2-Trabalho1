#pragma once
#include <string>
#include "NoArvVermPreto.h"

using namespace std;

class ArvoreVermelhoPreto
{

public:
    ArvoreVermelhoPreto();
    NoArvVermPreto* raiz;
    //Funções
    void Inserir(string id);
    void InserirAux(NoArvVermPreto* z);
    void RotacaoEsquerda(NoArvVermPreto* x);
    void RotacaoDireita(NoArvVermPreto* x);
    NoArvVermPreto* BuscaNaArvore(string id);
    //Parametros para a insercao
    int numRotacoes;
    int numTrocasDeCor;
    //Parametros para a busca
    int numTrocasBusca;
    int numComparacoesBusca;
};

