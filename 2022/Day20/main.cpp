#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <deque>
#include <algorithm>

using namespace std;

vector<int> readInput(string fileName)
{
	ifstream fin(fileName);
	vector<int> output;
	string temp;
	while (getline(fin, temp))
		output.push_back(stoi(temp));
	return output;
}

int partOne(vector<int> efile)
{
	vector<int> dfile = efile;
	for (int i = 0; i < efile.size(); i++)
	{
		auto num = efile[i];
		if (num == 0)
			continue;
		auto curPos = find(dfile.begin(), dfile.end(), num) - dfile.begin();
		auto newPos = (curPos + num); 
		if (newPos <= 0)
			newPos--;
		while (newPos < 0)
			newPos += efile.size();
		dfile.erase(dfile.begin() + curPos);
		dfile.insert(dfile.begin() + (newPos % efile.size()) , num);
	}
	auto zeroPos = find(dfile.begin(), dfile.end(), 0) - dfile.begin();
	int result = 0;
	for (int i = 1000; i <= 3000; i += 1000)
		result += dfile[(i + zeroPos) % dfile.size()];
	return result;
}

int partTwo(vector<int> efile)
{
	for (int i = 0; i < efile.size(); i++)
		efile[i] *= 811589153;
	for (int j = 0; j < 10; j++)
	{
		vector<int> dfile = efile;
		for (int i = 0; i < efile.size(); i++)
		{
			auto num = efile[i];
			if (num == 0)
				continue;
			auto curPos = find(dfile.begin(), dfile.end(), num) - dfile.begin();
			auto newPos = (curPos + num); 
			if (newPos <= 0)
				newPos--;
			while (newPos < 0)
				newPos += efile.size();
			dfile.erase(dfile.begin() + curPos);
			dfile.insert(dfile.begin() + (newPos % efile.size()) , num);
		}
		efile = dfile;
	}
	auto zeroPos = find(efile.begin(), efile.end(), 0) - efile.begin();
	int result = 0;
	for (int i = 1000; i <= 3000; i += 1000)
		result += efile[(i + zeroPos) % efile.size()];
	return result;
}

int main(int argc, char* argv[])
{
	auto allLines = readInput(argv[1]);
	cout << partOne(allLines) << endl;
	cout << partTwo(allLines) << endl;
	return 0;
}  
