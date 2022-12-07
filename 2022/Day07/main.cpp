#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

struct directory {
	string name;
	int totalFileSize = 0;
	vector<directory*> subDirectories;
	directory* parentDirectory;
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

int getDirSize(directory* currentDir)
{
	int totalSize = 0;
	for (directory* subDir : currentDir->subDirectories)
	{
		totalSize += getDirSize(subDir);
	}
	return totalSize + currentDir->totalFileSize;
}

vector<int> allDirSizes;

int partOne(vector<string> allLines)
{
	vector<directory*> allDirectories;
	directory* currentDirectory = new directory();
	currentDirectory->name = "/";
	allDirectories.push_back(currentDirectory);
	string name;
	int size;
	for (int i = 1; i < allLines.size(); i++)
	{
		string line = allLines[i];
		if (line[2] == 'c' && line[5] != '.')
		{
			string dirName = line.substr(5, string::npos);
			for (directory* d : currentDirectory->subDirectories)
			{
				if (d->name == dirName)
				{
					currentDirectory = d;
					break;
				}
			}
		}
		else if (line[2] == 'c')
		{
			currentDirectory = currentDirectory->parentDirectory;
		}
		else
		{
			line = allLines[++i];
			while (line[0] != '$')
			{
				if (line[0] == 'd')
				{
					name = line.substr(4, string::npos);
					directory* temp = new directory();
					temp->name = name;
					temp->parentDirectory = currentDirectory;
					allDirectories.push_back(temp);
					currentDirectory->subDirectories.push_back(temp);
				}
				else
				{
					stringstream ss(line);
					string tempInt;
					ss >> tempInt;
					currentDirectory->totalFileSize += stoi(tempInt);
				}
				if (i + 1 >= allLines.size())
				{
					i = allLines.size() + 100;
					break;
				}
				line = allLines[++i];
			}
			i--;
		}
	}
	int result = 0;
	for (directory* d : allDirectories)
	{
		int totalSize = getDirSize(d);
		if (totalSize <= 100000)
		{
			result += totalSize;
		}
		allDirSizes.push_back(totalSize);
	}
	return result;
}

int partTwo()
{
	sort(allDirSizes.begin(), allDirSizes.end(), greater<int>());
	int minSize = 30000000 - (70000000 - allDirSizes[0]);
	for (int i = 0; i < allDirSizes.size(); i++)
	{
		if (allDirSizes[i] < minSize)
			return allDirSizes[i - 1];		
	}
	return 0;
}

int main(int argc, char* argv[])
{
	vector<string> buffer = readInput(argv[1]);
	cout << partOne(buffer) << endl;
	cout << partTwo() << endl;
	return 0;
}  
