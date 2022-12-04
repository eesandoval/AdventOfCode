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
	vector<int> result;
	size_t commaPos = line.find(",");
	string string1 = line.substr(0, commaPos);
	string string2 = line.substr(commaPos + 1, line.length() - commaPos + 1);
	size_t dashPos1 = string1.find("-");
	size_t dashPos2 = string2.find("-");
	result.push_back(stoi(string1.substr(0, dashPos1)));
	result.push_back(stoi(string1.substr(dashPos1 + 1, string1.length() - dashPos1 + 1)));
	result.push_back(stoi(string2.substr(0, dashPos2)));
	result.push_back(stoi(string2.substr(dashPos2 + 1, string2.length() - dashPos2 + 1)));
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
