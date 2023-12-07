#include "day7.h"
#include <iostream>
#include "../../baseutil.h"
#include <algorithm>

int combination(string to_check) {
    char c1c = 0;
    int c1 = 1;
    int c2 = 1;
    for (char c : to_check) {
        if (c1 == 1) {
            c1 = count(to_check.begin(), to_check.end(), c);
            c1c = c;
        }
        else if (c2 == 1 && c != c1c)
            c2 = count(to_check.begin(), to_check.end(), c);
    }
    if (c1 == 5) return 6;
    if (c1 == 4) return 5;
    if ((c1 == 3 && c2 == 2) || (c1 == 2 && c2 == 3)) return 4;
    if (c1 == 3) return 3;
    if (c1 == 2 && c2 == 2) return 2;
    if (c1 == 2) return 1;
    return 0;
}

int combinationJ(string to_check) {
    char c1c = 0;
    int c1 = 1;
    int c2 = 1;
    for (char c : to_check) {
        if (c == 'J')
            continue;

        if (c1 == 1) {
            c1 = count(to_check.begin(), to_check.end(), c);
            c1c = c;
        }
        else if (c2 == 1 && c != c1c)
            c2 = count(to_check.begin(), to_check.end(), c);
    }
    int Js = count(to_check.begin(), to_check.end(), 'J');
    if (Js > 0) {
        if (c1 >= c2)
            c1 += Js;
        else
            c2 += Js;
    }


    if (c1 >= 5) return 6;
    if (c1 == 4) return 5;
    if ((c1 == 3 && c2 == 2) || (c1 == 2 && c2 == 3)) return 4;
    if (c1 == 3) return 3;
    if (c1 == 2 && c2 == 2) return 2;
    if (c1 == 2) return 1;
    return 0;
}

int calcBet(const vector<string>& rows) {
    int total = 0;
    for (int i = 0; i < rows.size(); i++) {
        total += (rows.size() - i) * stoi(baseutil::splitBy(rows[i], ' ')[1]);
    }
    return total;
}

int Day7::doWork(vector<string>& rows)
{
    sort(rows.begin(), rows.end(), [](const string& a, const string& b) {
        vector<string> s1 = baseutil::splitBy(a, ' ');
        vector<string> s2 = baseutil::splitBy(b, ' ');
        int c1 = combination(s1[0]);
        int c2 = combination(s2[0]);
        if (c1 == c2) {
            vector<char> scale = { 'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2' };
            for (int i = 0; i < s1[0].size(); i++)
                if (s1[0][i] != s2[0][i]) {
                    return find(scale.begin(), scale.end(), s1[0][i]) < find(scale.begin(), scale.end(), s2[0][i]);
                }
        }
        else
            return c1 > c2;
        });

    cout << calcBet(rows) << endl;

    sort(rows.begin(), rows.end(), [](const string& a, const string& b) {
        vector<string> s1 = baseutil::splitBy(a, ' ');
        vector<string> s2 = baseutil::splitBy(b, ' ');
        int c1 = combinationJ(s1[0]);
        int c2 = combinationJ(s2[0]);
        if (c1 == c2) {
            vector<char> scale = { 'A', 'K', 'Q', 'T', '9', '8', '7', '6', '5', '4', '3', '2', 'J' };
            for (int i = 0; i < s1[0].size(); i++)
                if (s1[0][i] != s2[0][i]) {
                    return find(scale.begin(), scale.end(), s1[0][i]) < find(scale.begin(), scale.end(), s2[0][i]);
                }
        }
        else
            return c1 > c2;
        });

    cout << calcBet(rows) << endl;

    return 0;
}
