#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <deque>
#include <set>
#include <map>
#include <algorithm>
#define Point pair<int,int>

using namespace std;

struct Blizzard
{
	Point curPos;
	char direction;
};

vector<string> readInput(string fileName)
{
	ifstream fin(fileName);
	vector<string> output;
	string temp;
	while (getline(fin, temp))
		output.push_back(temp);
	return output;
}

vector<Blizzard> getBlizzards(vector<string> allLines)
{
	vector<Blizzard> result;
	for (int i = 0; i < allLines.size(); i++)
		for (int j = 0; j < allLines[i].length(); j++)
			if (allLines[i][j] != '.' && allLines[i][j] != '#')
			{
				Blizzard b;
				b.curPos = make_pair(j, i);
				b.direction = allLines[i][j];
				result.push_back(b);
			}
	return result;
}

map<int, vector<Blizzard>> calculateAllBlizzards(vector<Blizzard> blizzards, int height, int width)
{
	map<int, vector<Blizzard>> result;
	for (auto b : blizzards)
	{
		result[0].push_back(b);
	}
	for (int time = 1; time <= width - 3; time++) // > and <
	{
		for (auto b : blizzards)
		{
			Blizzard b2;
			if (b.direction == '>')
			{
				b2.curPos = make_pair(b.curPos.first + 1, b.curPos.second);
				if (b2.curPos.first == width - 1)
					b2.curPos.first = 1;
			}
			else if (b.direction == '<')
			{
				b2.curPos = make_pair(b.curPos.first - 1, b.curPos.second);
				if (b2.curPos.first == 0)
					b2.curPos.first = width - 2;
			}
			else
			{
				continue;
			}
			result[time].push_back(b2);
		}
	}
	
	for (int time = 1; time <= height - 3; time++) // v and ^
	{
		for (auto b : blizzards)
		{
			Blizzard b2;
			if (b.direction == 'v')
			{
				b2.curPos = make_pair(b.curPos.first, b.curPos.second + 1);
				if (b2.curPos.second == height - 1)
					b2.curPos.second = 1;
			}
			else if (b.direction == '^')
			{
				b2.curPos = make_pair(b.curPos.first, b.curPos.second - 1);
				if (b2.curPos.second == 0)
					b2.curPos.second = height - 2;
			}
			else
			{
				continue;
			}
			result[time].push_back(b2);
		}
	}
	return result;
}

vector<pair<Point, int>> getValidMovements(vector<Blizzard> blizzards, Point curPos, int time)
{
	vector<pair<Point, int>> validMovements;
	vector<Point> blizzardPos;
	for (auto b : blizzards)
		blizzardPos.push_back(b.curPos);
	if (find(blizzardPos.begin(), blizzardPos.end(), make_pair(curPos.first, curPos.second + 1)) == blizzardPos.end())
		validMovements.push_back(make_pair(make_pair(curPos.first, curPos.second + 1), time));
	else if (find(blizzardPos.begin(), blizzardPos.end(), make_pair(curPos.first, curPos.second - 1)) == blizzardPos.end())
		validMovements.push_back(make_pair(make_pair(curPos.first, curPos.second - 1), time));
	else if (find(blizzardPos.begin(), blizzardPos.end(), make_pair(curPos.first + 1, curPos.second)) == blizzardPos.end())
		validMovements.push_back(make_pair(make_pair(curPos.first + 1, curPos.second), time));
	else if (find(blizzardPos.begin(), blizzardPos.end(), make_pair(curPos.first - 1, curPos.second)) == blizzardPos.end())
		validMovements.push_back(make_pair(make_pair(curPos.first - 1, curPos.second), time));
	return validMovements;
}

uint64_t partOne(vector<string> allLines)
{
	Point curPos = make_pair(1, 0);
	Point end = make_pair(allLines[0].length() - 2, allLines.size() - 1);
	deque<pair<Point, int>> q;
	set<pair<Point, int>> seen;
	q.push_back(make_pair(curPos, 0));
	seen.insert(make_pair(curPos, 0));
	auto blizzards = getBlizzards(allLines);
	auto allBlizzards = calculateAllBlizzards(blizzards, allLines[0].length(), allLines.size());
	while (q.size() > 0)
	{
		auto p = q.front();
		q.pop_front();
		if (p.first == end)
			return p.second;
		auto nextBlizzards = allBlizzards[p.second + 1];
		auto nextMovements = getValidMovements(nextBlizzards, p.first, (p.second + 1) % (allLines[0].length() * allLines.size()));
		for (auto nM : nextMovements)
		{
			if (find(seen.begin(), seen.end(), nM) == seen.end())
			{
				seen.insert(nM);
				q.push_back(nM);
			}
		}
	}
	return -1;
}

uint64_t partTwo(vector<string> allLines)
{
	Point curPos = make_pair(1, 0);
	Point end = make_pair(allLines[0].length() - 2, allLines.size() - 1);
	deque<pair<Point, int>> q;
	set<pair<Point, int>> seen;
	q.push_back(make_pair(curPos, 0));
	seen.insert(make_pair(curPos, 0));
	int time;
	auto blizzards = getBlizzards(allLines);
	auto allBlizzards = calculateAllBlizzards(blizzards, allLines[0].length(), allLines.size());
	while (q.size() > 0)
	{
		auto p = q.front();
		q.pop_front();
		if (p.first == end)
		{
			time = p.second;
			break;
		}
		auto nextBlizzards = allBlizzards[p.second + 1];
		auto nextMovements = getValidMovements(nextBlizzards, p.first, (p.second + 1) % (allLines[0].length() * allLines.size()));
		for (auto nM : nextMovements)
		{
			if (find(seen.begin(), seen.end(), nM) == seen.end())
			{
				seen.insert(nM);
				q.push_back(nM);
			}
		}
	}
	auto temp = curPos;
	curPos = end;
	q.clear();
	q.push_back(make_pair(curPos, time));
	end = temp;
	while (q.size() > 0)
	{
		auto p = q.front();
		q.pop_front();
		if (p.first == end)
		{
			time += p.second;
			break;
		}
		auto nextBlizzards = allBlizzards[time];
		auto nextMovements = getValidMovements(nextBlizzards, p.first, p.second % (allLines[0].length() * allLines.size()));
		for (auto nM : nextMovements)
		{
			if (find(seen.begin(), seen.end(), nM) == seen.end())
			{
				seen.insert(nM);
				q.push_back(nM);
			}
		}
	}
	temp = curPos;
	curPos = end;
	q.clear();
	q.push_back(make_pair(curPos, time));
	end = temp;
	while (q.size() > 0)
	{
		auto p = q.front();
		q.pop_front();
		if (p.first == end)
		{
			time += p.second;
			break;
		}
		auto nextBlizzards = allBlizzards[time];
		auto nextMovements = getValidMovements(nextBlizzards, p.first, p.second % (allLines[0].length() * allLines.size()));
		for (auto nM : nextMovements)
		{
			if (find(seen.begin(), seen.end(), nM) == seen.end())
			{
				seen.insert(nM);
				q.push_back(nM);
			}
		}
	}
	return time;
}

int main(int argc, char* argv[])
{
	auto allLines = readInput(argv[1]);
	cout << partOne(allLines) << endl;
	cout << partTwo(allLines) << endl;
	return 0;
}
