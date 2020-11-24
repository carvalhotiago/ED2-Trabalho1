#pragma once
#include "NoArvVermPreto.h"

class ArvoreVermelhoPreto
{
public:
    NoArvVermPreto* root = nullptr;
    NoArvVermPreto* GetRoot() { return root; }
    void RemoveNode(NoArvVermPreto* parent, NoArvVermPreto* curr, int stuff);
    void InsertNode(int stuff);
    void RB_Insert_Fixup(NoArvVermPreto* z);
    void Remove(int stuff);
    void RB_Delete_Fixup(NoArvVermPreto* z);
    NoArvVermPreto* TreeSearch(int stuff);
    void esqRotate(NoArvVermPreto* x);
    void dirRotate(NoArvVermPreto* x);
    void LeftRotate(NoArvVermPreto* x);
    void RightRotate(NoArvVermPreto* x);
    void PreorderTraversal(NoArvVermPreto* temp);
    void ostorderTraversal(NoArvVermPreto* temp);
};

