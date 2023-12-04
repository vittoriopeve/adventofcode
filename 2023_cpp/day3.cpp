#include "day3.h"
#include <iostream>
#include <set>

bool isNum(char c) {
    return c >= '0' && c <= '9';
}

vector<pair<int, int>> findNear(const vector<string>& rows, const int r, const int c, const char toAvoid) {
    vector<pair<int, int>> retval;
    //direct
    if (c > 0 && rows[r][c - 1] != toAvoid && !isNum(rows[r][c - 1]))
        retval.push_back(make_pair(r, c - 1));
    if (c < rows[r].size() - 1 && rows[r][c + 1] != toAvoid && !isNum(rows[r][c + 1]))
        retval.push_back(make_pair(r, c + 1));
    if (r > 0 && rows[r - 1][c] != toAvoid && !isNum(rows[r - 1][c]))
        retval.push_back(make_pair(r - 1, c));
    if (r < rows.size() - 1 && rows[r + 1][c] != toAvoid && !isNum(rows[r + 1][c]))
        retval.push_back(make_pair(r + 1, c));

    //diagonal
    if (r > 0 && c > 0 && rows[r - 1][c - 1] != toAvoid && !isNum(rows[r - 1][c - 1]))
        retval.push_back(make_pair(r - 1, c - 1));
    if (r > 0 && c < rows[r - 1].size() - 1 && rows[r - 1][c + 1] != toAvoid && !isNum(rows[r - 1][c + 1]))
        retval.push_back(make_pair(r - 1, c + 1));
    if (r < rows.size() - 1 && c > 0 && rows[r + 1][c - 1] != toAvoid && !isNum(rows[r + 1][c - 1]))
        retval.push_back(make_pair(r + 1, c - 1));
    if (r < rows.size() - 1 && c < rows[r + 1].size() - 1 && rows[r + 1][c + 1] != toAvoid && !isNum(rows[r + 1][c + 1]))
        retval.push_back(make_pair(r + 1, c + 1));

    return retval;
}

vector<pair<int, int>> findEqualNear(const vector<string>& rows, const int r, const int c, const char toFind) {
    vector<pair<int, int>> retval;
    //direct
    if (c > 0 && rows[r][c - 1] == toFind)
        retval.push_back(make_pair(r, c - 1));
    if (c < rows[r].size() - 1 && rows[r][c + 1] == toFind)
        retval.push_back(make_pair(r, c + 1));
    if (r > 0 && rows[r - 1][c] == toFind)
        retval.push_back(make_pair(r - 1, c));
    if (r < rows.size() - 1 && rows[r + 1][c] == toFind)
        retval.push_back(make_pair(r + 1, c));

    //diagonal
    if (r > 0 && c > 0 && rows[r - 1][c - 1] == toFind)
        retval.push_back(make_pair(r - 1, c - 1));
    if (r > 0 && c < rows[r - 1].size() - 1 && rows[r - 1][c + 1] == toFind)
        retval.push_back(make_pair(r - 1, c + 1));
    if (r < rows.size() - 1 && c > 0 && rows[r + 1][c - 1] == toFind)
        retval.push_back(make_pair(r + 1, c - 1));
    if (r < rows.size() - 1 && c < rows[r + 1].size() - 1 && rows[r + 1][c + 1] == toFind)
        retval.push_back(make_pair(r + 1, c + 1));

    return retval;
}

vector<pair<int, int>> findNumberNear(const vector<string>& rows, const int r, const int c) {
    vector<pair<int, int>> retval;
    //direct
    if (c > 0 && isNum(rows[r][c - 1]))
        retval.push_back(make_pair(r, c - 1));
    if (c < rows[r].size() - 1 && isNum(rows[r][c + 1]))
        retval.push_back(make_pair(r, c + 1));
    if (r > 0 && isNum(rows[r - 1][c]))
        retval.push_back(make_pair(r - 1, c));
    if (r < rows.size() - 1 && isNum(rows[r + 1][c]))
        retval.push_back(make_pair(r + 1, c));

    //diagonal
    if (r > 0 && c > 0 && isNum(rows[r - 1][c - 1]))
        retval.push_back(make_pair(r - 1, c - 1));
    if (r > 0 && c < rows[r - 1].size() - 1 && isNum(rows[r - 1][c + 1]))
        retval.push_back(make_pair(r - 1, c + 1));
    if (r < rows.size() - 1 && c > 0 && isNum(rows[r + 1][c - 1]))
        retval.push_back(make_pair(r + 1, c - 1));
    if (r < rows.size() - 1 && c < rows[r + 1].size() - 1 && isNum(rows[r + 1][c + 1]))
        retval.push_back(make_pair(r + 1, c + 1));

    return retval;
}

int findFirst(const vector<string>& rows, const int r, const int c) {
    int firstN = c;
    while (firstN > 0 && isNum(rows[r][firstN - 1]))
        firstN--;

    return firstN;
}

int findLast(const vector<string>& rows, const int r, const int c) {
    int lastN = c;
    while (lastN < rows[r].size() && isNum(rows[r][lastN + 1]))
        lastN++;

    return lastN;
}

int Day3::doWork(const vector<string>& rows)
{
    set<pair<int, int>> done;

    int total = 0;
    for (int r = 0; r < rows.size(); r++) {
        int first_num = -1;
        for (int c = 0; c < rows[r].size(); c++) {
            if (isNum(rows[r][c])) {
                
                if (first_num < 0) first_num = c;
                
                bool found = false;
                auto gear = findEqualNear(rows, r, c, '*');
                for (int g = 0; g < gear.size() && !found; g++) {
                    auto numbers = findNumberNear(rows, gear[g].first, gear[g].second);
                    if (numbers.size() > 1 && done.count(gear[g]) == 0) {
                        pair<int, int> fgear = make_pair(r, c);
                        for (auto n : numbers) {
                            if (fgear.first == n.first && fgear.second == n.second) continue;
                            else if (fgear.first != n.first) {
                                //riga diversa
                                int findstart = findFirst(rows, fgear.first, fgear.second);
                                int findend = findLast(rows, fgear.first, fgear.second);

                                int fN = stoi(rows[fgear.first].substr(findstart, (findend - findstart) + 1));

                                findstart = findFirst(rows, n.first, n.second);
                                findend = findLast(rows, n.first, n.second);

                                int sN = stoi(rows[n.first].substr(findstart, (findend - findstart) + 1));

                                total += fN * sN;

                                done.insert(gear[g]);

                                found = true;
                                break;
                            }
                            else if (fgear.second - n.second > 1 && !isNum(rows[fgear.first][n.second + 1])) {
                                //stessa ma divisa

                                int findstart = findFirst(rows, fgear.first, fgear.second);
                                int findend = findLast(rows, fgear.first, fgear.second);

                                int fN = stoi(rows[fgear.first].substr(findstart, (findend - findstart) + 1));

                                findstart = findFirst(rows, n.first, n.second);
                                findend = findLast(rows, n.first, n.second);

                                int sN = stoi(rows[n.first].substr(findstart, (findend - findstart) + 1));

                                total += fN * sN;

                                done.insert(gear[g]);

                                found = true;
                                break;
                            }
                            else if (n.second - fgear.second > 1 && !isNum(rows[fgear.first][fgear.second + 1])) {
                                //stessa ma divisa

                                int findstart = findFirst(rows, fgear.first, fgear.second);
                                int findend = findLast(rows, fgear.first, fgear.second);

                                int fN = stoi(rows[fgear.first].substr(findstart, (findend - findstart) + 1));

                                findstart = findFirst(rows, n.first, n.second);
                                findend = findLast(rows, n.first, n.second);

                                int sN = stoi(rows[n.first].substr(findstart, (findend - findstart) + 1));

                                total += fN * sN;

                                done.insert(gear[g]);

                                found = true;
                                break;
                            }
                        }
                    }
                }

                /*if (findNear(rows, r, c, '.').size() > 0) {
                    c = findLast(rows, r, c);
                    
                    int last_num = c;

                    total += stoi(rows[r].substr(first_num, (last_num - first_num) + 1));
                }*/
            }
            else
                first_num = -1;
        }
    }

    cout << total;


    return 0;
}
