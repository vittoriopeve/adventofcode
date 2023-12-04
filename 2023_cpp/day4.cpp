#include "day4.h"
#include <iostream>
#include <cmath>

vector<string> splitSpace(const string& row_to_split)
{
    vector<string> splitted;
    splitted.push_back("");

    for (char c : row_to_split)
    {
        if (c == ' ') {
            if(splitted[splitted.size() - 1].size() > 0)
                splitted.push_back("");
        }
        else
            splitted[splitted.size() - 1] += c;
    }

    return splitted;
}

int Day4::doWork(const vector<string>& rows)
{
    int total = 0;
    int total2 = 0;
    vector<int> multiplier;
    for (int r = 0; r < rows.size(); r++)
        multiplier.push_back(1);

    for (int r = 0; r < rows.size();r++) {
        vector<string> splitted = splitSpace(rows[r]);

        int counter = -1;
        for (int i = 2; i < 12; i++) {
            if (find(splitted.begin() + 12, splitted.end(), splitted[i]) != splitted.end())
                counter++;
        }
        if (counter > 0)
            total += pow(2, counter);

        total2 += multiplier[r];
        for (int i = 0; i <= counter; i++) {
            if (multiplier.size() > r + i + 1) {
                multiplier[r + i + 1] += multiplier[r];
            }
        }
    }

    cout << total << "/" << total2;

    return 0;
}
