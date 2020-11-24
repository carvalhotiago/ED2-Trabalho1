#pragma once
#include "NoArvVermPreto.h"
#include <string>

using namespace std;

class ArvoreVermelhoPreto
{
public:
    NoArvVermPreto* root = nullptr;
    NoArvVermPreto* GetRoot() { return root; }
    void RemoveNode(NoArvVermPreto* parent, NoArvVermPreto* curr, int stuff);
    void InsertNode(string id);
    void RB_Insert_Fixup(NoArvVermPreto* z);
    void Remove(int stuff);
    void RB_Delete_Fixup(NoArvVermPreto* z);
    NoArvVermPreto* TreeSearch(unsigned long long stuff);
    void esqRotate(NoArvVermPreto* x);
    void dirRotate(NoArvVermPreto* x);
    void LeftRotate(NoArvVermPreto* x);
    void RightRotate(NoArvVermPreto* x);
    void PreorderTraversal(NoArvVermPreto* temp);
    void ostorderTraversal(NoArvVermPreto* temp);
};

