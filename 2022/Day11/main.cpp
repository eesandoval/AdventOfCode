#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

class Monkey 
{
public:
	vector<uint64_t> items;
	char operationChar;
	bool operationSelf = false;
	uint64_t operationValue;
	int testValue;
	int testTrue;
	int testFalse;
	int timesInspected = 0;

	Monkey(vector<uint64_t> startingItems, char o, bool os, int ov, int tv, int tt, int tf) : 
		items(startingItems), operationChar(o), operationSelf(os), operationValue(ov), 
		testValue(tv), testTrue(tt), testFalse(tf) {}
	
	uint64_t operation(int itemIndex)
	{
		timesInspected++;
		if (operationSelf)
			operationValue = items[itemIndex];
		switch (operationChar)
		{
			case '+':
				items[itemIndex] += operationValue;
				break;
			case '*':
				items[itemIndex] *= operationValue;
				break;
		}
		return items[itemIndex];
	}

	uint64_t lowerWorry(int itemIndex)
	{
		items[itemIndex] /= 3;
		return items[itemIndex];
	}

	int test(int itemIndex)
	{
		if (items[itemIndex] % testValue == 0)
			return testTrue;
		return testFalse;
	}
	
	void clear()
	{
		items.clear();
	}

	void storeItem(uint64_t newItem)
	{
		items.push_back(newItem);
	}
};

vector<string> readInput(string fileName)
{
	vector<string> result;
	ifstream fin(fileName);
	string temp;
	while(getline(fin, temp))
	{
		result.push_back(temp);
	}
	return result;
}

uint64_t greatestCommonDivisor(uint64_t mod, uint64_t testValue)
{
	uint64_t temp = 0;
	while (testValue)
		temp = mod % testValue, mod = testValue, testValue = temp;
	return mod;
}

uint64_t monkeyBusiness(vector<string> allLines, bool lowerWorry, int rounds)
{
	vector<Monkey> monkeys;
	uint64_t mod = 1;

	for (int i = 1; i < allLines.size(); i += 7)
	{
		stringstream ss(allLines[i].substr(18, string::npos));
		string item, ovstr;
		vector<uint64_t> si;
		while (getline(ss >> ws, item, ','))
			si.push_back(stoi(item));
		char o = allLines[i+1][23];
		ovstr = allLines[i+1].substr(25, string::npos);
		int tv = stoi(allLines[i+2].substr(21, string::npos));
		int tt = stoi(allLines[i+3].substr(29, string::npos));
		int tf = stoi(allLines[i+4].substr(30, string::npos));
		if (ovstr == "old")
			monkeys.push_back(Monkey(si, o, true, 0, tv, tt, tf));
		else
			monkeys.push_back(Monkey(si, o, false, stoi(ovstr), tv, tt, tf));
		mod = mod / greatestCommonDivisor(mod, monkeys.back().testValue) * monkeys.back().testValue;
	}

	for (int round = 1; round < rounds + 1; round++)
	{
		for (int m = 0; m < monkeys.size(); m++)
		{
			for (int i = 0; i < monkeys[m].items.size(); i++)
			{
				uint64_t newItem = monkeys[m].operation(i);
				if (lowerWorry)
					newItem = monkeys[m].lowerWorry(i);
				else
					newItem = monkeys[m].items[i] % mod;
				int newMonkey = monkeys[m].test(i);
				monkeys[newMonkey].storeItem(newItem);
			}
			monkeys[m].clear();
		}
	}

	vector<uint64_t> inspections;
	for (int i = 0; i < monkeys.size(); i++)
		inspections.push_back(monkeys[i].timesInspected);
	sort(inspections.begin(), inspections.end(), greater<uint64_t>());
	return inspections[0] * inspections[1];
}

uint64_t partOne(vector<string> allLines)
{
	return monkeyBusiness(allLines, true, 20);
}

uint64_t partTwo(vector<string> allLines)
{
	return monkeyBusiness(allLines, false, 10000);
}

int main(int argc, char* argv[])
{
	vector<string> allLines = readInput(argv[1]);
	cout << partOne(allLines) << endl;
	cout << partTwo(allLines) << endl;
	return 0;
}  
