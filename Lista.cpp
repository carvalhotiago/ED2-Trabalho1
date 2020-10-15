#include <iostream>
#include "Lista.h"

template <typename T>
Lista<T>::Lista()
{
	this->primeiro = NULL;
}

template <typename T>
void Lista<T>::Insere(T* valor)
{
	No<T>* no = new No<T>(valor);
	No<T>* aux = this->primeiro;

	if (aux == NULL)
	{
		this->primeiro = no;
	}
	else {
		while (aux->GetProximo() != NULL) 
			aux = aux->GetProximo();
		
		aux->SetProximo(no);
	}
}

template <typename T>
T* Lista<T>::GetPrimeiro()
{
	return this->primeiro;
}