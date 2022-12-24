#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <sstream>
#include <utility>
#include <algorithm>
#define Point pair<int,int>
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

vector<Point> getElfPositions(vector<string> allLines)
{
	vector<Point> result;
	for (int y = 0; y < allLines.size(); y++)
		for (int x = 0; x < allLines[y].length(); x++)
			if (allLines[y][x] == '#')
				result.push_back(make_pair(x, y));
	return result;
}

vector<string> expandBoard(vector<string> allLines)
{
	vector<string> result;
	// add as many lines prior
	for (int i = 0; i < allLines.size(); i++)
	{
		stringstream ss;
		for (int j = 0; j < allLines[i].length() * 3; j++)
			ss << ".";
		result.push_back(ss.str());
	}
	// now add the included input
	for (int i = 0; i < allLines.size(); i++)
	{
		stringstream ss;
		for (int j = 0; j < allLines[i].length(); j++)
			ss << ".";
		for (int j = 0; j < allLines[i].length(); j++)
			ss << allLines[i][j];
		for (int j = 0; j < allLines[i].length(); j++)
			ss << ".";
		result.push_back(ss.str());
	}
	// same as before but now at the end
	for (int i = 0; i < allLines.size(); i++)
	{
		stringstream ss;
		for (int j = 0; j < allLines[i].length() * 3; j++)
			ss << ".";
		result.push_back(ss.str());
	}
	return result;
}

Point getNewPosition(Point eP, int nextDir, vector<string> board, vector<vector<Point>> lookAround)
{
	bool empty = true;
	for (auto lA : lookAround)
		for (auto p : lA)
			if (board[eP.second + p.second][eP.first + p.first] == '#')
				empty = false;
	if (empty)
		return eP; // dont move
	for (int i = 0; i < lookAround.size(); i++)
	{	
		empty = true;
		for (auto p : lookAround[nextDir])	
			if (board[eP.second + p.second][eP.first + p.first] == '#')
				empty = false;
		if (empty)
		{
			switch (nextDir)  // 0 -> N, 1 -> S, 2 -> W, 3 -> E
			{
				case 0:
					return make_pair(eP.first, eP.second - 1);
				case 1:
					return make_pair(eP.first, eP.second + 1); 
				case 2:
					return make_pair(eP.first - 1, eP.second);
				case 3:
					return make_pair(eP.first + 1, eP.second);
			}
		}
		nextDir = (nextDir + 1) % 4;
	}
	return eP; // in case the elf is surrounded, no movement(?)
}

int64_t elfMovement(vector<string> allLines, bool partTwo = false)
{
	auto board = expandBoard(allLines);
	auto elfPositions = getElfPositions(board);
	
	vector<vector<Point>> lookAround;
	vector<Point> north{make_pair(-1,-1), make_pair(0,-1), make_pair(1,-1)};
	vector<Point> south{make_pair(-1,1), make_pair(0,1), make_pair(1,1)};
	vector<Point> west{make_pair(-1,-1), make_pair(-1,0), make_pair(-1,1)};
	vector<Point> east{make_pair(1,-1), make_pair(1,0), make_pair(1,1)};
	lookAround.push_back(north); lookAround.push_back(south);
	lookAround.push_back(west); lookAround.push_back(east);
	
	vector<Point> newPositions = elfPositions;
	int round = 0;
	while (partTwo || !partTwo && round < 20)
	{
		bool movement = false;
		int nextDir = (round / 2) % 4;
		for (int i = 0; i < elfPositions.size(); i++)
		{
			if (round % 2 == 0) // first half
				newPositions[i] = getNewPosition(elfPositions[i], nextDir, board, lookAround);
			else // second half
			{
				if (count(newPositions.begin(), newPositions.end(), newPositions[i]) > 1)
					continue; // dont move if the counts bigger than 1
				if (elfPositions[i] != newPositions[i])
					movement = true;
				board[elfPositions[i].second][elfPositions[i].first] = '.';
				board[newPositions[i].second][newPositions[i].first] = '#';
				elfPositions[i] = newPositions[i];
			}
		}
		if (partTwo && round % 2 == 1 && !movement)
			break;
		round++;
	}
	if (partTwo)
		return (round+1)/2;
	int startR = 0, startC = board[0].length(), endR = board.size() - 1, endC = 0;
	for (; startR < board.size(); startR++)
		if (board[startR].find('#') != string::npos)
			break;
	for (; endR > 0; endR--)
		if (board[endR].find('#') != string::npos)
			break;
	for (int i = startR; i <= endR; i++)
	{
		auto found1 = board[i].find_first_of("#");
		auto found2 = board[i].find_last_of("#");
		if (found1 != string::npos)
			startC = min(startC, (int)found1);
		if (found2 != string::npos)
			endC = max(endC, (int)found2);
	}
	int result = 0;
	for (int i = startR; i <= endR; i++)
		for (int j = startC; j <= endC; j++)
			if (board[i][j] == '.')
				result++;
	return result;
}

uint64_t partOne(vector<string> allLines)
{
	return elfMovement(allLines);
}

uint64_t partTwo(vector<string> allLines)
{
	return elfMovement(allLines, true);
}

int main(int argc, char* argv[])
{
	auto allLines = readInput(argv[1]);
	cout << partOne(allLines) << endl;
	cout << partTwo(allLines) << endl;
	return 0;
}
