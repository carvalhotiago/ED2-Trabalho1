#include "Author.h"

Author::Author(string name)
{
	this->appearances = 1;
	this->authorName = name;
}

Author::Author(int id)
{
	this->appearances = 1;
	this->id = id;
}
