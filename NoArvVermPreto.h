#pragma once
#include <string>

using namespace std;

class NoArvVermPreto
{
public:
	int info;
	string cor;
	NoArvVermPreto* esq = nullptr;
	NoArvVermPreto* dir = nullptr;
	NoArvVermPreto* pai = nullptr;
};

