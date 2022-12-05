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

vector<stack<char>> parseCrates(vector<string> allLines)
{
	int totalCrates = (allLines[0].length() / 4) + 1;
	vector<stringstream> temp(totalCrates);
	vector<stack<char>> result(totalCrates);
	for (int i = 0; i < totalCrates; i++)
	{
		temp[i] = stringstream();
		result[i] = stack<char>();
	}
	for (string line : allLines)
	{
		if (line[1] == '1')
			break;
		int crateNum = -1;
		for (int i = 1; i < line.length(); i += 4)
		{
			crateNum++;
			if (line[i] == ' ')
				continue;
			temp[crateNum] << line[i];
		}
	}
	for (int i = 0; i < totalCrates; i++)
	{
		string s = temp[i].str();
		for (int j = s.length(); j >= 0; j--)
		{
			result[i].push(s[j]);
		}
	}
	return result;
}

vector<string> parseMoves(vector<string> allLines)
{
	vector<string> result;
	for (string line : allLines)
	{
		if (line.empty() || line[0] != 'm')
			continue;
		result.push_back(line);
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
	vector<stack<char>> crates = parseCrates(allLines);
	vector<string> allMoves = parseMoves(allLines);
	cout << partOne(allMoves, crates) << endl;
	cout << partTwo(allMoves, crates) << endl;
	return 0;
}  
