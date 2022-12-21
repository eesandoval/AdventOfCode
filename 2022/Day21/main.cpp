#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <deque>
#include <algorithm>
#include <map>
#include <stdexcept>
#include <unistd.h>
using namespace std;

struct Monkey
{
	string l;
	string r;
	int64_t lnum;
	int64_t rnum;
	char operand;
	int64_t result;
	bool hasResult = false;
	bool haslnum = false;
	bool hasrnum = false;
	
	void yell(map<string, Monkey> monkeys)
	{
		if (monkeys[l].hasResult && !haslnum)
		{
			lnum = monkeys[l].result;
			haslnum = true;
		}
		if (monkeys[r].hasResult && !hasrnum)
		{
			rnum = monkeys[r].result;
			hasrnum = true;
		}
		if (hasrnum && haslnum)
		{
			hasResult = true;
			switch (operand)
			{
				case '*':
					result = lnum * rnum;
					break;
				case '+':
					result = lnum + rnum;
					break;
				case '-':
					result = lnum - rnum;
					break;
				case '/':
					result = lnum / rnum;
					break;
			}
		}
	}
};

vector<string> readInput(string fileName)
{
	ifstream fin(fileName);
	vector<string> output;
	string temp;
	while (getline(fin, temp))
		output.push_back(temp);
	return output;
}

map<string, Monkey> parseMonkeys(vector<string> allLines)
{
	map<string, Monkey> monkeys;
	for (auto l : allLines)
	{
		Monkey m;
		string name = l.substr(0, 4), operation = l.substr(6, string::npos);
		try 
		{
			m.result = stoi(operation);
			m.hasResult = true;
		}
		catch (const invalid_argument& ia)
		{
			m.l = operation.substr(0, 4);
			m.operand = operation[5];
			m.r = operation.substr(7, string::npos);
		}
		monkeys[name] = m;
	}
	return monkeys;
}

int64_t partOne(map<string, Monkey> monkeys)
{
	while (!monkeys["root"].hasResult)
	{
		for (auto m : monkeys)
		{
			if (monkeys[m.first].hasResult)
				continue;
			monkeys[m.first].yell(monkeys);
		}
	}
	return monkeys["root"].result;
}

bool hasHumn(map<string, Monkey> monkeys, string name)
{
	if (name == "humn")
		return true;
	if (monkeys[name].hasResult)
		return false;
	auto l = monkeys[name].l;
	auto r = monkeys[name].r;
	if (l == "humn" || r == "humn")
		return true;
	return hasHumn(monkeys, l) || hasHumn(monkeys, r);
}

void solve(map<string, Monkey>& monkeys, string name)
{
	if (monkeys[name].hasResult)
		return;
	auto l = monkeys[name].l;
	auto r = monkeys[name].r;
	solve(monkeys, l); solve(monkeys, r);
	monkeys[name].yell(monkeys);
}

void solveTree(map<string, Monkey>& monkeys, string name)
{
	if (name == "humn")
		return;
	auto lmonkey = monkeys[name].l, rmonkey = monkeys[name].r;

	if (hasHumn(monkeys, lmonkey)) // lmonkey is dependent
	{	
		solve(monkeys, rmonkey);
		solveTree(monkeys, lmonkey);
	}
	else if (hasHumn(monkeys, rmonkey)) // rmonkey is dependent
	{
		solve(monkeys, lmonkey);
		solveTree(monkeys, rmonkey);
	}
}

uint64_t partTwo(map<string, Monkey> monkeys)
{
	monkeys["humn"].hasResult = false;
	// solve as much of the tree as we can
	solveTree(monkeys, "root");

	// find which side is the problemMonkey (pm) with humn
	// gM is the goodMonkey side that we won't solve
	string pM, gM;
	if (hasHumn(monkeys, monkeys["root"].l))
	{
		pM = monkeys["root"].l;
		gM = monkeys["root"].r;
	}
	else
	{
		pM = monkeys["root"].r;
		gM = monkeys["root"].l;
	}

	// problem side == good side result for equality check
	monkeys[pM].result = monkeys[gM].result;
	monkeys[pM].hasResult = true;
	while (pM != "humn")
	{
		auto l = monkeys[pM].l;
		auto r = monkeys[pM].r;
		if (monkeys[l].hasResult) // solve r
		{
			switch (monkeys[pM].operand)
			{
				case '+':
					monkeys[r].result = monkeys[pM].result - monkeys[l].result;
					break;
				case '-':
					monkeys[r].result = monkeys[l].result - monkeys[pM].result;
					break;
				case '*':
					monkeys[r].result = monkeys[pM].result / monkeys[l].result;
					break;
				case '/':
					monkeys[r].result = monkeys[l].result / monkeys[pM].result;
					break;
			}
			monkeys[r].hasResult = true;
			pM = r; // r is the new problem
		}
		else // solve l
		{
			switch (monkeys[pM].operand)
			{
				case '+':
					monkeys[l].result = monkeys[pM].result - monkeys[r].result;
					break;
				case '-':
					monkeys[l].result = monkeys[pM].result + monkeys[r].result;
					break;
				case '*':
					monkeys[l].result = monkeys[pM].result / monkeys[r].result;
					break;
				case '/':
					monkeys[l].result = monkeys[pM].result * monkeys[r].result;
					break;
			}
			monkeys[l].hasResult = true;
			pM = l; // l is the new problem
		}
	}
	return monkeys["humn"].result;
}

int main(int argc, char* argv[])
{
	auto allLines = readInput(argv[1]);
	auto monkeys = parseMonkeys(allLines);
	cout << partOne(monkeys) << endl;
	cout << partTwo(monkeys) << endl;
	return 0;
}  
