#include "ArvoreB.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

const int T_CHAVE = 9;

ArvoreB::ArvoreB(int ordem)
{
	NoArvB* raiz = NULL;

	this->raiz = new NoArvB;
	this->raiz->keys = new vector<unsigned long long >;
	this->raiz->isFolha = 1;
	this->raiz->nodesNumber = 0;
	this->raiz->nosFilhos = new vector<NoArvB*>;

	this->ordem = ordem;
}

/* Fun��o que reparte um n� da �rvore e promove uma chave */
void ArvoreB::ReparteArvoreNoFilho(NoArvB* pai, unsigned long long  i, int ordem) {

	int j;

	//z � o novo n� criado com a reparti��o
	NoArvB* z = new NoArvB;

	//y � o n� que ser� repartido
	NoArvB* y = pai->nosFilhos->at(i);

	z->isFolha = y->isFolha;

	//A quantidade de chaves de z ser� a quantidae m�nima de chaves que um n� pode ter 
	z->nodesNumber = ceil((double)ordem / 2) - 1;

	//Transfere-se metade das chaves de y para z
	for (j = 0; j < (int)ceil((double)ordem / 2) - 1; j++) {
		z->keys->push_back(y->keys->at(j + (ordem / 2)));
	}

	//Caso y n�o seja folha(n�o tenha filhos), transfere-se metade dos filhos de z para y
	if (!y->isFolha) {
		for (j = 0; j < (int)((ordem + 1) / 2); j++) {
			z->nosFilhos->push_back(y->nosFilhos->at(j + (ordem / 2)));
		}
	}

	//A quantidade de chaves de y tamb�m ser� a quantidade m�nima de chaves que um n� pode ter
	y->nodesNumber = ceil(ordem / 2) - 1;

	//Reorganiza-se os filhos do n� pai para inserir o novo filho 
	for (j = pai->nodesNumber; j >= i + 1; j--) {
		pai->nosFilhos->push_back(pai->nosFilhos->at(j));
	}

	//Liga-se o novo filho ao n� pai
	pai->nosFilhos->push_back(z);

	//Insere-se no n� pai, a chave promovida
	pai->keys->push_back(y->keys->at((int)(ordem / 2) - 1));
	pai->nodesNumber++;
}

/* Fun��o que insere uma nova chave em um n� que n�o est� cheio */
void ArvoreB::InsertKey(NoArvB* no, unsigned long long  chave, int ordem) {

	//Numero de n�s � decrementado por 1 pois em C vetores come�am em 0 e precisaremos acessar a chave 0 em algum momento
	int i = no->nodesNumber - 1;

	//Caso em que o n� � folha(n�o tem filhos)
	if (no->isFolha) {

		//Percorre as chaves do final para o come�o at� encontrar a posi��o certa de inserir a chave ou chegar � ultima chave 
		//Enquanto percorre, vai passando todas as chaves para a posi��o � direita
		while (i >= 0 && (no->keys->at(i) > chave) > 0) {
			no->keys->push_back(no->keys->at(i));
			i--;
		}

		//Insere a chave na posi��o encontrada
		no->keys->push_back(chave);
		no->nodesNumber++;
	}

	//Caso em que o n� n�o � folha
	else {

		//Econtra a posi��o do filho que vai ter a nova chave
		while (i >= 0 && (no->keys->at(i) > chave) > 0) {
			i--;
		}
		i++;

		//Caso em que deseja-se inserir a nova chave em um filho cheio
		if (no->nosFilhos->at(i)->nodesNumber == ordem - 1) {

			//Reparte-se o filho para caber a nova chave
			ReparteArvoreNoFilho(no, i, ordem);

			//Decide-se quais dos dois novos filhos iremos entrar para inserir a nova chave
			if ((no->keys->at(i) < chave) < 0) {
				i = i + 1;
			}
		}

		//Insere-se a chave no filho decidido no if anterior
		InsertKey(no->nosFilhos->at(i), chave, ordem);
	}
}

/* Fun��o que insere uma nova chave na �rvore */
void ArvoreB::Insert(unsigned long long  chave) {

	NoArvB* r = this->raiz;

	//Caso em que deseja-se inserir um novo n� em uma raiz vazia
	if (this->raiz->nodesNumber == 0) {
		this->raiz->keys->push_back(chave);
		this->raiz->nodesNumber++;
	}

	//Caso em que a raiz n�o � vazia
	else {

		//Caso em que o n� raiz est� cheio
		if (r->nodesNumber == this->ordem - 1) {

			//Cria��o de um novo n� que se tornar� a nova raiz
			NoArvB* s = new NoArvB();
			this->raiz = s;
			s->isFolha = 0;
			s->nodesNumber = 0;

			//A antiga raiz se torna filha da nova raiz
			s->nosFilhos->push_back(r);

			//Reparte-se a raiz para que ela tenha 2 filhos
			ReparteArvoreNoFilho(s, 0, this->ordem);

			//Insere-se o novo n�
			InsertKey(s, chave, this->ordem);
		}

		//Caso em que a raiz n�o est� cheia
		else {
			InsertKey(r, chave, this->ordem);
		}
	}
}