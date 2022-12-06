#include <iostream>
#include <string>
#include <fstream>
#include <deque>
#include <set>

using namespace std;

string readInput(string fileName)
{
	ifstream fin(fileName);
	string temp;
	getline(fin, temp);
	return temp;
}

int getMarker(string buffer, int offset)
{
	int result = 0;
	deque<char> seen;
	for (; result < offset; result++)
	{
		seen.push_front(buffer[result]);
	}
	for (; result < buffer.length(); result++)
	{
		if (set<char>(seen.begin(), seen.end()).size() == offset)
			break;
		seen.pop_back();
		seen.push_front(buffer[result]);
	}
	return result;
}

int partOne(string buffer)
{
	return getMarker(buffer, 4);
}

int partTwo(string buffer)
{
	return getMarker(buffer, 14);
}

int main(int argc, char* argv[])
{
	string buffer = readInput(argv[1]);
	cout << partOne(buffer) << endl;
	cout << partTwo(buffer) << endl;
	return 0;
}  
