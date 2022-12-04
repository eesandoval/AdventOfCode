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

vector<int> parseLine(string line)
{
	vector<int> result(4, 0);
	sscanf(line.c_str(), "%d-%d,%d-%d", &result[0], &result[1], &result[2], &result[3]);
	return result;
}

int partOne(vector<string> allLines)
{
	int result = 0;
	for (string line : allLines)
	{
		vector<int> ranges = parseLine(line);
		if (ranges[2] >= ranges[0] && ranges[3] <= ranges[1])
			result += 1;
		else if (ranges[2] <= ranges[0] && ranges[3] >= ranges[1])
			result += 1;
	}
	return result;
}

int partTwo(vector<string> allLines)
{
	int result = 0;
	for (string line : allLines)
	{
		vector<int> ranges = parseLine(line);
		if (ranges[0] <= ranges[3] && ranges[1] >= ranges[2])
			result += 1;
		else if (ranges[0] >= ranges[2] && ranges[1] <= ranges[3])
			result += 1;
	}
	return result;
}

int main(int argc, char* argv[])
{
	vector<string> allLines = readInputVector(argv[1]);
	cout << partOne(allLines) << endl;
	cout << partTwo(allLines) << endl;
	return 0;
}  
