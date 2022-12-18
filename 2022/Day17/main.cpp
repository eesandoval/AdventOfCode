#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <map>
#define Point pair<int,int>

using namespace std;

struct Piece
{
	int shape;
	vector<Point> rock;
};

string readInput(string fileName)
{
	ifstream fin(fileName);
	string s((istreambuf_iterator<char>(fin)), (istreambuf_iterator<char>()));
	return s;
}

Piece createPiece(int highestFloor, int shape)
{
	Piece result;
	result.shape = shape % 5;
	switch (result.shape)
	{
		case 0: // horizontal line
			for (int i = 2; i < 6; i++)
				result.rock.push_back(make_pair(i, highestFloor + 3));
			break;
		case 1: // plus
			result.rock.push_back(make_pair(2, highestFloor + 4));
			result.rock.push_back(make_pair(3, highestFloor + 3));
			result.rock.push_back(make_pair(3, highestFloor + 4));
			result.rock.push_back(make_pair(3, highestFloor + 5));
			result.rock.push_back(make_pair(4, highestFloor + 4));
			break;
		case 2: // flipped L
			for (int i = 2; i < 5; i++)
				result.rock.push_back(make_pair(i, highestFloor + 3));
			result.rock.push_back(make_pair(4, highestFloor + 4));
			result.rock.push_back(make_pair(4, highestFloor + 5));
			break;
		case 3: // vertical line
			for (int i = highestFloor + 3; i < highestFloor + 7; i++)
				result.rock.push_back(make_pair(2, i));
			break;
		case 4: // square
			result.rock.push_back(make_pair(2, highestFloor + 3));
			result.rock.push_back(make_pair(3, highestFloor + 3));
			result.rock.push_back(make_pair(2, highestFloor + 4));
			result.rock.push_back(make_pair(3, highestFloor + 4));
			break;
	}
	return result;
}

bool checkCollision(vector<string> board, Piece p, char direction)
{
	int xOffset = 0, yOffset = 0;
	switch (direction)
	{
		case '>':
			for (auto pr : p.rock)
				if (pr.first == 6)
					return true;
			xOffset = 1;
			break;
		case '<':
			for (auto pr : p.rock)
				if (pr.first == 0)
					return true;
			xOffset = -1;
			break;
		case 'v':
			yOffset = -1;
			break;
	}
	for (auto pr : p.rock)
	{
		if (pr.second + yOffset == -1) // actual floor
		{
			return true;
		}
		if (board[pr.second + yOffset][pr.first + xOffset] != '.')
			return true;
	}
	return false;
}

pair<int, map<int, vector<int>>> partOne(string jets, int totalRocks = 2022)
{
	vector<string> board;
	for (int i = 0; i < 4; i++)
		board.push_back(".......");
	int jetIter = 0, trueJet = 0, highestFloor = -1, x = 0;
	map<int, vector<int>> repeats;
	for (int r = 0; r < totalRocks; r++)
	{
		while (board.size() < highestFloor + 10)
			board.push_back(".......");
		Piece p = createPiece(highestFloor + 1, r);
		if (p.shape == 0 && highestFloor >= 0 && board[highestFloor][4] == '#')
			if (repeats.find(jetIter) != repeats.end())
				repeats[jetIter].push_back(r);
			else
				repeats[jetIter] = vector<int>(1, r);
		while (true)
		{
			x = 0;
			char c = jets[jetIter];
			jetIter = (jetIter + 1) % (jets.length() - 1); // reset
			switch (c)
			{
				case '>':
					x = 1;
					break;
				case '<':
					x = -1;
					break;
			}
			if (!checkCollision(board, p, c))
				for (int i = 0; i < p.rock.size(); i++)
					p.rock[i] = make_pair(p.rock[i].first + x, p.rock[i].second);

			if (checkCollision(board, p, 'v'))
				break; // immediately stop
			for (int i = 0; i < p.rock.size(); i++)
				p.rock[i] = make_pair(p.rock[i].first, p.rock[i].second - 1);
		}
		for (auto pr : p.rock)
			board[pr.second][pr.first] = '#';
		for (int i = board.size() - 1; i >= 0; i--)
		{
			auto found = board[i].find('#');
			if (found != string::npos)
			{
				highestFloor = i;
				break;
			}
		}
	}
	return make_pair(highestFloor + 1, repeats);
}

uint64_t partTwo(string jets)
{
	int cycles = (jets.size() - 1) * 5;
	auto repeats = partOne(jets, cycles).second;
	int biggest = 0;
	for (auto entry : repeats)
		if (entry.first > biggest)
			biggest = entry.first;
	int repetition = repeats[biggest].back() - repeats[biggest].end()[-2];
	int growth = partOne(jets, repeats[biggest].back()).first - partOne(jets, repeats[biggest].end()[-2]).first;
	int start = 1000000000000 % repetition + cycles / repetition * repetition;
	return partOne(jets, start).first + growth * (1000000000000 - start) / repetition;
}

int main(int argc, char* argv[])
{
	string jets = readInput(argv[1]);
	cout << partOne(jets).first << endl;
	cout << partTwo(jets) << endl;
	return 0;
}
