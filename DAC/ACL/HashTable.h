#include <iostream>
#include <string.h>
#include <algorithm>
#include "LinkedList.h"

#define A 54059	  /* a prime */
#define B 76963	  /* another prime */
#define C 101	  /* yet another prime */
#define FIRSTH 37 /* also prime */

class HashTable
{
private:
	LinkedList *list[110];

public:
	HashTable()
	{
		for (int i = 0; i < 101; i++)
		{
			this->list[i] = new LinkedList("", "");
		}
	}

	// Hash Function: convert string to int.
	unsigned hash_str(string key)
	{
		unsigned h = FIRSTH;
		for (int i = 0; i < key.length(); i++)
		{
			h = (h * A) ^ (key[i] * B);
		}
		return h % C;
	}

	void addEntry(string key, string value, string filename)
	{

		unsigned hashed_key = this->hash_str(key);

		string cvalue = this->list[hashed_key]->getValue();
		if (cvalue == "")
		{
			this->list[hashed_key]->push(value, filename);
			return;
		}

		this->list[hashed_key]->push_back(value, filename);
		return;
	}

	void remove(string key, string value, string filename)
	{
		unsigned hashed_key = this->hash_str(key);
		this->list[hashed_key]->remove(value, filename);
	}

	bool search(string key, string value, string filename)
	{
		unsigned hashed_key = this->hash_str(key);
		LinkedList *ll = this->list[hashed_key]->search(value, filename);
		if (ll == nullptr)
		{
			return false;
		}

		return true;
	}

	void print(string key)
	{
		unsigned hashed_key = this->hash_str(key);
		cout << key << " :";
		this->list[hashed_key]->print();
		cout << endl;
	}
};