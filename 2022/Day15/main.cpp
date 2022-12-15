#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <set>
#include <tuple>

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

int partOne(vector<string> allLines)
{
	int rowScan = 20;
	set<pair<int, int>> notBeacons;
	for (auto line : allLines)
	{
		int sx, sy, bx, by;
		sscanf(line.c_str(), "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d",
				 &sx, &sy, &bx, &by);
		int mDist = abs(sx - bx) + abs(sy - by); // get the distance from beacon to S
		// to see if we even interact with the rowScan, take the manhattan distance
		// and substract the absolute distance between the satellite and the rowScan
		int stepsToRow = mDist - abs(rowScan - sy);

		// values under 0 do not interact with the rowScan
		if (stepsToRow < 0)
			continue;

		// find each point starting from sx - stepsToRow and increment horizontally
		for (int x = sx - stepsToRow; x < sx + stepsToRow + 1; x++)
			if (x != bx || rowScan != by)
				notBeacons.insert(make_pair(x, rowScan));
	}
	return notBeacons.size();
}

vector<pair<int64_t, int64_t>> getBoundaryPoints(int x, int y, int mDist)
{
	vector<pair<int64_t, int64_t>> result;
	int64_t xt = x, yt = y + mDist;
	// check each boundary, x+mDist,y x,y-mDist, x-mDist,y, x,y+mDist
	while (xt != x + mDist || yt != y)
		result.push_back(make_pair(++xt, --yt));
	while (xt != x || yt != y - mDist)
		result.push_back(make_pair(--xt, --yt));
	while (xt != x - mDist || yt != y)
		result.push_back(make_pair(--xt, ++yt));
	while (xt != x || yt != y + mDist)
		result.push_back(make_pair(++xt, ++yt));
	return result;
}

int64_t partTwo(vector<string> allLines)
{
	int64_t maxVal = 4000000;
	vector<tuple<int64_t, int64_t, int64_t>> satellites;
	for (auto line : allLines)
	{
		int sx, sy, bx, by;
		sscanf(line.c_str(), "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d",
				 &sx, &sy, &bx, &by);
		int mDist = abs(sx - bx) + abs(sy - by); // get the distance from beacon to S
		satellites.push_back(make_tuple(sx, sy, mDist));
	}
	for (auto s : satellites)
		for (auto b : getBoundaryPoints(get<0>(s), get<1>(s), get<2>(s) + 1))
			if (b.first >= 0 && b.first <= maxVal && b.second >= 0 && b.second <= maxVal)
			{
				bool foundFreq = true;
				for (auto ss : satellites)
					if (abs(b.first - get<0>(ss)) + abs(b.second - get<1>(ss)) <= get<2>(ss))
					{
						foundFreq = false;
						break;
					}
				if (foundFreq)
					return maxVal * b.first + b.second;
			}
	return -1;
}

int main(int argc, char* argv[])
{
	vector<string> allLines = readInput(argv[1]);
	cout << partOne(allLines) << endl;
	cout << partTwo(allLines) << endl;
	return 0;
}
