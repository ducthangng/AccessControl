#include <iostream>
#include <vector>

using namespace std;

class Role
{
private:
	vector<string> permissions;
	string session;
	string name;

public:
	Role() {}
	Role(string name, string session)
	{
		this->name = name;
		this->session = session;
	}

	void addPermissions(string permission)
	{
		permissions.push_back(permission);
	}

	string getName()
	{
		return name;
	}

	vector<string> getPermissions()
	{
		return permissions;
	}

	string getSession()
	{
		return session;
	}

	bool operator==(Role other)
	{
		if (this->name == other.getName())
			return true;
		else
			return false;
	}

	void printPermissions()
	{
		for (int i = 0; i < permissions.size(); i++)
		{
			cout << permissions[i] << endl;
		}
	}
};

class User
{
private:
	vector<Role> roles;
	vector<string> sessions;
	string name;
	vector<string> permissions;

public:
	User() {}
	User(string name)
	{
		this->name = name;
	}

	void addSession(string session)
	{
		sessions.push_back(session);
	}

	void addPermission(string permission)
	{
		permissions.push_back(permission);
	}

	void combinePermission()
	{
		for (int i = 0; i < roles.size(); i++)
		{
			for (int j = 0; j < sessions.size(); j++)
			{
				if (sessions[j] == roles[i].getSession())
				{
					for (int k = 0; k < roles[i].getPermissions().size(); k++)
					{
						this->addPermission(roles[i].getPermissions()[k]);
					}
				}
			}
		}
	}

	void addRole(Role role)
	{
		roles.push_back(role);
	}

	string getName()
	{
		return name;
	}

	vector<string> getSession()
	{
		return sessions;
	}

	vector<Role> getRole()
	{
		return roles;
	}

	vector<string> getPermissions()
	{
		return permissions;
	}

	void printPermissions()
	{
		for (int i = 0; i < permissions.size(); i++)
		{
			cout << permissions[i] << endl;
		}
	}

	void printSession()
	{
		for (int i = 0; i < sessions.size(); i++)
		{
			cout << sessions[i] << roles[0].getSession() << endl;
		}
	}

	void printRole()
	{
		for (int i = 0; i < roles.size(); i++)
		{
			cout << roles[i].getName() << endl;
		}
	}
};

static Role faculty("Faculty", "s1");
static Role student("Student", "s2");
static Role pcmember("PCMember", "s1");
static Role lecturer("Lecturer", "s1");
static Role ta("TA", "s2");
static Role ptemployee("PTEmployee", "s2");

class UserList
{
private:
	vector<User> users;

public:
	UserList() {}
	void addUser(User user)
	{
		users.push_back(user);
	}

	void combinePermission()
	{
		for (int i = 0; i < users.size(); i++)
		{
			for (int j = 0; j < users[i].getRole().size(); j++)
			{
				if (users[i].getRole()[j].getName() == "PCMember")
				{
					users[i].addRole(faculty);
					users[i].addRole(student);
					users[i].addRole(lecturer);
					users[i].addRole(ta);
					users[i].addRole(ptemployee);
					break;
				}

				else if (users[i].getRole()[j].getName() == "Faculty")
				{
					users[i].addRole(student);
				}

				else if (users[i].getRole()[j].getName() == "Lecturer")
				{
					users[i].addRole(ta);
					users[i].addRole(ptemployee);
				}
			}

			users[i].combinePermission();
		}
	}

	vector<User> getUserList()
	{
		return users;
	}
};

void canAssign(User user, string permission)
{
	int x = 0;
	for (int i = 0; i < user.getPermissions().size(); i++)
	{
		if (permission == user.getPermissions()[i])
		{
			x++;
			break;
		}
	}

	if (x == 0)
		cout << "NO" << endl;
	if (x == 1)
		cout << "YES" << endl;
}

int main()
{
	User ducthang("ducthang");
	User quangnet("quangnet");
	User trung("trung");
	User khang("khang");

	UserList list;

	faculty.addPermissions("delete_course1");
	faculty.addPermissions("modify_course2");
	lecturer.addPermissions("modify_course2");
	ta.addPermissions("modify_course3");
	pcmember.addPermissions("delete_course2");
	student.addPermissions("register_to_course1");

	khang.addSession("s1");
	quangnet.addSession("s2");
	trung.addSession("s1");
	khang.addSession("s2");
	trung.addSession("s2");
	ducthang.addSession("s1");

	quangnet.addRole(pcmember);
	khang.addRole(lecturer);
	trung.addRole(ta);
	ducthang.addRole(ta);
	ducthang.addRole(student);

	list.addUser(quangnet);
	list.addUser(khang);
	list.addUser(trung);
	list.addUser(ducthang);
	list.combinePermission();

	quangnet = list.getUserList()[0];
	khang = list.getUserList()[1];
	trung = list.getUserList()[2];
	ducthang = list.getUserList()[3];

	canAssign(khang, "modify_course3");
	canAssign(quangnet, "modify_course2");
}
