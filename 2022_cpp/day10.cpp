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

void draw(int &cycle_number, const int Xregister)
{
	int registerToUse = Xregister + ((cycle_number / 40) * 40);
	cout << (cycle_number >= registerToUse - 1 && cycle_number <= registerToUse + 1 ? "#" : ".");
	if ((cycle_number+1) % 40 == 0)
		cout << endl;
	cycle_number++;
}

int main() {
	vector<string> ss;
	vutil::file_2_vector("D:\\tmp\\test.txt", ss);
	
	int Xregister = 1;
	int cycle_number = 0;
	int next_cycle = 20;
	int sumXregister = 0;

	for (string s : ss)
	{
		if (s == "noop")
			draw(cycle_number, Xregister);
		else
		{
			draw(cycle_number, Xregister);
			draw(cycle_number, Xregister);
		}

		if (cycle_number >= next_cycle)
		{
			sumXregister += (Xregister * next_cycle);
			if (next_cycle > 220)
				break;
		}

		if (s != "noop")
			Xregister += to_int(s.substr(s.find(" ") + 1));
	}

	cout << endl << sumXregister << endl;

	system("PAUSE");
	return 0;
}
