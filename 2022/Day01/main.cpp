#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

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

vector<int> sumAllCalories(vector<string> allCalories)
{
	int tempTotalCalories = 0;
	vector<int> summedCalories;
	for (string calorieStr : allCalories)
	{
		if (calorieStr.empty())
		{
			summedCalories.push_back(tempTotalCalories);
			tempTotalCalories = 0;
		}
		else
		{
			tempTotalCalories += stoi(calorieStr);
		}
	}
	summedCalories.push_back(tempTotalCalories);
	sort(summedCalories.begin(), summedCalories.end(), greater<int>());
	return summedCalories;
}

int partOne(vector<int> summedCalories)
{
	return summedCalories[0];
}

int partTwo(vector<int> summedCalories)
{
	int result = 0;
	for (int i = 0; i < 3; i++)
	{
		result += summedCalories[i];
	}
	return result;
}

int main(int argc, char* argv[])
{
	vector<string> allCalories = readInputVector(argv[1]);
	vector<int> summedCalories = sumAllCalories(allCalories);
	cout << partOne(summedCalories) << endl;
	cout << partTwo(summedCalories) << endl;
	return 0;
}  
