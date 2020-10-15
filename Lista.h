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
	T* GetPrimeiro();
};

