#pragma once
#include <string>

using namespace std;

class Author
{
public:
	Author(string name);
	Author(int id);
	string authorName;
	int id;
	int appearances;
};

