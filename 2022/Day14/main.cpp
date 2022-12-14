#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

vector<string> readInput(string fileName)
{
	vector<string> result;
	ifstream fin(fileName);
	string temp;
	while(getline(fin, temp))
		result.push_back(temp);
	return result;
}

const int maxX = 1000, maxY = 1000;
int rMaxY = 0, startX = 500, startY = 0;
char cave[maxX][maxY];

void createLine(int x1, int x2, int y1, int y2)
{
	rMaxY = max(rMaxY, y1);
	if (x2 != -1 && y2 != -1) // after first token
		if (x1 == x2) // same column
			for (int i = min(y1, y2); i <= max(y1, y2); i++)
				cave[i][x1] = '#';
		else if (y1 == y2) // same row
			for (int i = min(x1, x2); i <= max(x1, x2); i++)
				cave[y1][i] = '#';
}

void setupCave(vector<string> allLines)
{	
	for (int y = 0; y < maxY; y++)
		for (int x = 0; x < maxX; x++)
			cave[y][x] = '.';
	size_t pos = 0;
	string token;
	for (auto line : allLines)
	{
		int x1 = -1, x2 = -1, y1 = -1, y2 = -1; // defaults
		while ((pos = line.find(" -> ")) != string::npos)
		{
			token = line.substr(0, pos);
			sscanf(token.c_str(), "%d,%d", &x1, &y1);
			createLine(x1, x2, y1, y2);
			x2 = x1, y2 = y1; // put it on the back burner
			line.erase(0, pos + 4);
		}
		sscanf(line.c_str(), "%d,%d", &x1, &y1);
		createLine(x1, x2, y1, y2);
	}
	cave[startY][startX] = '+';
}

int placeSand()
{
	int result = 0, sandX, sandY;
	while (true)
	{
		sandX = startX, sandY = startY;
		while (sandY <= rMaxY)
			if (cave[sandY + 1][sandX] == '.')
				sandY++;
			else if (cave[sandY + 1][sandX - 1] == '.')
				sandY++, sandX--;
			else if (cave[sandY + 1][sandX + 1] == '.')
				sandY++, sandX++;
			else
				break;
		if (sandY > rMaxY || (sandY == startY && sandX == startX))
			break; // exit if we are going into the void or can't place sand
		cave[sandY][sandX] = 'o';
		result++;
	}
	return result;
}

int partOne(vector<string> allLines)
{
	setupCave(allLines);
	return placeSand();
}

int partTwo(vector<string> allLines)
{
	setupCave(allLines);
	rMaxY += 2;
	for (int x = 0; x <= maxX; x++) // floor
		cave[rMaxY][x] = '#';
	return placeSand() + 1;
}

int main(int argc, char* argv[])
{
	vector<string> allLines = readInput(argv[1]);
	cout << partOne(allLines) << endl;
	cout << partTwo(allLines) << endl;
	return 0;
}
