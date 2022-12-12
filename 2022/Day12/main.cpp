#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <tuple>
#include <set>
#include <deque>

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

tuple<int, int, int> sPosition(vector<string> allLines)
{
	for (int row = 0; row < allLines.size(); row++)
		for (int col = 0; col < allLines[0].length(); col++)
			if (allLines[row][col] == 'S')
				return make_tuple(row, col, 0);
	return make_tuple(0, 0, 0); // default
}

deque<tuple<int, int, int>> aPosition(vector<string> allLines)
{
	deque<tuple<int, int, int>> result;
	for (int row = 0; row < allLines.size(); row++)
		for (int col = 0; col < allLines[0].length(); col++)
			if (allLines[row][col] == 'a')
				result.push_back(make_tuple(row, col, 0));
	return result;
}

vector<string> updateE(vector<string> allLines)
{
	for (int row = 0; row < allLines.size(); row++)
		for (int col = 0; col < allLines[0].length(); col++)
			if (allLines[row][col] == 'E')
			{
				allLines[row][col] = 'z';
				return allLines;
			}
	return allLines; // failsafe
}

vector<tuple<int, int, int>> validPositions(vector<string> allLines, tuple<int, int, int> position)
{
	vector<tuple<int, int, int>> result;
	int row = get<0>(position), col = get<1>(position), steps = get<2>(position);
	char currElevation = allLines[row][col];
	if (currElevation == 'S')
		currElevation = 'a';

	if (row - 1 >= 0 && allLines[row - 1][col] - currElevation <= 1)
		result.push_back(make_tuple(row - 1, col, steps+1));
	if (row + 1 <= allLines.size() - 1 && allLines[row + 1][col] - currElevation <= 1)
		result.push_back(make_tuple(row + 1, col, steps+1));
	if (col - 1 >= 0 && allLines[row][col - 1] - currElevation <= 1)
		result.push_back(make_tuple(row, col - 1, steps+1));
	if (col + 1 <= allLines[0].length() - 1 && allLines[row][col + 1] - currElevation <= 1)
		result.push_back(make_tuple(row, col + 1, steps+1));
	return result;
}

int partOne(vector<string> originalLines)
{
	auto startPosition = sPosition(originalLines);
	vector<string> allLines = updateE(originalLines);
	set<tuple<int, int>> seen;
	deque<tuple<int, int, int>> nextPositions; 
	nextPositions.push_back(startPosition);
	
	while (nextPositions.size() > 0)
	{
		auto nextPosition = nextPositions.front();
		nextPositions.pop_front();
		auto checkPosition = make_tuple(get<0>(nextPosition), get<1>(nextPosition));		

		if (seen.find(checkPosition) != seen.end()) // skip seen positions
			continue; 
		seen.insert(checkPosition);
		
		if (originalLines[get<0>(nextPosition)][get<1>(nextPosition)] == 'E')
			return get<2>(nextPosition); // return steps
		auto newPositions = validPositions(allLines, nextPosition);
		for (auto newPosition : newPositions)
			nextPositions.push_back(newPosition);
	}
	return -1; // Should never hit this 
}

int partTwo(vector<string> originalLines)
{
	vector<string> allLines = updateE(originalLines);
	set<tuple<int, int>> seen;
	deque<tuple<int, int, int>> nextPositions = aPosition(originalLines);
	
	while (nextPositions.size() > 0)
	{
		auto nextPosition = nextPositions.front();
		nextPositions.pop_front();
		auto checkPosition = make_tuple(get<0>(nextPosition), get<1>(nextPosition));		

		if (seen.find(checkPosition) != seen.end()) // skip seen positions
			continue; 
		seen.insert(checkPosition);
	
		if (originalLines[get<0>(nextPosition)][get<1>(nextPosition)] == 'E')
			return get<2>(nextPosition); // return steps
		auto newPositions = validPositions(allLines, nextPosition);
		for (auto newPosition : newPositions)
			nextPositions.push_back(newPosition);
	}
	return -1; // Should never hit this 
}

int main(int argc, char* argv[])
{
	vector<string> allLines = readInput(argv[1]);
	cout << partOne(allLines) << endl;
	cout << partTwo(allLines) << endl;
	return 0;
}  
