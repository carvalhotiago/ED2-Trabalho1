#include <iostream>
#include "Lista.h"
#include "Book.h"

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
No<T>* Lista<T>::GetPrimeiro()
{
	return this->primeiro;
}

template class Lista<int>;
template class Lista<Book>;