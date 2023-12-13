#include "day13.h"
#include <iostream>
#include "../../baseutil.h"
#include <numeric>
#include <regex>
#include <set>

vector<string> day13_vector_reverse(const vector<string>& rows, const int start, const int end) {
    vector<string> reversed(rows[start].size());
    for (int i = start; i < end; i++)
        for (int j = 0; j < rows[i].size(); j++)
            reversed[j] += rows[i][j];

    return reversed;
}

bool day13_differ_for_one_char(const string& s1, const string& s2) {
    bool change_done = false;

    for (int i = 0; i < s1.size(); i++) {
        if (s1[i] != s2[i]) {
            if (!change_done)
                change_done = true;
            else
                return false;
        }
    }

    return true;
}

int day13_perform_calc(const vector<string>& rows, const int start, const int end, const bool perform_fix) {
    for (int check = start; check < end; check++) {
        if (check + 1 < rows.size() && !rows[check+1].empty()) {
            bool first_allowed = false;
            bool is_eq = rows[check] == rows[check + 1];
            if (!is_eq && perform_fix) {
                first_allowed = true;
                is_eq = day13_differ_for_one_char(rows[check], rows[check + 1]);
            }
            if (is_eq) {
                bool all_ok = true;
                for (int mid1 = check-1, mid2 = check + 2; mid1 >= start && mid2 < end && all_ok; mid1--, mid2++) {
                    all_ok = rows[mid1] == rows[mid2];
                    if (!all_ok && perform_fix && !first_allowed) {
                        first_allowed = true;
                        all_ok = day13_differ_for_one_char(rows[mid1], rows[mid2]);
                    }
                }
                if (all_ok)
                    return (check - start) + 1;
            }
        }
    }

    return 0;
}

int day13_do_check(const vector<string>& rows, const int start, const int end, const bool perform_fix = false) {
    //horizontal
    int res1 = day13_perform_calc(rows, start, end, perform_fix);
    if (!res1) {
        //vertical
        vector<string> rows_reversed = day13_vector_reverse(rows, start, end);
        return day13_perform_calc(rows_reversed, 0, rows_reversed.size() - 1, perform_fix);
    }
    else
        return res1 * 100;
}

int Day13::doWork(const vector<string>& rows)
{
    int total1 = 0;
    int start = 0;
    int end = 0;
    for (string row : rows) {
        if (row.empty()) {
            total1 += day13_do_check(rows, start, end);
            start = end + 1;
        }

        end++;
    }

    total1 += day13_do_check(rows, start, end);

    int total2 = 0;
    start = 0;
    end = 0;
    for (string row : rows) {
        if (row.empty()) {
            total2 += day13_do_check(rows, start, end, true);
            start = end + 1;
        }

        end++;
    }

    total2 += day13_do_check(rows, start, end, true);

    cout << "Part 1: " << total1 << endl;
    cout << "Part 2: " << total2 << endl;

    return 0;
}
