#include <iostream>
#include <vector>
#include <string>

using namespace std;

class User
{
private:
	int ID;
	string Name;

public:
	User() {}

	User(int ID, string Name)
	{
		this->ID = ID;
		this->Name = Name;
	}

	int GetID() { return this->ID; }

	string GetName() { return this->Name; }

	bool operator==(const User &a)
	{
		if ((this->ID == a.ID) && (this->Name == a.Name))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

class Object
{
private:
	string Name;

public:
	Object() {}

	Object(string Name)
	{
		this->Name = Name;
	}

	string GetName() { return this->Name; }

	bool operator==(const Object &a)
	{
		if (this->Name == a.Name)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

class Action
{
private:
	string Name;

public:
	Action() {}

	Action(string Name)
	{
		this->Name = Name;
	}

	string GetName() { return this->Name; }

	bool operator==(const Action &a)
	{
		if (this->Name == a.Name)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

class TableRow
{
private:
	User U;
	Action Act;
	Object Obj;

public:
	TableRow() {}
	TableRow(User U, Action action, Object Objectname)
	{
		this->U = U;
		this->Act = action;
		this->Obj = Objectname;
	}

	User GetUserInfo() { return this->U; }
	Action GetAction() { return this->Act; }
	Object GetObjectName() { return this->Obj; }

	bool Compare(User user, Action Act, Object Obj)
	{
		if ((this->U == user) && (this->Act == Act) && (this->Obj == Obj))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

class AuthorizationTable
{
private:
	vector<TableRow> AuthTable;

public:
	AuthorizationTable() {}

	void addRows(TableRow &r)
	{
		this->AuthTable.push_back(r);
	}

	void Determine(User user, Action Act, Object Obj)
	{
		for (int i = 0; i < this->AuthTable.size(); i++)
		{
			TableRow x = this->AuthTable[i];

			bool Comparing = x.Compare(user, Act, Obj);
			if (Comparing)
			{
				cout << "Permitted" << endl;
				return;
			}
		}

		cout << "Not Permitted" << endl;
	}
};

int main()
{

	// 2 users
	User thang(1, "ducthang");
	User trung(2, "quoctrung");

	// 2 files
	Object file1("file1");
	Object file2("file2");

	// 3 actions
	Action write("write");
	Action read("read");
	Action execute("execute");

	// Authorization Table has 4 rows: first is the name, next is the action, lastly is the object.
	TableRow row1(thang, write, file1);
	TableRow row2(thang, read, file1);
	TableRow row3(trung, execute, file1);
	TableRow row4(trung, read, file2);

	// Add the rows to table;
	AuthorizationTable auth_table;
	auth_table.addRows(row1);
	auth_table.addRows(row2);
	auth_table.addRows(row3);
	auth_table.addRows(row4);

	// test
	auth_table.Determine(trung, execute, file1);
	auth_table.Determine(thang, execute, file1);
	auth_table.Determine(thang, read, file2);
	auth_table.Determine(trung, write, file2);
	auth_table.Determine(trung, read, file2);
}