#include "day6.h"
#include <iostream>
#include <cmath>
#include <iomanip>

vector<string> splitByC(const string& row_to_split, const char splitC)
{
    vector<string> splitted;
    splitted.push_back("");

    for (char c : row_to_split)
    {
        if (c == splitC) {
            if (splitted[splitted.size() - 1].size() > 0)
                splitted.push_back("");
        }
        else
            splitted[splitted.size() - 1] += c;
    }

    return splitted;
}

template <class T>
int calculate(T max_time, T dist_to_beat) {
    T counter = 0;
    for (int i = 1; i <= max_time; i++) {
        if (i * (max_time - i) > dist_to_beat)
            counter++;
    }
    return counter;
}

int Day6::doWork(const vector<string>& rows)
{
    vector<string> splittedTime = splitByC(rows[0], ' ');
    vector<string> splittedDist = splitByC(rows[1], ' ');

    string collapsedTime = "";
    string collapsedDist = "";
    for (int time = 1; time < splittedTime.size(); time++) {
        collapsedTime += splittedTime[time];
        collapsedDist += splittedDist[time];
    }

    int total = 0;
    for (int time = 1; time < splittedTime.size(); time++) {
        int max_time = stoi(splittedTime[time]);
        int beat_dist = stoi(splittedDist[time]);
        
        if (total == 0)
            total = calculate(max_time, beat_dist);
        else
            total *= calculate(max_time, beat_dist);
    }

    cout << total << " / " << calculate(stod(collapsedTime), stod(collapsedDist)) << endl;

    return 0;
}
