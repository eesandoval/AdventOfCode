#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>

using namespace std;

vector<string> readInputVector(string fileName)
{
	ifstream fin(fileName);
	vector<string> output;
	string temp;
	while (getline(fin, temp))
	{
		output.push_back(temp);
	}
	return output;
}

vector<stack<char>> parseCrates(vector<string> crateLines)
{
	vector<stack<char>> result;
	for (int i = 0; i < crateLines.size(); i++)
	{
		result.push_back(stack<char>());
		for (char crate : crateLines[i])
		{
			result[i].push(crate);
		}
	}
	return result;
}

string moveCrates(vector<string> allLines, vector<stack<char>> crates, bool part2 = false)
{
	stringstream result;
	int quantity, from, to;
	for (string line : allLines)
	{
		sscanf(line.c_str(), "move %d from %d to %d", &quantity, &from, &to);
		stack<char> tempStack;
		for (int i = 0; i < quantity; i++)
		{
			char temp = crates[from - 1].top();
			crates[from - 1].pop();
			tempStack.push(temp);
			if (!part2)
				crates[to - 1].push(temp);
		}
		if (part2)
		{
			for (int i = 0; i < quantity; i++)
			{
				char temp = tempStack.top();
				tempStack.pop();
				crates[to - 1].push(temp);
			}
		}
	}
	
	for (stack<char> crate : crates)
	{
		result << crate.top();
	}
	return result.str();
}

string partOne(vector<string> allLines, vector<stack<char>> crates)
{
	return moveCrates(allLines, crates);
}

string partTwo(vector<string> allLines, vector<stack<char>> crates)
{
	return moveCrates(allLines, crates, true);
}

int main(int argc, char* argv[])
{
	vector<string> allLines = readInputVector(argv[1]);
	vector<string> crateLines = readInputVector(argv[2]);
	vector<stack<char>> crates = parseCrates(crateLines);
	cout << partOne(allLines, crates) << endl;
	cout << partTwo(allLines, crates) << endl;
	return 0;
}  
