#pragma once
#include <string>
#include <vector>

using namespace std;

class NoArvB
{
public:
	NoArvB();
	vector<unsigned long long > *keys;
	int isFolha;
	int nodesNumber;
	vector<NoArvB*> *nosFilhos;
};

