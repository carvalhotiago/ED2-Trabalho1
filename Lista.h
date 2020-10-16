#pragma once
#include "No.h"

template <typename T>
class Lista
{
private:
	No<T>* primeiro;

public:
	Lista();
	void Insere(T* valor);
	No<T>* GetPrimeiro();
	void PrintListOfBook(Lista<T> books);
};

