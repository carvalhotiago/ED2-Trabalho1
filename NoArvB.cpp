#include "NoArvB.h"

NoArvB::NoArvB()
{
	isFolha = 1;
	nodesNumber = 0;
	nosFilhos = new vector<NoArvB*>;
	keys = new vector<unsigned long long >;
}