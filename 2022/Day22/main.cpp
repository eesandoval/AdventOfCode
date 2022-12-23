#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <sstream>
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

void moveOnPath(vector<string> allLines, int& ccol, int& crow, int& cdir, int nextMove, char nextDir)
{
	int colMove = 0, rowMove = 0, j;
	for (j = 0; j < nextMove; j++)
	{
		switch (cdir)
		{
			case 0: // right
				colMove = 1;
				break;
			case 1: // down
				rowMove = 1;
				break;
			case 2: // left
				colMove = -1;
				break;
			case 3: // up
				rowMove = -1;
				break;
		}
		if (colMove == 1 && (colMove + ccol >= allLines[crow].length() || allLines[crow][colMove + ccol] == ' '))
		{
			int nextPos = allLines[crow].find_first_of(".#");
			if (allLines[crow][nextPos] == '#')
				break;
			ccol = nextPos;
		}
		else if (colMove == -1 && (colMove + ccol < 0 || allLines[crow][colMove + ccol] == ' '))
		{
			int nextPos = allLines[crow].find_last_of(".#");
			if (allLines[crow][nextPos] == '#')
				break;
			ccol = nextPos;
		} 
		else if (rowMove == 1 && (rowMove + crow >= allLines.size() || 
				ccol >= allLines[rowMove + crow].length() || allLines[rowMove + crow][ccol] == ' '))
		{
			int nextPos = -1;
			while (allLines[++nextPos][ccol] == ' ');
			if (allLines[nextPos][ccol] == '#')
				break;
			crow = nextPos;
		}
		else if (rowMove == -1 && (rowMove + crow < 0 || allLines[rowMove + crow][ccol] == ' '))
		{
			int nextPos = allLines.size();
			while(ccol >= allLines[--nextPos].length() || allLines[nextPos][ccol] == ' ');
			if (allLines[nextPos][ccol] == '#')
				break;
			crow = nextPos;
		}
		else // just move
		{
			if (allLines[rowMove + crow][colMove + ccol] == '#')
				break;
			ccol += colMove, crow += rowMove;
		}
	}
	nextMove = -1;
	switch (nextDir)
	{
		case 'L':
			if (--cdir < 0)
				cdir += 4;
			break;
		case 'R':
			cdir = (cdir + 1) % 4;
			break;
	}
	nextDir = ' ';
}

int64_t partOne(vector<string> allLines)
{
	string p = allLines.back(), temp;
	allLines.erase(allLines.end() - 2, allLines.end());
	int crow = -1, ccol = -1, cdir = 0;
	for (int row = 0; row < allLines.size(); row++)
	{
		for (int col = 0; col < allLines[row].length(); col++)
		{
			if (allLines[row][col] == '.')
			{
				crow = row, ccol = col;
				break;
			}
		}
		if (crow != -1 && ccol != -1)
			break;
	}
	
	stringstream tempNum;
	int nextMove = -1;
	char nextDir = ' ';
	for (int i = 0; i < p.length(); i++)
	{
		if (isdigit(p[i]))
		{
			tempNum << p[i];
			continue;
		}
		nextMove = stoi(tempNum.str());
		tempNum.str(string());
		nextDir = p[i];
		moveOnPath(allLines, ccol, crow, cdir, nextMove, nextDir);
	}
	nextMove = stoi(tempNum.str());
	moveOnPath(allLines, ccol, crow, cdir, nextMove, ' ');
	return 1000 * (crow + 1) + 4 * (ccol + 1) + cdir;
}

// This basically guarantees my code only works for my input ... 
int determineGrid(int ccol, int crow)
{
	if (50 <= ccol <= 99 && 0 <= crow <= 49)
		return 0;
	if (100 <= ccol <= 149 && 0 <= crow <= 49)
		return 1;
	if (50 <= ccol <= 99 && 50 <= crow <= 99)
		return 2;
	if (0 <= ccol <= 49 && 100 <= crow <= 149)
		return 3;
	if (50 <= ccol <= 99 && 100 <= crow <= 149)
		return 4;
	if (0 <= ccol <= 49 && 150 <= crow <= 199)
		return 5;
	return -1; // we fell off the cube
}

bool translateGrids(int cGrid, int nGrid, int& ccol, int& crow, vector<string> allLines) // returns true if we hit #
{
	int oldccol = ccol, oldcrow = crow;
	if (cGrid == 0 && nGrid == 3) // F
	{
//		ccol = 49 - oldcrow;
//		crow = 49 + oldccol;
		crow = 149 - crow;
		ccol = 0;
	}
	else if (cGrid == 0 && nGrid == 5) // D
	{
		crow = ccol + 100;
		ccol = 0;
	}
	else if (cGrid == 1 && nGrid == 2) // A
	{
		crow = ccol;
		ccol = 99;
	}
	else if (cGrid == 1 && nGrid == 4) // B
	{
		ccol = 99;
		crow = 149 - crow;
	}
	else if (cGrid == 1 && nGrid == 5) // G
	{
		crow = 199;
		ccol = ccol - 100;
	}
	else if (cGrid == 2 && nGrid == 3) // C
	{
		ccol = crow - 50;
		crow = 100;
	}
	else if (cGrid == 4 && nGrid == 5) // E
	{
		crow = ccol + 100;
		ccol = 49;
	}
	// reversed
	else if (cGrid == 3 && nGrid == 0) // F
	{
//		ccol = oldcrow - 49;
//		crow = 49 - oldccol;
		ccol = 50;
		crow = 149 - crow;
	}
	else if (cGrid == 5 && nGrid == 0) // D
	{
		ccol = crow - 100;
		crow = 0;
	}
	else if (cGrid == 2 && nGrid == 1) // A
	{
		ccol = crow;
		crow = 49;
	}
	else if (cGrid == 4 && nGrid == 1) // B
	{
		ccol = 149;
		crow = 149 - crow;
	}
	else if (cGrid == 5 && nGrid == 1) // G
	{
		crow = 0;
		ccol = ccol + 100;
	}
	else if (cGrid == 3 && nGrid == 2) // C
	{
		crow = ccol + 50;
		ccol = 50;
	}
	else if (cGrid == 5 && nGrid == 4) // E
	{
		ccol = crow - 100;
		crow = 149;
	}
	if (allLines[crow][ccol] == '#')
	{
		crow = oldcrow;
		ccol = oldccol;
		return true;
	}
	return false;
}

void moveOnCube(vector<string> allLines, int& ccol, int& crow, int& cdir, int nextMove, char nextDir)
{
	int colMove = 0, rowMove = 0, j, currentGrid = determineGrid(ccol, crow);
	for (j = 0; j < nextMove; j++)
	{
		switch (cdir)
		{
			case 0: // right
				colMove = 1;
				break;
			case 1: // down
				rowMove = 1;
				break;
			case 2: // left
				colMove = -1;
				break;
			case 3: // up
				rowMove = -1;
				break;
		}
		currentGrid = determineGrid(ccol, crow);
		int nextGrid = determineGrid(ccol + colMove, crow + rowMove);
		if (currentGrid == nextGrid)
		{
			WALK:
			if (allLines[rowMove + crow][colMove + ccol] == '#')
				break;
			ccol += colMove, crow += rowMove;
			continue;
		}
		// forgive me for the gotos
		// colMove -> 1 is right
		// colMove -> -1 is left
		// rowMove -> 1 is down
		// rowMove -> -1 is up
		switch (currentGrid)
		{
			case 0:
				if (colMove == 1) // 0 -> 1
				{
					goto WALK;
				}
				else if (colMove == -1) // 0 -> 3
				{
					if (translateGrids(currentGrid, 3, ccol, crow,allLines))
						goto END;
				}
				else if (rowMove == 1) // 0 -> 2
				{
					goto WALK;
				}
				else if (rowMove == -1) // 0 -> 5
				{
					if (translateGrids(currentGrid, 5, ccol, crow,allLines))
						goto END;
				}
				break;
			case 1:
				if (colMove == 1) // 1 -> 4
				{
					if (translateGrids(currentGrid, 4, ccol, crow,allLines))
						goto END;
				}
				else if (colMove == -1) // 1 -> 0
				{
					// translate
					goto WALK;
				}
				else if (rowMove == 1) // 1 -> 2
				{
					if (translateGrids(currentGrid, 2, ccol, crow,allLines))
						goto END;
				}
				else if (rowMove == -1) // 1 -> 5
				{
					if (translateGrids(currentGrid, 5, ccol, crow,allLines))
						goto END;
				}
				break;
			case 2:
				if (colMove == 1) // 2 -> 1
				{
					if (translateGrids(currentGrid, 1, ccol, crow,allLines))
						goto END;
				}
				else if (colMove == -1) // 2 -> 3
				{
					if (translateGrids(currentGrid, 3, ccol, crow,allLines))
						goto END;
				}
				else if (rowMove == 1) // 2 -> 4
				{
					goto WALK;
				}
				else if (rowMove == -1) // 2 -> 0
				{
					goto WALK;
				}
				break;
			case 3:
				if (colMove == 1) // 3 -> 4
				{
					goto WALK;
				}
				else if (colMove == -1) // 3 -> 0
				{
					if (translateGrids(currentGrid, 0, ccol, crow,allLines))
						goto END;
				}
				else if (rowMove == 1) // 3 -> 5
				{
					goto WALK;
				}
				else if (rowMove == -1) // 3 -> 2
				{
					if (translateGrids(currentGrid, 2, ccol, crow,allLines))
						goto END;
				}
				break;
			case 4:
				if (colMove == 1) // 4 -> 1
				{
					if (translateGrids(currentGrid, 1, ccol, crow,allLines))
						goto END;
				}
				else if (colMove == -1) // 4 -> 3
				{
					goto WALK;
				}
				else if (rowMove == 1) // 4 -> 5
				{
					if (translateGrids(currentGrid, 5, ccol, crow,allLines))
						goto END;
				}
				else if (rowMove == -1) // 4 -> 2
				{
					goto WALK;
				}
				break;
			case 5:
				if (colMove == 1) // 5 -> 4
				{
					if (translateGrids(currentGrid, 4, ccol, crow,allLines))
						goto END;
				}
				else if (colMove == -1) // 5 -> 0
				{
					if (translateGrids(currentGrid, 0, ccol, crow,allLines))
						goto END;
				}
				else if (rowMove == 1) // 5 -> 1
				{
					if (translateGrids(currentGrid, 1, ccol, crow,allLines))
						goto END;
				}
				else if (rowMove == -1) // 5 -> 3
				{
					goto WALK;
				}
				break;
		}
	}
	END:
	nextMove = -1;
	switch (nextDir)
	{
		case 'L':
			if (--cdir < 0)
				cdir += 4;
			break;
		case 'R':
			cdir = (cdir + 1) % 4;
			break;
	}
	nextDir = ' ';
}
uint64_t partTwo(vector<string> allLines)
{
	return 0;
}

int main(int argc, char* argv[])
{
	auto allLines = readInput(argv[1]);
	cout << partOne(allLines) << endl;
	cout << partTwo(allLines) << endl;
	return 0;
}
