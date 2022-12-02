#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

vector<string> readInputVector(string fileName)
{
    ifstream fin(fileName);
    vector<string> output;
    string temp;
    while (getline(fin, temp))
    {
        output.push_back(temp);
    }
    return output;
}

vector<pair<char, char>> extractPlays(vector<string> guide)
{
	vector<pair<char, char>> result;
	for (string line : guide)
	{
		stringstream ss(line);
		string opponent;
		ss >> opponent;
		string play;
		ss >> play;
		pair<char, char> tempPair = make_pair(opponent[0], play[0]);
		result.push_back(tempPair);
	}
	return result;
}

int partOne(vector<pair<char, char>> plays)
{
	int totalScore = 0;
	map<pair<char, char>, int> cheatGuide;
	cheatGuide[make_pair('A', 'X')] = 4;
	cheatGuide[make_pair('A', 'Y')] = 8;
	cheatGuide[make_pair('A', 'Z')] = 3;
	cheatGuide[make_pair('B', 'X')] = 1;
	cheatGuide[make_pair('B', 'Y')] = 5;
	cheatGuide[make_pair('B', 'Z')] = 9;
	cheatGuide[make_pair('C', 'X')] = 7;
	cheatGuide[make_pair('C', 'Y')] = 2;
	cheatGuide[make_pair('C', 'Z')] = 6;
	for (pair<char, char> play : plays)
	{
		totalScore += cheatGuide[play];
	}
    return totalScore;
}

int partTwo(vector<pair<char, char>> plays)
{
	int totalScore = 0;
	map<pair<char, char>, int> cheatGuide;
	cheatGuide[make_pair('A', 'X')] = 3;
	cheatGuide[make_pair('A', 'Y')] = 4;
	cheatGuide[make_pair('A', 'Z')] = 8;
	cheatGuide[make_pair('B', 'X')] = 1;
	cheatGuide[make_pair('B', 'Y')] = 5;
	cheatGuide[make_pair('B', 'Z')] = 9;
	cheatGuide[make_pair('C', 'X')] = 2;
	cheatGuide[make_pair('C', 'Y')] = 6;
	cheatGuide[make_pair('C', 'Z')] = 7;
	for (pair<char, char> play : plays)
	{
		totalScore += cheatGuide[play];
	}
    return totalScore;
}

int main(int argc, char* argv[])
{
    vector<string> guide = readInputVector(argv[1]);
	vector<pair<char, char>> plays = extractPlays(guide);
    cout << partOne(plays) << endl;
    cout << partTwo(plays) << endl;
    return 0;
}  
