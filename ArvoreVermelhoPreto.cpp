#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "ArvoreVermelhoPreto.h"

using namespace std;

ArvoreVermelhoPreto::ArvoreVermelhoPreto()
{
	root = nullptr;
	numRotacoes = 0;
	numTrocasDeCor = 0;
	nosPercorridosBusca = 0;
	comparacoesNaBusca = 0;
}

void ArvoreVermelhoPreto::InsertNode(string id) {

	stringstream idBookInt(id);
	unsigned long long idBook = 0;
	idBookInt >> idBook;

	if (root == nullptr)
	{
		root = new NoArvVermPreto();
		root->info = idBook;
		root->pai = nullptr;
		root->cor = "BLACK";
	}
	else 
	{
		NoArvVermPreto *linker = root;
		NoArvVermPreto* newnode = new NoArvVermPreto();
		newnode->info = idBook;

		while (linker != nullptr) 
		{
			if (linker->info > idBook) 
			{
				if (linker->esq == nullptr) 
				{
					linker->esq = newnode;
					newnode->cor = "RED";
					newnode->pai = linker;
					break;
				}
				else 
					linker = linker->esq; 
			}
			else
			{
				if (linker->dir == nullptr) 
				{
					linker->dir = newnode;
					newnode->cor = "RED";
					newnode->pai = linker;
					break;
				}
				else
					linker = linker->dir;
			}
		}
		RB_Insert_Fixup(newnode);
	}
}

void ArvoreVermelhoPreto::RB_Insert_Fixup(NoArvVermPreto* z) 
{
	while (z->pai->cor == "RED") 
	{
		auto grandpai = z->pai->pai;
		auto uncle = root;
		if (z->pai == grandpai->esq) 
		{
			if (grandpai->dir) 
				uncle = grandpai->dir;
			if (uncle->cor == "RED") 
			{
				z->pai->cor = "BLACK";
				uncle->cor = "BLACK";
				grandpai->cor = "RED";
				numTrocasDeCor++;
				if (grandpai->info != root->info) 
					z = grandpai;
				else 
					break;
			}
			else if (z == grandpai->esq->dir) {
				esqRotate(z->pai);
				numRotacoes++;
			}
			else {
				z->pai->cor = "BLACK";
				grandpai->cor = "RED";
				numTrocasDeCor++;
				dirRotate(grandpai);
				numRotacoes++;
				if (grandpai->info != root->info) 
					z = grandpai;
				else
					break;
			}
		}
		else 
		{
			if (grandpai->esq) 
				uncle = grandpai->esq;

			if (uncle->cor == "RED")
			{
				z->pai->cor = "BLACK";
				uncle->cor = "BLACK";
				grandpai->cor = "RED";
				numTrocasDeCor++;
				if (grandpai->info != root->info)
					z = grandpai;
				else
					break;
			}
			else if (z == grandpai->dir->esq)
			{
				dirRotate(z->pai);
				numRotacoes++;
			}
			
			else {
				z->pai->cor = "BLACK";
				grandpai->cor = "RED";
				numTrocasDeCor++;
				esqRotate(grandpai);
				numRotacoes++;
				if (grandpai->info != root->info) 
					z = grandpai;
				else
					break;
			}
		}
	}

	root->cor = "BLACK";
}

NoArvVermPreto* ArvoreVermelhoPreto::TreeSearch(string id) 
{
	stringstream idBookInt(id);
	unsigned long long idBook = 0;
	idBookInt >> idBook;

	auto* temp = root;
	if (temp == nullptr)
		return nullptr;

	while (temp) 
	{
		comparacoesNaBusca++;
		if (idBook == temp->info)
			return temp;
		else
		{
			comparacoesNaBusca++;
			if (idBook < temp->info)
				temp = temp->esq;
			else
				temp = temp->dir;
		}

		nosPercorridosBusca++;
	}

	return nullptr;
}

void ArvoreVermelhoPreto::esqRotate(NoArvVermPreto* x) {
	NoArvVermPreto* nw_node = new NoArvVermPreto();
	if (x->dir->esq) { nw_node->dir = x->dir->esq; }
	nw_node->esq = x->esq;
	nw_node->info = x->info;
	nw_node->cor = x->cor;
	x->info = x->dir->info;
	x->cor = x->dir->cor;
	x->esq = nw_node;
	if (nw_node->esq) { nw_node->esq->pai = nw_node; }
	if (nw_node->dir) { nw_node->dir->pai = nw_node; }
	nw_node->pai = x;

	if (x->dir->dir) { x->dir = x->dir->dir; }
	else { x->dir = nullptr; }

	if (x->dir) { x->dir->pai = x; }
}

void ArvoreVermelhoPreto::dirRotate(NoArvVermPreto* x) {
	NoArvVermPreto* nw_node = new NoArvVermPreto();
	if (x->esq->dir) { nw_node->esq = x->esq->dir; }
	nw_node->dir = x->dir;
	nw_node->info = x->info;
	nw_node->cor = x->cor;

	x->info = x->esq->info;
	x->cor = x->esq->cor;

	x->dir = nw_node;
	if (nw_node->esq) { nw_node->esq->pai = nw_node; }
	if (nw_node->dir) { nw_node->dir->pai = nw_node; }
	nw_node->pai = x;

	if (x->esq->esq) { x->esq = x->esq->esq; }
	else { x->esq = nullptr; }

	if (x->esq) { x->esq->pai = x; }
}