#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

class State
{
private:
	vector<char> label;
	int name;

public:
	State() {}
	State(int name)
	{
		this->name = name;
	}

	void addLabel(vector<char> other)
	{
		label.insert(label.end(), other.begin(), other.end());
	}

	void clearLable()
	{
		label.clear();
	}

	void printLabel()
	{
		for (int i = 0; i < label.size(); i++)
		{
			cout << label[i] << endl;
		}
	}

	vector<char> getLabel()
	{
		return label;
	}

	int LabelSize()
	{
		return label.size();
	}
};

class Transition
{
private:
	int begin;
	int end;

public:
	Transition(int begin, int end)
	{
		this->begin = begin;
		this->end = end;
	}

	int getBegin()
	{
		return begin;
	}

	int getEnd()
	{
		return end;
	}

	void printTransition()
	{
		cout << begin << "   " << end << endl;
	}
};

class Model
{
private:
	vector<State> states;
	vector<Transition> transitions;
	vector<int> path;

public:
	Model() {}

	void addState(State state)
	{
		states.push_back(state);
	}

	void addTransition(Transition transition)
	{
		transitions.push_back(transition);
	}

	void addPath(int path)
	{
		this->path.push_back(path);
	}

	void printTransition()
	{
		for (int i = 0; i < transitions.size(); i++)
		{
			transitions[i].printTransition();
		}
	}

	bool checkPath()
	{
		int x = 0;
		for (int i = 0; i < path.size() - 1; i++)
		{
			for (int j = 0; j < transitions.size(); j++)
			{
				if ((path[i] == transitions[j].getBegin()) && (path[i + 1] == transitions[j].getEnd()))
				{
					x++;
					break;
				}
			}
		}

		if (x == path.size() - 1)
			return true;
		else
			return false;
	}

	vector<int> Pattern()
	{
		int length = 1;
		vector<int> pattern;
		int n = path.size();
		int a = 0, b = 1, c = 0;

		while ((a < length) && (length < n))
		{
			length = b;
			a = 0;
			pattern.push_back(path[n - length]);
			for (int i = 0; i < length; i++)
			{
				if (pattern[i] == path[n - 1 - i - length])
				{
					a++;
				}
			}
			b++;
		}

		reverse(pattern.begin(), pattern.end());
		return pattern;
	}

	void printPath()
	{
		for (int i = 0; i < path.size(); i++)
		{
			cout << path[i] << endl;
		}
	}

	void printPattern()
	{
		for (int i = 0; i < Pattern().size(); i++)
		{
			cout << Pattern()[i] << endl;
		}
	}

	void Checking(vector<char> s)
	{
		int c = 0;
		int d = 0;
		if (s[0] == 'F')
		{
			if (s[1] == 'X')
			{
				for (int i = 0; i < states[Pattern()[0]].LabelSize(); i++)
				{
					if (s[2] == states[Pattern()[0]].getLabel()[i])
					{
						c = 1;
						break;
					}
				}
				if (s[3] == 'V')
				{
					for (int i = 0; i < states[Pattern()[0]].LabelSize(); i++)
					{
						if (s[6] == states[Pattern()[0]].getLabel()[i])
						{
							c = 1;
							break;
						}
					}
				}
			}

			if (s[1] == 'G')
			{
				d = 0;
				for (int j = 0; j < Pattern().size(); j++)
				{
					for (int i = 0; i < states[Pattern()[0]].LabelSize(); i++)
					{
						if (s[2] == states[Pattern()[j]].getLabel()[i])
						{
							d++;
							break;
						}
					}
				}
				if (d == Pattern().size())
					c = 1;
				if (s[3] == 'V')
				{
					d = 0;
					for (int j = 0; j < Pattern().size(); j++)
					{
						for (int i = 0; i < states[Pattern()[0]].LabelSize(); i++)
						{
							if (s[6] == states[Pattern()[j]].getLabel()[i])
							{
								d++;
								break;
							}
						}
					}
					if (d == Pattern().size())
						c = 1;
				}
			}

			else
			{
				for (int j = 0; j < Pattern().size(); j++)
				{
					for (int i = 0; i < states[Pattern()[0]].LabelSize(); i++)
					{
						if (s[1] == states[Pattern()[j]].getLabel()[i])
						{
							c = 1;
							break;
						}
					}
				}
				if (s[2] == 'V')
				{
					for (int j = 0; j < Pattern().size(); j++)
					{
						for (int i = 0; i < states[Pattern()[0]].LabelSize(); i++)
						{
							if (s[4] == states[Pattern()[j]].getLabel()[i])
							{
								c = 1;
								break;
							}
						}
					}
				}
			}
		}

		if (s[0] = 'G')
		{
			d = 0;
			c = 1;
			if (s[1] = 'F')
			{
				for (int i = 0; i < states[Pattern()[0]].LabelSize(); i++)
				{
					if (s[2] == states[Pattern()[Pattern().size() - 1]].getLabel()[i])
					{
						c = 1;
						break;
					}
				}
				if (s[3] == 'V')
				{
					for (int i = 0; i < states[Pattern()[0]].LabelSize(); i++)
					{
						if (s[6] == states[Pattern()[Pattern().size() - 1]].getLabel()[i])
						{
							c = 1;
							break;
						}
					}
				}
			}

			if (s[1] = 'X')
			{
				d = 0;
				for (int j = 0; j < Pattern().size(); j++)
				{
					for (int i = 0; i < states[Pattern()[0]].LabelSize(); i++)
					{
						if (s[2] == states[Pattern()[j]].getLabel()[i])
						{
							d++;
							break;
						}
					}
				}
				if (d == Pattern().size())
					c = 1;
				if (s[3] == 'V')
				{
					d = 0;
					for (int j = 0; j < Pattern().size(); j++)
					{
						for (int i = 0; i < states[Pattern()[0]].LabelSize(); i++)
						{
							if (s[6] == states[Pattern()[j]].getLabel()[i])
							{
								d++;
								break;
							}
						}
					}
					if (d == Pattern().size())
						c = 1;
				}
			}

			else
			{
				d = 0;
				for (int j = 0; j < Pattern().size(); j++)
				{
					for (int i = 0; i < states[Pattern()[0]].LabelSize(); i++)
					{
						if (s[1] == states[Pattern()[j]].getLabel()[i])
						{
							d++;
							break;
						}
					}
				}
				if (d == Pattern().size())
					c = 1;
				if (s[2] == 'V')
				{
					d = 0;
					for (int j = 0; j < Pattern().size(); j++)
					{
						for (int i = 0; i < states[Pattern()[0]].LabelSize(); i++)
						{
							if (s[4] == states[Pattern()[j]].getLabel()[i])
							{
								d++;
								break;
							}
						}
					}
					if (d == Pattern().size())
						c = 1;
				}
			}
		}

		if (s[0] == 'X')
		{
			if (s[1] = 'G')
			{
				d = 0;
				for (int j = 0; j < Pattern().size(); j++)
				{
					for (int i = 0; i < states[Pattern()[0]].LabelSize(); i++)
					{
						if (s[2] == states[Pattern()[j]].getLabel()[i])
						{
							d++;
							break;
						}
					}
				}
				if (d == Pattern().size())
					c = 1;
				if (s[3] == 'V')
				{
					d = 0;
					for (int j = 0; j < Pattern().size(); j++)
					{
						for (int i = 0; i < states[Pattern()[0]].LabelSize(); i++)
						{
							if (s[6] == states[Pattern()[j]].getLabel()[i])
							{
								d++;
								break;
							}
						}
					}
					if (d == Pattern().size())
						c = 1;
				}
			}

			if (s[1] == 'F')
			{
				for (int i = 0; i < states[Pattern()[0]].LabelSize(); i++)
				{
					if (s[2] == states[Pattern()[0]].getLabel()[i])
					{
						c = 1;
						break;
					}
				}
				if (s[3] == 'V')
				{
					for (int i = 0; i < states[Pattern()[0]].LabelSize(); i++)
					{
						if (s[6] == states[Pattern()[0]].getLabel()[i])
						{
							c = 1;
							break;
						}
					}
				}
			}

			else
			{
				for (int i = 0; i < states[path[1]].getLabel().size(); i++)
				{
					if (states[path[1]].getLabel()[i] == s[2])
					{
						c = 1;
						break;
					}
				}

				if (s[2] == 'V')
				{
					for (int i = 0; i < states[path[1]].getLabel().size(); i++)
					{
						if (states[path[1]].getLabel()[i] == s[4])
						{
							c = 1;
							break;
						}
					}
				}
			}
		}

		else
		{
			if (s[1] == 'V')
			{
				d = 0;
				for (int j = 0; j < path.size(); j++)
				{
					for (int i = 0; i < states[path[1]].getLabel().size(); i++)
					{
						if ((states[path[j]].getLabel()[i] == s[0]) || (states[path[j]].getLabel()[i] == s[2]) || (states[path[j]].getLabel()[i] == s[4]))
						{
							d++;
							break;
						}
					}
				}
				if (d = path.size())
					c = 1;
			}
			else
			{
				d = 0;
				for (int j = 0; j < path.size(); j++)
				{
					for (int i = 0; i < states[path[1]].getLabel().size(); i++)
					{
						if ((states[path[j]].getLabel()[i] == s[0]) || (states[path[j]].getLabel()[i] == s[2]))
						{
							d++;
							break;
						}
					}
				}
				if (d = path.size())
					c = 1;
			}
		}

		if (checkPath() == true)
		{
			if (c == 1)
				cout << "Satisfied" << endl;
			if (c == 0)
				cout << "Not Satisfied" << endl;
		}

		else if (checkPath() == false)
			cout << "Not Satisfied" << endl;
	}
};

int main()
{
	int a, c, d, e, f;
	string line, line2;
	char x, b, g, h;
	vector<char> labels;
	Model kripke;
	State state;
	vector<char> key;

	cout << "how many states" << endl;
	cin >> a;
	cin.ignore();
	for (int i = 0; i < a; i++)
	{

		cout << "input labels seperated by spaces for s" << i << " E.g : p q v" << endl;

		getline(cin, line);
		istringstream stream(line);
		while (stream >> x)
		{
			labels.push_back(x);
		}

		state.addLabel(labels);
		labels.clear();

		kripke.addState(state);

		state.printLabel();
		state.clearLable();
	}

	cout << "enter transition" << endl;
	cin >> g >> h;
	while ((g != 'e') && (h != 'e'))
	{
		cout << "enter transition:" << endl;
		Transition transition((int)g - 48, (int)h - 48);
		cin >> g >> h;

		kripke.addTransition(transition);
	}

	cin.ignore();

	kripke.printTransition();

	cout << "Enter a path: " << endl;
	getline(cin, line);
	istringstream stream(line);
	while (stream >> b)
	{
		kripke.addPath(b - 48);
	}

	kripke.printPath();

	cout << "Enter a string: " << endl;

	getline(cin, line2);
	istringstream streamm(line2);
	while (streamm >> b)
	{
		key.push_back(b);
	}

	kripke.Checking(key);
}
