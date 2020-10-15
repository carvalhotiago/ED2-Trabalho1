#include "No.h"
#include <iostream>

template <typename T>
No<T>::No(T* valor)
{
	this->valor = valor;
	this->proximo = NULL;
}

template <typename T>
No<T>* No<T>::GetProximo()
{
	return this->proximo;
}

template <typename T>
void No<T>::SetProximo(No<T>* proximo)
{
	this->proximo = proximo;
}

template <typename T>
T* No<T>::GetValor()
{
	return this->valor;
}
