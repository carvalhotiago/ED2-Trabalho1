#include "NoArvB.h"

NoArvB::NoArvB()
{
	
}

// Function to search key k in subtree rooted with this node
NoArvB* NoArvB::Busca(int k)
{
	// Find the first key greater than or equal to k
	int i = 0;
	while (i < keys->size() && k > keys->at(i))
		i++;

	// If the found key is equal to k, return this node
	if (keys->at(i) == k)
		return this;

	// If the key is not found here and this is a leaf node
	if (isFolha == true)
		return NULL;

	// Go to the appropriate child
	return nosFilhos->at(i)->Busca(k);
}