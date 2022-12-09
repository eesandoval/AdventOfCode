#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <tuple>
#include <set>

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

int snakeMovement(vector<string> allLines, int snakeSize)
{
	int step;
	vector<tuple<int, int>> tails;
	for (int i = 0; i < snakeSize; i++)
		tails.push_back(make_tuple(1000, 1000));
	tuple<int, int> head (1000, 1000), newHead (1000, 1000);
	set<tuple<int, int>> visited;
	visited.insert(make_tuple(1000, 1000));
	char direction;
	for (auto line : allLines)
	{
		sscanf(line.c_str(), "%c %d", &direction, &step);
		for (int i = 0; i < step; i++)
		{
			switch(direction)
			{
				case 'R':
					get<0>(head)++;
					break;
				case 'U':
					get<1>(head)++;
					break;
				case 'L':
					get<0>(head)--;
					break;
				case 'D':
					get<1>(head)--;
					break;
			}
			for (int t = 0; t < tails.size(); t++)
			{
				if (t == 0)
				{
					newHead = make_tuple(get<0>(head), get<1>(head));
				}
				else
				{
					newHead = make_tuple(get<0>(tails[t-1]), get<1>(tails[t-1]));
				}
				if (abs(get<0>(tails[t])-get<0>(newHead)) <= 1 && abs(get<1>(tails[t])-get<1>(newHead)) <= 1)
				{
					continue;
				}
				if (get<0>(tails[t]) != get<0>(newHead) && get<1>(tails[t]) != get<1>(newHead)) // neither x or y match, diagonal
				{
					if (get<1>(newHead)-get<1>(tails[t]) == 2 && get<0>(newHead)-get<0>(tails[t]) == 2) // its far up right
					{
						get<0>(tails[t])++;
						get<1>(tails[t])++;
					}

					else if (get<1>(newHead)-get<1>(tails[t]) == 2 && get<0>(newHead)-get<0>(tails[t]) == -2) // its far up left
					{
						get<0>(tails[t])--;
						get<1>(tails[t])++;
					}
					else if (get<1>(newHead)-get<1>(tails[t]) == -2 && get<0>(newHead)-get<0>(tails[t]) == 2) // its far down right
					{
						get<0>(tails[t])++;
						get<1>(tails[t])--;
					}
					else if (get<1>(newHead)-get<1>(tails[t]) == -2 && get<0>(newHead)-get<0>(tails[t]) == -2) // its far down left
					{
						get<0>(tails[t])--;
						get<1>(tails[t])--;
					}
					else if (get<1>(newHead)-get<1>(tails[t]) == 2) // it went up, align the x and have y - 1
					{
						get<0>(tails[t]) = get<0>(newHead);
						get<1>(tails[t]) = get<1>(newHead) - 1;
					}
					else if (get<1>(newHead)-get<1>(tails[t]) == -2) // it went down, align the x and have y + 1
					{
						get<0>(tails[t]) = get<0>(newHead);
						get<1>(tails[t]) = get<1>(newHead) + 1;
					}
					else if (get<0>(newHead)-get<0>(tails[t]) == 2) // it went right, align the y and have x - 1
					{
						get<1>(tails[t]) = get<1>(newHead);
						get<0>(tails[t]) = get<0>(newHead) - 1;
					}
					else // it went left, align the y and have x + 1
					{
						get<1>(tails[t]) = get<1>(newHead);
						get<0>(tails[t]) = get<0>(newHead) + 1;
					}
				}
				else if (get<0>(tails[t]) == get<0>(newHead)) // x matches, move up or down
				{
					if (get<1>(tails[t]) < get<1>(newHead)) // newHead went up
						get<1>(tails[t])++;
					else // else it went down
						get<1>(tails[t])--;
				}
				else if (get<1>(tails[t]) == get<1>(newHead)) // y matches, move left or right
				{
					if (get<0>(tails[t]) > get<0>(newHead)) // newHead went left
						get<0>(tails[t])--;
					else // else it went right
						get<0>(tails[t])++;
				}
			}
			visited.insert(tails[snakeSize-1]);
		}
		
	}
	return visited.size();
}

int partOne(vector<string> allLines)
{
	return snakeMovement(allLines, 1);
}

int partTwo(vector<string> allLines)
{
	return snakeMovement(allLines, 9);
}

int main(int argc, char* argv[])
{
	vector<string> allLines = readInput(argv[1]);
	cout << partOne(allLines) << endl;
	cout << partTwo(allLines) << endl;
	return 0;
}  
