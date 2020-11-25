#pragma once
#include <string>

using namespace std;

class NoArvVermPreto
{
public:
	string cor;
	unsigned long long info;
	NoArvVermPreto* esq = nullptr;
	NoArvVermPreto* dir = nullptr;
	NoArvVermPreto* pai = nullptr;
};

