#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

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

vector<pair<string, string>> getRucksacks(vector<string> allLines)
{
	vector<pair<string, string>> result;
	for (string line : allLines)
	{
		stringstream comp1, comp2;
		for (int i = 0; i < line.length() / 2; i++)
		{
			comp1 << line[i];
		}
		for (int i = line.length() / 2; i < line.length(); i++)
		{
			comp2 << line[i];
		}
		result.push_back(make_pair(comp1.str(), comp2.str()));
	}
	return result;
}

int charToScore(char c)
{
	if (c > 90)
		return c - 96;
	else
		return c - 38;
}

int partOne(vector<pair<string, string>> rucksacks)
{
	int result = 0;
	for (pair<string, string> rucksack : rucksacks)
	{
		for (int i = 0; i < rucksack.first.length(); i++)
		{
			size_t found = rucksack.second.find(rucksack.first[i]);
			if (found != string::npos)
			{
				result += charToScore(rucksack.first[i]);
				break;
			}
		}
	}
	return result;
}

int partTwo(vector<string> allLines)
{
	int result = 0;
	for (int i = 0; i < allLines.size(); i += 3)
	{
		for (int j = 0; j < allLines[i].length(); j++)
		{
			size_t found1 = allLines[i + 1].find(allLines[i][j]);
			size_t found2 = allLines[i + 2].find(allLines[i][j]);
			if (found1 != string::npos && found2 != string::npos)
			{
				result += charToScore(allLines[i][j]);
				break;
			}
		}
	}
	return result;
}

int main(int argc, char* argv[])
{
	vector<string> allLines = readInputVector(argv[1]);
	vector<pair<string, string>> rucksacks = getRucksacks(allLines);
	cout << partOne(rucksacks) << endl;
	cout << partTwo(allLines) << endl;
	return 0;
}  
