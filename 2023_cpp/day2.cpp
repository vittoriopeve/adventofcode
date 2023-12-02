#include "day2.h"
#include <iostream>

void splitSpace(const string& row_to_split, vector<string>& splitted)
{
    splitted.push_back("");

    for (char c : row_to_split)
    {
        if (splitted[splitted.size()-1].size() > 0 && (c == ' ' || c == ':' || c == ',' || c == ';'))
            splitted.push_back("");
        else
            splitted[splitted.size() - 1] += c;
    }
}

int Day2::doWork(const vector<string>& rows)
{
    const int red_max = 12;
    const int green_max = 13;
    const int blue_max = 14;

    int total = 0;
    int total_pwr = 0;

    for (string row : rows) 
    {
        int red_max_row = 0;
        int green_max_row = 0;
        int blue_max_row = 0;

        vector<string> rsplitted;
        splitSpace(row, rsplitted);

        bool skipped = false;
        for (int i = 2; i < rsplitted.size()-1; i+=2) 
        {
            int val = stoi(rsplitted[i]);
            if (rsplitted[i + 1] == "red") {
                if(!skipped) skipped = val > red_max;
                if(val > red_max_row)
                    red_max_row = val;
            }
            if (rsplitted[i + 1] == "blue") {
                if(!skipped) skipped = val > blue_max;
                if (val > blue_max_row)
                    blue_max_row = val;
            }
            if (rsplitted[i + 1] == "green") {
                if(!skipped) skipped = val > green_max;
                if (val > green_max_row)
                    green_max_row = val;
            }
        }

        total_pwr += red_max_row * blue_max_row * green_max_row;
        if (!skipped)
            total += stoi(rsplitted[1]);
    }

    cout << "Total: " << total << endl << "Tot power: " << total_pwr << endl;

    return 0;
}
