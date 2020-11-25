#pragma once
#include <string>
#include <vector>

using namespace std;

class NoArvB
{
public:
	NoArvB();
	int isFolha;
	int nodesNumber;
	vector<NoArvB*> *nosFilhos;
	vector<unsigned long long > *keys;
};

