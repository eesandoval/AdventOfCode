#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <deque>
#include <set>

using namespace std;

struct Blueprint
{
	int ore;
	int clay;
	pair<int, int> obs;
	pair<int, int> geo;
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

int findMost(Blueprint bp, int time = 24)
{
	int most = 0;
	auto s = vector<int>{0,0,0,0,1,0,0,0,time}; // ore, clay, obs, geo, r1-r4, time
	deque<vector<int>> q;
	q.push_back(s);
	set<vector<int>> seen;
	while (q.size() > 0)
	{
		s = q.front();
		q.pop_front();
		most = max(s[3], most); // always take biggest
		if (s[8] == 0) // out of time
			continue;

		// find whats the biggest cost of ore
		int cOre = max(bp.ore, max(bp.clay, max(bp.obs.first, bp.geo.first)));
	
		// now get the rates of each resource that are not as important
		int rOre = min(s[4], cOre);
		int rClay = min(s[5], bp.obs.second);
		int rObs = min(s[6], bp.geo.second);
		int ore = min(s[0], s[8] * cOre - rOre * (s[8] - 1));
		int clay = min(s[1], s[8] * bp.obs.second - rClay * (s[8] - 1));
		int obs = min(s[2], s[8] * bp.geo.second - rObs * (s[8] - 1));

		// for BFS keep track of what we've seen and skip if the state was seen
		s = vector<int>{ore, clay, obs, s[3], rOre, rClay, rObs, s[7], s[8]};
		if (seen.find(s) != seen.end())
			continue;
		seen.insert(s);

		// Do nothing
		q.push_back(vector<int>{ore + rOre, clay + rClay, obs + rObs,
					s[3] + s[7], rOre, rClay, rObs, s[7], s[8] - 1});
		
		// Make bots in order: ore > clay > obsidian > geode
		if (ore >= bp.ore)
			q.push_back(vector<int>{ore - bp.ore + rOre, clay + rClay,
						obs + rObs, s[3] + s[7], rOre + 1, rClay, rObs,
						s[7], s[8] - 1});
		if (ore >= bp.clay)
			q.push_back(vector<int>{ore - bp.clay + rOre, clay + rClay,
						obs + rObs, s[3] + s[7], rOre, rClay + 1, rObs,
						s[7], s[8] - 1});
		if (ore >= bp.obs.first && clay >= bp.obs.second)
			q.push_back(vector<int>{ore - bp.obs.first + rOre,
						clay - bp.obs.second + rClay, obs + rObs,
						s[3] + s[7], rOre, rClay, rObs + 1, s[7], s[8] - 1});
		if (ore >= bp.geo.first && obs >= bp.geo.second)
			q.push_back(vector<int>{ore - bp.geo.first + rOre, clay + rClay,
						obs - bp.geo.second + rObs, s[3] + s[7], rOre, rClay,
						rObs, s[7] + 1, s[8] - 1});
	}
	return most;
}

vector<Blueprint> parseBlueprints(vector<string> allLines)
{

	string text = "Blueprint %d: Each ore robot costs %d ore. Each clay robot costs %d ore. Each obsidian robot costs %d ore and %d clay. Each geode robot costs %d ore and %d obsidian.";
	vector<Blueprint> blueprints(allLines.size());
	for (int i = 0; i < allLines.size(); i++)
	{
		auto line = allLines[i];
		int id;
		sscanf(line.c_str(), text.c_str(), &id, &(blueprints[i].ore), 
			&(blueprints[i].clay), &(blueprints[i].obs.first),
			&(blueprints[i].obs.second), &(blueprints[i].geo.first),
			&(blueprints[i].geo.second));
	}
	return blueprints;
}

int partOne(vector<Blueprint> blueprints)
{
	int result = 0;
	for (int i = 1; i <= blueprints.size(); i++)
		result += i * findMost(blueprints[i - 1]);
	return result;
}

int partTwo(vector<Blueprint> blueprints)
{
	int result = 1;
	for (int i = 0; i < 3; i++)
		result *= findMost(blueprints[i], 32);
	return result;
}

int main(int argc, char* argv[])
{
	auto allLines = readInput(argv[1]);
	auto blueprints = parseBlueprints(allLines);
	cout << partOne(blueprints) << endl;
	cout << partTwo(blueprints) << endl;
	return 0;
}  
