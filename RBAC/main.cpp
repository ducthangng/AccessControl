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

	string getUserName()
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
		if (this->name == other.getUserName())
			return true;
		else
			return false;
	}

	void printPermissionInfo()
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

	void addRoleForUser(Role role)
	{
		roles.push_back(role);
	}

	string getUserName()
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

	void printPermissionInfo()
	{
		for (int i = 0; i < permissions.size(); i++)
		{
			cout << permissions[i] << endl;
		}
	}

	void printPermissionInfo()
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
			cout << roles[i].getUserName() << endl;
		}
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
	User charlie("Charlie");
	User bob("Bob");
	User oscar("Oscar");
	User alice("Alice");

	vector<User> users;

	Role faculty("Faculty", "s1");
	Role student("Student", "s2");
	Role pcmember("PCMember", "s1");
	Role lecturer("Lecturer", "s1");
	Role ta("TA", "s2");
	Role ptemployee("PTEmployee", "s2");

	faculty.addPermissions("delete_course1");
	faculty.addPermissions("modify_course2");
	lecturer.addPermissions("modify_course2");
	ta.addPermissions("modify_course3");
	pcmember.addPermissions("delete_course2");
	student.addPermissions("register_to_course1");

	alice.addSession("s1");
	bob.addSession("s2");
	oscar.addSession("s1");
	alice.addSession("s2");
	oscar.addSession("s2");
	charlie.addSession("s1");

	bob.addRoleForUser(pcmember);
	alice.addRoleForUser(lecturer);
	oscar.addRoleForUser(ta);
	charlie.addRoleForUser(ta);
	charlie.addRoleForUser(student);

	users.push_back(bob);
	users.push_back(alice);
	users.push_back(oscar);
	users.push_back(charlie);

	for (int i = 0; i < users.size(); i++)
	{
		for (int j = 0; j < users[i].getRole().size(); j++)
		{
			if (users[i].getRole()[j].getUserName() == "PCMember")
			{
				users[i].addRoleForUser(faculty);
				users[i].addRoleForUser(student);
				users[i].addRoleForUser(lecturer);
				users[i].addRoleForUser(ta);
				users[i].addRoleForUser(ptemployee);
				break;
			}

			else if (users[i].getRole()[j].getUserName() == "Faculty")
			{
				users[i].addRoleForUser(student);
			}

			else if (users[i].getRole()[j].getUserName() == "Lecturer")
			{
				users[i].addRoleForUser(ta);
				users[i].addRoleForUser(ptemployee);
			}
		}

		users[i].combinePermission();
	}

	bob = users[0];
	alice = users[1];
	oscar = users[2];
	charlie = users[3];

	canAssign(alice, "modify_course3");
	canAssign(bob, "modify_course2");
}
