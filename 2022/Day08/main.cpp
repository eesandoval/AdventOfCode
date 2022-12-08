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
	{
		result.push_back(temp);
	}
	return result;
}

int ctoi(char c)
{
	return c - '0';
}

int partOne(vector<string> allLines)
{
	int result = allLines.size() * 2 + allLines[0].length() * 2 - 4;
	bool visible = false;
	int i, j, k;
	bool nvis, svis, evis, wvis;
	for (i = 1; i < allLines.size() - 1; i++)
	{
		for (j = 1; j < allLines[i].length() - 1; j++)
		{
			nvis = true, svis = true, evis = true, wvis = true;
			// Look west
			for (k = j - 1; k >= 0 && wvis; k--)
			{
				if (ctoi(allLines[i][k]) >= ctoi(allLines[i][j]))
					wvis = false;
			}
			// Look east
			for (k = j + 1; k < allLines[i].length() && evis; k++)
			{
				if (ctoi(allLines[i][k]) >= ctoi(allLines[i][j]))
					evis = false;
			}
			// Look south
			for (k = i + 1; k < allLines.size() && svis; k++)
			{
				if (ctoi(allLines[k][j]) >= ctoi(allLines[i][j]))
					svis = false;
			}
			// Look north
			for (k = i - 1; k >= 0 && nvis; k--)
			{
				if (ctoi(allLines[k][j]) >= ctoi(allLines[i][j]))
					nvis = false;
			}
			if (nvis || svis || evis || wvis)
				result += 1;
		}
	}
	return result;
}

int partTwo(vector<string> allLines)
{
	int result = 0;
	bool visible = false;
	int i, j, k, treeCount, scenicScore;
	bool nvis, svis, evis, wvis;
	for (i = 1; i < allLines.size() - 1; i++)
	{
		for (j = 1; j < allLines[i].length() - 1; j++)
		{
			nvis = true, svis = true, evis = true, wvis = true;
			scenicScore = 1;
			// Look west
			for (k = j - 1, treeCount = 0; k >= 0 && wvis; k--, treeCount++)
			{
				if (ctoi(allLines[i][k]) >= ctoi(allLines[i][j]))
					wvis = false;
			}
			scenicScore *= treeCount;
			// Look east
			for (k = j + 1, treeCount = 0; k < allLines[i].length() && evis; k++, treeCount++)
			{
				if (ctoi(allLines[i][k]) >= ctoi(allLines[i][j]))
					evis = false;
			}
			scenicScore *= treeCount;
			// Look south
			for (k = i + 1, treeCount = 0; k < allLines.size() && svis; k++, treeCount++)
			{
				if (ctoi(allLines[k][j]) >= ctoi(allLines[i][j]))
					svis = false;
			}
			scenicScore *= treeCount;
			// Look north
			for (k = i - 1, treeCount = 0; k >= 0 && nvis; k--, treeCount++)
			{
				if (ctoi(allLines[k][j]) >= ctoi(allLines[i][j]))
					nvis = false;
			}
			scenicScore *= treeCount;
			if (scenicScore > result)
				result = scenicScore;
		}
	}
	return result;
}

int main(int argc, char* argv[])
{
	vector<string> allLines = readInput(argv[1]);
	cout << partOne(allLines) << endl;
	cout << partTwo(allLines) << endl;
	return 0;
}  
