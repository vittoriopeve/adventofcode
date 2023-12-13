#include "day12.h"
#include <iostream>
#include "../../baseutil.h"
#include <numeric>
#include <regex>
#include <set>

int day12_do_all_stuff(const vector<string>& splitted) {
    int total_variables = count(splitted[0].begin(), splitted[0].end(), '?');
    int total_fixed = count(splitted[0].begin(), splitted[0].end(), '#');

    vector<int> numbers;
    for (string split : baseutil::splitBy(splitted[1], ','))
        numbers.push_back(stoi(split));
    int total_numbers = accumulate(numbers.begin(), numbers.end(), 0);
    string composed_pattern = ".*";
    for (int n : numbers) {
        composed_pattern += (composed_pattern == ".*" ? "" : "\\.{1,}");
        composed_pattern += "#{" + to_string(n) + "}";
    }
    composed_pattern += ".*";
    std::regex pattern(composed_pattern);

    int to_insert = total_numbers - total_fixed;
    int to_not_skip = total_variables - total_numbers;

    int counter = 0;
    int inserted = 0;
    set<string> done;
    do {
        inserted = 0;
        string copy_split = splitted[0];
        for (int i = 0; inserted < to_insert && count(copy_split.begin(), copy_split.end(), '?') > 0; i++) {
            if (static_cast<int>(counter & (static_cast<int>(pow(2, i)))) == 0) {
                copy_split.replace(copy_split.find('?'), 1, "#");
                inserted++;
            }
            else
                copy_split.replace(copy_split.find('?'), 1, ".");
        }
        if (inserted == to_insert) {
            while (count(copy_split.begin(), copy_split.end(), '?') > 0)
                copy_split.replace(copy_split.find('?'), 1, ".");

            if (done.find(copy_split) == done.end()) {
                if (regex_match(copy_split, pattern)) {
                    done.insert(copy_split);
                }
            }
        }

        counter++;
    } while (counter < pow(2, total_variables));

    return done.size();
}

int Day12::doWork(const vector<string>& rows)
{
    int total_poss = 0;
    int total_poss2 = 0;
    for (string row : rows) {
        vector<string> splitted = baseutil::splitBy(row, ' ');
        //total_poss += day12_do_all_stuff(splitted);

        splitted[0] = splitted[0] + "?" + splitted[0] + "?" + splitted[0] + "?" + splitted[0] + "?" + splitted[0];
        splitted[1] = splitted[1] + "," + splitted[1] + "," + splitted[1] + "," + splitted[1] + "," + splitted[1];
        total_poss2 += day12_do_all_stuff(splitted);
    }

    cout << "Part 1: " << total_poss << endl;
    cout << "Part 2: " << total_poss2 << endl;

    return 0;
}
