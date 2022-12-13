#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

struct Pair
{
	int i;
	vector<Pair> vp;
	bool isInt;
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

// splits on , and pretends [] is a quoted string
vector<string> splitString(string s)
{
	vector<string> result;
	const char* start = s.c_str();
	int nested = 0;
	for (const char* p = start; *p; p++)
	{
		if (*p == '[')
			nested++;
		else if (*p == ']')
			nested--;
		else if (*p == ',' && nested == 0)
		{
			result.push_back(string(start, p - start));
			start = p + 1;
		}
	}
	result.push_back(string(start));
	return result;
}

int isPairOrdered(Pair leftPair, Pair rightPair)
{
	if (leftPair.isInt && rightPair.isInt)
	{
		if (leftPair.i == rightPair.i)
			return -1;
		return leftPair.i < rightPair.i;
	}
	if (!leftPair.isInt && !rightPair.isInt)
	{
		for (int i = 0; i < min(leftPair.vp.size(), rightPair.vp.size()); i++)
		{
			int pairOrdered = isPairOrdered(leftPair.vp[i], rightPair.vp[i]);
			if (pairOrdered != -1)
				return pairOrdered;
		}
		Pair lp, rp;
		lp.isInt = true;
		lp.i = leftPair.vp.size();
		rp.isInt = true;
		rp.i = rightPair.vp.size();
		return isPairOrdered(lp, rp);
	}
	if (leftPair.isInt) // convert left
	{
		Pair p;
		p.isInt = false;
		p.vp.push_back(leftPair);
		return isPairOrdered(p, rightPair);
	}
	Pair p;
	p.isInt = false;
	p.vp.push_back(rightPair);
	return isPairOrdered(leftPair, p);
}

vector<Pair> generatePairs(string s)
{
	vector<Pair> result;
	if (s.empty())
		return result;
	auto allString = splitString(s);
	for (auto subString : allString)
	{
		Pair p;
		if (subString[0] == '[')
		{
			p.isInt = false;
			subString = subString.substr(1, subString.length() - 2);
			p.vp = generatePairs(subString);
		}
		else
		{
			p.isInt = true;
			p.i = stoi(subString);
		}
		result.push_back(p);
	}
	return result;
}

int partOne(vector<string> allLines)
{
	int result = 0, pairIndex = 1, i = 0;
	for (; i < allLines.size(); i += 3)
	{
		string leftString = allLines[i], rightString = allLines[i + 1];
		auto leftPairs = generatePairs(leftString);
		auto rightPairs = generatePairs(rightString);
		if (isPairOrdered(leftPairs[0], rightPairs[0]))
			result += pairIndex;
		pairIndex++;
	}
	return result;
}

int partTwo(vector<string> allLines)
{
	string pair2str = "[[2]]", pair6str = "[[6]]";
	auto pair2 = generatePairs(pair2str)[0];
	auto pair6 = generatePairs(pair6str)[0];
	int pair2Index = 1, pair6Index = 2, i = 0;
	vector<Pair> allPairs;
	for (; i < allLines.size(); i += 3)
	{
		string leftString = allLines[i], rightString = allLines[i + 1];
		auto leftPair = generatePairs(leftString)[0];
		auto rightPair = generatePairs(rightString)[0];
		allPairs.push_back(leftPair);
		allPairs.push_back(rightPair);
	}
	for (Pair p : allPairs)
	{
		if (isPairOrdered(p, pair2))
			pair2Index++;
		if (isPairOrdered(p, pair6))
			pair6Index++;
	}
	return pair2Index * pair6Index;
}

int main(int argc, char* argv[])
{
	vector<string> allLines = readInput(argv[1]);
	cout << partOne(allLines) << endl;
	cout << partTwo(allLines) << endl;
	return 0;
}  
