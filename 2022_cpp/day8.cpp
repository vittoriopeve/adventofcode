#include<cstdlib>
#include<iostream>
#include<fstream>
#include<string.h>
#include<cmath>
#include "vutil.h"
#include <filesystem>
#include <map>

using namespace std;
using namespace vutil;

int spot(vector<string> &ss, int row, int col)
{
	int topbottomcounter = 0, bottomtopcounter = 0, leftrightcounter = 0, rightleftcounter = 0;
	auto current_max = -1;
	//top -> bottom
	for (int i = row + 1; i < ss.size(); i++)
	{
		if (current_max == -1 || ss[i][col] > current_max)
		{
			current_max = ss[i][col] < ss[row][col] ? -1 : ss[i][col];
			topbottomcounter++;

			if (current_max != -1)
				break;
		}
	}
	current_max = -1;
	//bottom -> top
	for (int i = row - 1; i >= 0; i--)
	{
		if (current_max == -1 || ss[i][col] > current_max)
		{
			current_max = ss[i][col] < ss[row][col] ? -1 : ss[i][col];
			bottomtopcounter++;

			if (current_max != -1)
				break;
		}
	}
	current_max = -1;
	//left -> right
	for (int i = col + 1; i < ss[0].size(); i++)
	{
		if (current_max == -1 || ss[row][i] > current_max)
		{
			current_max = ss[row][i] < ss[row][col] ? -1 : ss[row][i];
			leftrightcounter++;

			if (current_max != -1)
				break;
		}
	}
	current_max = -1;
	//bottom -> top
	for (int i = col - 1; i >= 0; i--)
	{
		if (current_max == -1 || ss[row][i] > current_max)
		{
			current_max = ss[row][i] < ss[row][col] ? -1 : ss[row][i];
			rightleftcounter++;

			if (current_max != -1)
				break;
		}
	}

	return topbottomcounter * bottomtopcounter * leftrightcounter * rightleftcounter;
}

int main() {
	vector<string> ss;
	vutil::file_2_vector("D:\\tmp\\test.txt", ss);
	vector<string> ss_copy = ss;
	
	for (int row = 0; row < ss.size(); row++)
	{
		auto maxer = max_element(ss[row].begin(), ss[row].end());
		auto current_max = ss[row].begin();
		//left -> right
		for (auto iter = ss[row].begin(), iter_copy = ss_copy[row].begin(); iter != ss[row].end(); iter++, iter_copy++)
		{
			if (iter == ss[row].begin() || *current_max < *iter)
			{
				if (*iter_copy != '-')
					*iter_copy = '-';

				current_max = iter;
			}

			if (*iter == *maxer)
				break;
		}
		
		current_max = ss[row].end() - 1;
		//right -> left
		for (auto iter = ss[row].end() - 1, iter_copy = ss_copy[row].end() - 1; iter != ss[row].begin(); iter--, iter_copy--)
		{
			if (iter == ss[row].end() - 1 || *current_max < *iter)
			{
				if (*iter_copy != '-')
					*iter_copy = '-';

				current_max = iter;
			}

			if (*iter == *maxer)
				break;
		}
	}

	for (int col = 0; col < ss[0].size(); col++)
	{
		char current_max = 0;
		//top -> down
		for (auto iter = ss.begin(), iter_copy = ss_copy.begin(); iter != ss.end(); iter++, iter_copy++)
		{
			if (iter == ss.begin() || current_max < (*iter)[col])
			{
				if ((*iter_copy)[col] != '-')
					(*iter_copy)[col] = '-';

				current_max = (*iter)[col];
			}
		}

		current_max = 0;
		//down -> top
		for (auto iter = ss.end() - 1, iter_copy = ss_copy.end() - 1; iter != ss.begin(); iter--, iter_copy--)
		{
			if (iter == ss.end() - 1 || current_max < (*iter)[col])
			{
				if ((*iter_copy)[col] != '-')
					(*iter_copy)[col] = '-';

				current_max = (*iter)[col];
			}
		}
	}

	int counter = 0;
	for (string s : ss_copy)
		counter += count(s.begin(), s.end(), '-');

	cout << counter << endl;

	int maxer = 0;
	for (int row = 0; row < ss.size() - 1; row++)
		for (int col = 0; col < ss[0].size(); col++)
			maxer = max(spot(ss, row, col), maxer);

	cout << maxer << endl;

	system("PAUSE");
	return 0;
}
