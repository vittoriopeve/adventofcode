#include<cstdlib>
#include<iostream>
#include<fstream>
#include<string.h>
#include<cmath>
#include "vutil.h"
#include <filesystem>
#include <set>

using namespace std;
using namespace vutil;

void move_pair(pair<int, int>& pos, pair<int, int>* next_pos, char where)
{
	if (next_pos)
	{
		if (abs(next_pos->first - pos.first) <= 1 && abs(next_pos->second - pos.second) <= 1)
			return;
		if (next_pos->second != pos.second) pos.second += (next_pos->second > pos.second) ? 1 : -1;
		if (next_pos->first != pos.first) pos.first += (next_pos->first > pos.first) ? 1 : -1;
	}
	else
		switch (where)
		{
		case 'R': pos.first++; break;
		case 'D': pos.second--; break;
		case 'L': pos.first--; break;
		case 'U': pos.second++; break;
		}
}

int main() {
	vector<string> ss;
	vutil::file_2_vector("D:\\tmp\\test.txt", ss);
	
	vector<pair<int, int>> snake_body;
	set<pair<int,int>> positions;

	for (int i = 0; i < 10; i++)
		snake_body.push_back(pair<int,int>(0, 0));
	
	for (string s : ss)
	{
		int how_many = to_int(s.substr(s.find(" ") + 1));
		for (int h = 0; h < how_many; h++)
		{
			for (int i = 0; i < snake_body.size(); i++)
			{
				move_pair(snake_body[i], (i > 0 ? &snake_body[i - 1] : 0), s[0]);
				if(i == 9) positions.insert(snake_body[i]);
			}
		}
	}

	cout << positions.size() << endl;

	system("PAUSE");
	return 0;
}
