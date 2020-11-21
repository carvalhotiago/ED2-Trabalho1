#pragma once
#include <string>
#include <vector>

using namespace std;

class NoArvB
{
public:
	vector<string> *keys;
	int isFolha;
	int nodesNumber;
	vector<NoArvB*> *nosFilhos;
};

