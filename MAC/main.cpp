

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class AccessAuthorization
{
protected:
	string access;
	string name;

public:
	AccessAuthorization() {}
	string GetAccess() { return this->access; }

	string GetName() { return this->name; }

	bool operator==(const AccessAuthorization &a)
	{
		if ((this->access == a.access) && (this->name == a.name))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	int AccessLevel()
	{
		if (access == "U")
			return 0;
		if (access == "C")
			return 1;
		if (access == "S")
			return 2;
		if (access == "TS")
			return 3;
		else
			return 0;
	}

	bool operator<(AccessAuthorization a)
	{
		if (this->AccessLevel() < a.AccessLevel())
			return true;
		else
			return false;
	}
};

class Subject : public AccessAuthorization
{
public:
	Subject() {}

	Subject(string name, string access)
	{
		this->access = access;
		this->name = name;
	}
};

class Object : public AccessAuthorization
{
public:
	Object() {}

	Object(string name, string access)
	{
		this->name = name;
		this->access = access;
	}
};

void Determine(Subject subject, Object object, string mode)
{
	if (subject.AccessLevel() < object.AccessLevel())
	{
		if (mode == "read")
			cout << subject.GetName() << " cannot read " << object.GetName() << endl;
		if (mode == "write")
			cout << subject.GetName() << " can write " << object.GetName() << endl;
	}
	else
	{
		if (mode == "read")
			cout << subject.GetName() << " can read " << object.GetName() << endl;
		if (mode == "write")
			cout << subject.GetName() << " cannot write " << object.GetName() << endl;
	}
}

int main()
{

	// 2 Subjects
	Subject thang("Thang", "TS");
	Subject trung("Trung", "U");

	// 2 files
	Object file1("file1", "S");
	Object file2("file2", "U");

	Determine(thang, file1, "read");
	Determine(trung, file1, "read");
}