#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

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

int partOne(vector<string> allLines)
{
	string operation;
	int addx, x = 1, cycle = 0, result = 0, i;
	for (auto line : allLines)
	{
		stringstream ss(line); 
		ss >> operation;
		if (operation == "addx")
		{
			ss >> addx;
			for (i = 0; i < 2; i++)
				if (++cycle % 40 == 20)
					result += cycle * x;
			x += addx;
		}
		else
			if (++cycle % 40 == 20)
				result += cycle * x;
	}
	return result;
}

void partTwo(vector<string> allLines)
{
	string operation;
	int addx, x = 1, cycle = 0, i, cycle_delay = 0;
	stringstream CRT;
	for (auto line : allLines)
	{
		stringstream ss(line); 
		ss >> operation;
		
		if (operation == "addx")
		{
			ss >> addx;
			cycle_delay = 2;
		}
		else 
		{
			cycle_delay = 1;
		}
		for (i = 0; i < cycle_delay; i++)
		{
			if (cycle >= x - 1 && cycle <= x + 1)
				CRT << "#";
			else
				CRT << ".";
			cycle = (cycle + 1) % 40;
		}
		if (operation == "addx")
			x += addx;
	}
	string output = CRT.str();
	for (i = 0; i < output.length(); i++)
	{
		cout << output[i];
		if ((i + 1) % 40 == 0)
			cout << endl;
	}
}

int main(int argc, char* argv[])
{
	vector<string> allLines = readInput(argv[1]);
	cout << partOne(allLines) << endl;
	partTwo(allLines);
	return 0;
}  
