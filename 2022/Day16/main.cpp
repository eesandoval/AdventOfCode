#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <unistd.h>
#include <set>
using namespace std;

struct Valve
{
	string name;
	int flowRate;
	vector<string> tunnels;
	map<string, int> tunnelsBFS;
};

vector<string> readInput(string fileName)
{
	vector<string> result;
	ifstream fin(fileName);
	string temp;
	while(getline(fin, temp))
		result.push_back(temp);
	return result;
}

map<string, Valve> valves;

int BFS(string start, string end)
{
	int result = 1;
	auto tunnels = valves[start].tunnels;
	while (true)
	{
		set<string> nextTunnels;
		for (auto tunnel : tunnels)
		{
			if (tunnel == end)
			{
				return result;
			}
			for (auto nextTunnel : valves[tunnel].tunnels)
				nextTunnels.insert(nextTunnel);
		}
		tunnels.clear();
		for (auto nt : nextTunnels)
			tunnels.push_back(nt);
		++result;
	}
	return -1;
}

void searchTunnel(set<string> opened, int pressure, string cTunnel, int time, int& maxP, bool p2 = false, bool elephant = false)
{
	if (pressure > maxP) // update maxP
	{
		maxP = pressure;
	}
	if (time <= 0) // out of time
		return;
	if (opened.find(cTunnel) == opened.end())
	{
		opened.insert(cTunnel);
		if (p2)
		{
			searchTunnel(opened, pressure + valves[cTunnel].flowRate * time, cTunnel, time - 1, maxP, p2, elephant);
			if (!elephant)
				searchTunnel(opened, pressure + valves[cTunnel].flowRate * time, "AA", 25, maxP, p2, true);
		}
		searchTunnel(opened, pressure + valves[cTunnel].flowRate * time, cTunnel, time - 1, maxP);
	}
	else
	{
		set<string> nextTunnels;
		for (auto const& tunnelBFS : valves[cTunnel].tunnelsBFS)
		{
			if (opened.find(tunnelBFS.first) == opened.end())
				nextTunnels.insert(tunnelBFS.first);
		}
		for (auto nT : nextTunnels)
			searchTunnel(opened, pressure, nT, time - valves[cTunnel].tunnelsBFS[nT], maxP, p2, elephant);
	}
}

int partOne(vector<string> allLines)
{
	vector<string> non0Valves;
	vector<string> non0ValvesAndAA;
	for (auto line : allLines)
	{
		char vN[3];
		int fR;
		char t[255];
		sscanf(line.c_str(), 
				"Valve %2s has flow rate=%d; tunnels lead to valves %[^\t\n]", vN, &fR, t);
		string tunnels(t), tunnel;
		Valve v;
		v.name = string(vN);
		v.flowRate = fR;
		stringstream ss(tunnels);
		while (!ss.eof())
		{
			getline(ss, tunnel, ',');
			if (tunnel[0] == ' ')
				tunnel = tunnel.substr(1, string::npos);
			v.tunnels.push_back(tunnel);
		}
		if (v.flowRate > 0 || v.name == "AA")
			non0ValvesAndAA.push_back(v.name);
		if (v.flowRate > 0)
			non0Valves.push_back(v.name);
		valves[v.name] = v;
	}
	sort(non0ValvesAndAA.begin(), non0ValvesAndAA.end(), greater<string>());
	sort(non0Valves.begin(), non0Valves.end(), greater<string>());
	// Setup a BFS from each tunnel to every other tunnel
	for (auto v1 : non0ValvesAndAA)
		for (auto v2 : non0Valves)
			if (v1 != v2)
				valves[v1].tunnelsBFS[v2] = BFS(v1, v2);

	int maxPressure = 0;
	set<string> AATunnel;
	AATunnel.insert("AA");
	searchTunnel(AATunnel, 0, "AA", 29, maxPressure);
	return maxPressure;
}

int partTwo(vector<string> allLines)
{
	int maxPressure = 0;
	set<string> AATunnel;
	AATunnel.insert("AA");
	searchTunnel(AATunnel, 0, "AA", 29, maxPressure, true, false);
	return maxPressure;
}

int main(int argc, char* argv[])
{
	vector<string> allLines = readInput(argv[1]);
	cout << partOne(allLines) << endl;
	cout << partTwo(allLines) << endl;
	return 0;
}
