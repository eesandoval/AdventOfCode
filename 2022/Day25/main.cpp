#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

vector<string> readInput(string fileName)
{
	ifstream fin(fileName);
	vector<string> output;
	string temp;
	while (getline(fin, temp))
		output.push_back(temp);
	return output;
}

string partOne(vector<string> allLines)
{
	uint64_t number = 0;
	for (auto line : allLines)
	{
		uint64_t power = 1;
		uint64_t currentNum = 0;
		reverse(begin(line), end(line));
		for (auto c : line)
		{
			switch (c)
			{
				case '0':
					break;
				case '1':
					currentNum += power;
					break;
				case '2':
					currentNum += power * 2;
					break;
				case '-':
					currentNum -= power;
					break;
				case '=':
					currentNum -= power * 2;
			}
			power *= 5;
		}
		reverse(begin(line), end(line));
		number += currentNum;
	}
	stringstream ss;
	while (number > 0)
	{
		int leftover = number % 5;
		int carryOver = 0;
		switch (leftover)
		{
			case 0:
			case 1:
			case 2:
				ss << to_string(leftover);
				break;
			case 3:
				ss << "=";
				carryOver = 1;
				break;
			case 4:
				ss << "-";
				carryOver = 1;
				break;
		}
		number = (number / 5) + carryOver;
	}
	string result = ss.str();
	reverse(begin(result), end(result));
	return result;
}

int main(int argc, char* argv[])
{
	auto allLines = readInput(argv[1]);
	cout << partOne(allLines) << endl;
	return 0;
}
