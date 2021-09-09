#include <iostream>
#include <algorithm>
#include "HashTable.h"

using namespace std;

HashTable ht;
bool determine(string subject, string action, string object)
{
	if (ht.search(object, action, subject))
	{
		return true;
	}
	return false;
}

int main()
{
	ht.addEntry("file1", "read", "ducthang");
	ht.addEntry("file1", "write", "ducthang");
	ht.addEntry("file2", "read", "ducthang");
	ht.addEntry("file2", "read", "ironman");
	ht.addEntry("file1", "execute", "ironman");
	ht.addEntry("file2", "share", "captain");

	determine("ducthang", "read", "file1") == true ? cout << "accepted" << endl : cout << "rejected" << endl;
	determine("ducthang", "write", "file1") == true ? cout << "accepted" << endl : cout << "rejected" << endl;
	determine("ironman", "write", "file2") == true ? cout << "accepted" << endl : cout << "rejected" << endl;
	determine("ironman", "execute", "file2") == true ? cout << "accepted" << endl : cout << "rejected" << endl;
}