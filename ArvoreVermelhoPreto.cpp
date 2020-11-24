#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include "ArvoreVermelhoPreto.h"

using namespace std;

void ArvoreVermelhoPreto::InsertNode(int stuff) {
	if (root == nullptr) {
		root = new NoArvVermPreto();
		root->info = stuff;
		root->pai = nullptr;
		root->cor = "BLACK";
		cout << "Element inserted.\n";
	}
	else {
		auto linker = GetRoot();
		NoArvVermPreto* newnode = new NoArvVermPreto();
		newnode->info = stuff;

		while (linker != nullptr) {
			if (linker->info > stuff) {
				if (linker->esq == nullptr) {
					linker->esq = newnode;
					newnode->cor = "RED";
					newnode->pai = linker;
					cout << "Element inserted.\n"; break;
				}
				else { linker = linker->esq; }
			}
			else {
				if (linker->dir == nullptr) {
					linker->dir = newnode;
					newnode->cor = "RED";
					newnode->pai = linker;
					cout << "Element inserted.\n"; break;
				}
				else { linker = linker->dir; }
			}
		}
		RB_Insert_Fixup(newnode);
	}
}

void ArvoreVermelhoPreto::RB_Insert_Fixup(NoArvVermPreto* z) {
	while (z->pai->cor == "RED") {
		auto grandpai = z->pai->pai;
		auto uncle = GetRoot();
		if (z->pai == grandpai->esq) {
			if (grandpai->dir) { uncle = grandpai->dir; }
			if (uncle->cor == "RED") {
				z->pai->cor = "BLACK";
				uncle->cor = "BLACK";
				grandpai->cor = "RED";
				if (grandpai->info != root->info) { z = grandpai; }
				else { break; }
			}
			else if (z == grandpai->esq->dir) {
				esqRotate(z->pai);
			}
			else {
				z->pai->cor = "BLACK";
				grandpai->cor = "RED";
				dirRotate(grandpai);
				if (grandpai->info != root->info) { z = grandpai; }
				else { break; }
			}
		}
		else {
			if (grandpai->esq) { uncle = grandpai->esq; }
			if (uncle->cor == "RED") {
				z->pai->cor = "BLACK";
				uncle->cor = "BLACK";
				grandpai->cor = "RED";
				if (grandpai->info != root->info) { z = grandpai; }
				else { break; }
			}
			else if (z == grandpai->dir->esq) {
				dirRotate(z->pai);
			}
			else {
				z->pai->cor = "BLACK";
				grandpai->cor = "RED";
				esqRotate(grandpai);
				if (grandpai->info != root->info) { z = grandpai; }
				else { break; }
			}
		}
	}
	root->cor = "BLACK";
}


void ArvoreVermelhoPreto::RemoveNode(NoArvVermPreto* pai, NoArvVermPreto* curr, int stuff) {
	if (curr == nullptr) { return; }
	if (curr->info == stuff) {
		//CASE -- 1
		if (curr->esq == nullptr && curr->dir == nullptr) {
			if (pai->info == curr->info) { root = nullptr; }
			else if (pai->dir == curr) {
				RB_Delete_Fixup(curr);
				pai->dir = nullptr;
			}
			else {
				RB_Delete_Fixup(curr);
				pai->esq = nullptr;
			}
		}
		//CASE -- 2
		else if (curr->esq != nullptr && curr->dir == nullptr) {
			int swap = curr->info;
			curr->info = curr->esq->info;
			curr->esq->info = swap;
			RemoveNode(curr, curr->esq, stuff);
		}
		else if (curr->esq == nullptr && curr->dir != nullptr) {
			int swap = curr->info;
			curr->info = curr->dir->info;
			curr->dir->info = swap;
			RemoveNode(curr, curr->dir, stuff);
		}
		//CASE -- 3
		else {
			bool flag = false;
			NoArvVermPreto* temp = curr->dir;
			while (temp->esq) { flag = true; pai = temp; temp = temp->esq; }
			if (!flag) { pai = curr; }
			int swap = curr->info;
			curr->info = temp->info;
			temp->info = swap;
			RemoveNode(pai, temp, swap);
		}
	}
}

void ArvoreVermelhoPreto::Remove(int stuff) {
	auto temp = root;
	auto pai = temp;
	bool flag = false;
	if (!temp) { RemoveNode(nullptr, nullptr, stuff); }

	while (temp) {
		if (stuff == temp->info) { flag = true; RemoveNode(pai, temp, stuff); break; }
		else if (stuff < temp->info) { pai = temp; temp = temp->esq; }
		else { pai = temp; temp = temp->dir; }
	}

	if (!flag) { cout << "\nElement doesn't exist in the table"; }
}

void ArvoreVermelhoPreto::RB_Delete_Fixup(NoArvVermPreto* z) {
	while (z->info != root->info && z->cor == "BLACK") {
		auto sibling = GetRoot();
		if (z->pai->esq == z) {
			if (z->pai->dir) { sibling = z->pai->dir; }
			if (sibling) {
				//CASE -- 1
				if (sibling->cor == "RED") {
					sibling->cor = "BLACK";
					z->pai->cor = "RED";
					esqRotate(z->pai);
					sibling = z->pai->dir;
				}
				//CASE -- 2
				if (sibling->esq == nullptr && sibling->dir == nullptr) {
					sibling->cor = "RED";
					z = z->pai;
				}
				else if (sibling->esq->cor == "BLACK" && sibling->dir->cor == "BLACK") {
					sibling->cor = "RED";
					z = z->pai;
				}
				//CASE -- 3
				else if (sibling->dir->cor == "BLACK") {
					sibling->esq->cor = "BLACK";
					sibling->cor = "RED";
					dirRotate(sibling);
					sibling = z->pai->dir;
				}
				else {
					sibling->cor = z->pai->cor;
					z->pai->cor = "BLACK";
					if (sibling->dir) { sibling->dir->cor = "BLACK"; }
					esqRotate(z->pai);
					z = root;
				}
			}
		}
		else {
			if (z->pai->dir == z) {
				if (z->pai->esq) { sibling = z->pai->esq; }
				if (sibling) {
					//CASE -- 1
					if (sibling->cor == "RED") {
						sibling->cor = "BLACK";
						z->pai->cor = "RED";
						dirRotate(z->pai);
						sibling = z->pai->esq;
					}
					//CASE -- 2
					if (sibling->esq == nullptr && sibling->dir == nullptr) {
						sibling->cor = "RED";
						z = z->pai;
					}
					else if (sibling->esq->cor == "BLACK" && sibling->dir->cor == "BLACK") {
						sibling->cor = "RED";
						z = z->pai;
					}
					//CASE -- 3 
					else if (sibling->esq->cor == "BLACK") {
						sibling->dir->cor = "BLACK";
						sibling->cor = "RED";
						dirRotate(sibling);
						sibling = z->pai->esq;
					}
					else {
						sibling->cor = z->pai->cor;
						z->pai->cor = "BLACK";
						if (sibling->esq) { sibling->esq->cor = "BLACK"; }
						esqRotate(z->pai);
						z = root;
					}
				}
			}

		}
	}
	z->cor = "BLACK";
}

NoArvVermPreto* ArvoreVermelhoPreto::TreeSearch(int stuff) {
	auto* temp = GetRoot();
	if (temp == nullptr) { return nullptr; }

	while (temp) {
		if (stuff == temp->info)
			return temp;
		else if (stuff < temp->info) { temp = temp->esq; }
		else { temp = temp->dir; }
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

void ArvoreVermelhoPreto::PreorderTraversal(NoArvVermPreto* temp) {
	if (!temp) { return; }
	cout << "--> " << temp->info << "<" << temp->cor << ">";
	PreorderTraversal(temp->esq);
	PreorderTraversal(temp->dir);
}

void ArvoreVermelhoPreto::ostorderTraversal(NoArvVermPreto* temp) {
	if (!temp) { return; }
	PreorderTraversal(temp->esq);
	PreorderTraversal(temp->dir);
	cout << "--> " << temp->info << "<" << temp->cor << ">";
}