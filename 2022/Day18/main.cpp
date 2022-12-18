#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <deque>
#include <climits>

using namespace std;

int max_x = 0, max_y = 0, max_z = 0, min_x = INT_MAX, min_y = INT_MAX, min_z = INT_MAX;

struct Cube
{
	int x;
	int y;
	int z;

	Cube(int cx, int cy, int cz) : x(cx), y(cy), z(cz) {}

	bool operator==(const Cube& c2) const
	{
		return x == c2.x && y == c2.y && z == c2.z;
	}

	Cube operator+(const Cube& c2) const
	{
		return Cube(x + c2.x, y + c2.y, z + c2.z);
	}
	
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

vector<Cube> parseInput(vector<string> allLines)
{
	vector<Cube> cubes;
	for (auto line : allLines)
	{
		Cube c(0,0,0);
		sscanf(line.c_str(), "%d,%d,%d", &c.x, &c.y, &c.z);
		max_x = max(c.x, max_x), max_y = max(c.y, max_y), max_z = max(c.z, max_z);
		min_x = min(c.x, min_x), min_y = min(c.y, min_y), min_z = min(c.z, min_z);
		cubes.push_back(c);
	}
	return cubes;
}

int partOne(vector<Cube> cubes)
{
	int totalSides = 0;
	for (auto cube : cubes)
	{
		int openSides = 6;
		for (auto cube2 : cubes)
		{
			if (cube == cube2)
				continue;
			if ((cube.x == cube2.x && cube.y == cube2.y && abs(cube.z - cube2.z) == 1) ||
				(cube.x == cube2.x && abs(cube.y - cube2.y) == 1 && cube.z == cube2.z) ||
				(abs(cube.x - cube2.x) == 1 && cube.y == cube2.y && cube.z == cube2.z))
				openSides--;
		}
		totalSides += max(openSides, 0);
	}
	return totalSides;
}

// Find is not cooperating so here's a function to do it
bool findCube(vector<Cube> cubes, Cube c)
{
	for (auto cube : cubes)
		if (c.x == cube.x && c.y == cube.y && c.z == cube.z)
			return true;
	return false;
}

int partTwo(vector<Cube> cubes)
{
	min_x--, min_y--, min_z--;
	max_x++, max_y++, max_z++;
	int result = 0;
	vector<Cube> adjacent;
	adjacent.push_back(Cube(1, 0, 0));
	adjacent.push_back(Cube(-1, 0, 0));
	adjacent.push_back(Cube(0, 1, 0));
	adjacent.push_back(Cube(0, -1, 0));
	adjacent.push_back(Cube(0, 0, 1));
	adjacent.push_back(Cube(0, 0, -1));
	deque<Cube> q;
	vector<Cube> seen;
	q.push_back(Cube(1, 0, 0));
	while (q.size() > 0)
	{
		auto cube = q.front();
		q.pop_front();
		if (findCube(seen, cube))
			continue;
		seen.push_back(cube);
		if (cube.x < min_x || cube.x > max_x || cube.y < min_y || cube.y > max_y || cube.z < min_z || cube.z > max_z)
			continue;
		for (auto a : adjacent)
		{
			Cube ca = cube + a;
			if (findCube(cubes, ca))
				result++;
			else if (!findCube(cubes, ca) && !findCube(seen, ca))
				q.push_back(ca);
		}
	}
	return result;
}

int main(int argc, char* argv[])
{
	vector<string> allLines = readInput(argv[1]);
	vector<Cube> cubes = parseInput(allLines);
	cout << partOne(cubes) << endl;
	cout << partTwo(cubes) << endl;
	return 0;
}  
