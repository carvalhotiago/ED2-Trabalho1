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
    void InserirAux(NoArvVermPreto* no);
    void RotacaoEsquerda(NoArvVermPreto* no);
    void RotacaoDireita(NoArvVermPreto* no);
    NoArvVermPreto* BuscaNaArvore(string id);
    //Parametros para a insercao
    int numRotacoes;
    int numTrocasDeCor;
    //Parametros para a busca
    int numTrocasBusca;
    int numComparacoesBusca;
};

