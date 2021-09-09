#include <iostream>
#include <algorithm>

using namespace std;

class LinkedList
{
private:
	LinkedList *next;
	LinkedList *before;
	string value;
	string filename;

public:
	LinkedList(string value, string filename)
	{
		this->next = nullptr;
		this->before = nullptr;
		this->value = value;
		this->filename = filename;
	}

	string getValue()
	{
		return this->value;
	}

	string getFilename()
	{
		return this->filename;
	}

	void push(string value, string filename)
	{
		this->value = value;
		this->filename = filename;
		return;
	}

	void push_back(string value, string filename)
	{
		if (this->next != nullptr)
		{
			this->next->push_back(value, filename);
			return;
		}

		this->next = new LinkedList(value, filename);
		this->next->before = this;
	}

	void push_front(string value, string filename)
	{
		if (this->before != nullptr)
		{
			this->before->push_front(value, filename);
			return;
		}

		this->before = new LinkedList(value, filename);
		this->before->next = this;
	}

	LinkedList *search(string value, string filename)
	{
		bool top = this->search2top(value, filename);
		bool bot = this->search2bot(value, filename);

		if ((top == true) || (bot == true))
		{
			return this;
		}

		return nullptr;
	}

	LinkedList *search2top(string value, string filename)
	{
		if ((this->value != value) || (this->filename != filename))
		{
			return this->next == nullptr ? nullptr : this->next->search2top(value, filename);
		}
		return this;
	}

	LinkedList *search2bot(string value, string filename)
	{
		if ((this->value != value) || (this->filename != filename))
		{
			return this->next == nullptr ? nullptr : this->next->search2bot(value, filename);
		}
		return this;
	}

	void remove(string value, string filename)
	{
		LinkedList *currentNode = this->search(value, filename);
		if (currentNode != nullptr)
		{
			currentNode->before->next = currentNode->next;
			currentNode->next->before = currentNode->before;
			delete currentNode;
		}
	}

	void print()
	{
		cout << this->getValue() << "-" << this->getFilename() << " ";
		if (this->next != nullptr)
		{
			this->next->print();
		}
	}
};