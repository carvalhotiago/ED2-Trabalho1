#pragma once
#include <string>
#include <vector>

using namespace std;

class NoArvB
{
public:
	NoArvB();
	vector<int> *keys;
	int isFolha;
	int nodesNumber;
	vector<NoArvB*> *nosFilhos;
};

