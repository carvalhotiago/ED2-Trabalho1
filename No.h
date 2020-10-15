#pragma once

template <typename T>
class No
{
private:
	T* valor;
	No* proximo;

public:
	No(T* valor);
	T* GetValor();
	No* GetProximo();
	void SetProximo(No<T>* proximo);
};

