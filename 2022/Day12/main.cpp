#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <tuple>
#include <set>
#include <deque>
#define StepPoint tuple<int, int, int>
#define Point tuple<int, int>

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

StepPoint sPosition(vector<string> allLines)
{
	for (int row = 0; row < allLines.size(); row++)
		for (int col = 0; col < allLines[0].length(); col++)
			if (allLines[row][col] == 'S')
				return make_tuple(row, col, 0);
	return make_tuple(0, 0, 0); // default
}

deque<StepPoint> aPosition(vector<string> allLines)
{
	deque<StepPoint> result;
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

vector<StepPoint> validPositions(vector<string> hMap, StepPoint sp)
{
	vector<StepPoint> result;
	int row = get<0>(sp), col = get<1>(sp), steps = get<2>(sp);
	char height = hMap[row][col];
	if (height == 'S')
		height = 'a';

	if (row - 1 >= 0 && hMap[row - 1][col] - height <= 1)
		result.push_back(make_tuple(row - 1, col, steps + 1));

	if (row + 1 <= hMap.size() - 1 && hMap[row + 1][col] - height <= 1)
		result.push_back(make_tuple(row + 1, col, steps + 1));

	if (col - 1 >= 0 && hMap[row][col - 1] - height <= 1)
		result.push_back(make_tuple(row, col - 1, steps + 1));

	if (col + 1 <= hMap[0].length() - 1 && hMap[row][col + 1] - height <= 1)
		result.push_back(make_tuple(row, col + 1, steps + 1));

	return result;
}

int BFS(vector<string> hMap, vector<string> hMapE, deque<StepPoint> dsp)
{
	set<Point> seen;
	while (dsp.size() > 0)
	{
		auto pos = dsp.front();
		dsp.pop_front();
		auto checkPos = make_tuple(get<0>(pos), get<1>(pos));		

		if (seen.find(checkPos) != seen.end()) // skip seen positions
			continue; 
		seen.insert(checkPos);
	
		if (hMapE[get<0>(pos)][get<1>(pos)] == 'E')
			return get<2>(pos); // return steps
		auto newPositions = validPositions(hMap, pos);
		for (auto newPosition : newPositions)
			dsp.push_back(newPosition);
	}
	return -1; // Should never hit this 
}

int partOne(vector<string> hMap, vector<string> hMapE)
{
	auto startPosition = sPosition(hMap);
	deque<StepPoint> positions;
	positions.push_back(startPosition);

	return BFS(hMap, hMapE, positions);
}

int partTwo(vector<string> hMap, vector<string> hMapE)
{
	auto positions = aPosition(hMap);
	
	return BFS(hMap, hMapE, positions);
}

int main(int argc, char* argv[])
{
	vector<string> hMapE = readInput(argv[1]);
	vector<string> hMap = updateE(hMapE);
	cout << partOne(hMap, hMapE) << endl;
	cout << partTwo(hMap, hMapE) << endl;
	return 0;
}  
