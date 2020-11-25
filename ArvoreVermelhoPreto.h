#pragma once
#include "NoArvVermPreto.h"
#include <string>

using namespace std;

class ArvoreVermelhoPreto
{
public:
    ArvoreVermelhoPreto();
    NoArvVermPreto* root;
    //Parametros para a insercao
    int numRotacoes;
    int numTrocasDeCor;
    //Parametros para a busca
    int nosPercorridosBusca;
    int comparacoesNaBusca;
    void InsertNode(string id);
    void RB_Insert_Fixup(NoArvVermPreto* z);
    NoArvVermPreto* TreeSearch(string id);
    void esqRotate(NoArvVermPreto* x);
    void dirRotate(NoArvVermPreto* x);
};

