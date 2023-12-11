#include "day9.h"
#include <iostream>
#include "../../baseutil.h"
#include <algorithm>

void day9_split_into_nums(vector<int>& splitted, const string& row) {
    vector<string> spl = baseutil::splitBy(row, ' ');
    for (string s : spl) {
        splitted.push_back(stoi(s));
    }
}

vector<int> day9_find_differences(vector<int>& numbers) {
    vector<int> results;
    for (unsigned int i = 0; i < numbers.size()-1; i++) {
        results.push_back(numbers[i + 1] - numbers[i]);
    }
    return results;
}

int Day9::doWork(const vector<string>& rows)
{
    int total_forward = 0, total_backward = 0;

    for (const string& row : rows) {
        vector<vector<int>> splitted_numbers{ {} };
        day9_split_into_nums(splitted_numbers[0], row);

        while (count_if(splitted_numbers.back().begin(), splitted_numbers.back().end(), [](int number) {return number != 0;}) > 0) {
            splitted_numbers.push_back(day9_find_differences(splitted_numbers.back()));
        }

        for (int i = splitted_numbers.size() - 2, prev_number = 0; i >= 0; i--) {
            prev_number = splitted_numbers[i].back() + prev_number;
            splitted_numbers[i].push_back(prev_number);
        }

        for (int i = splitted_numbers.size() - 2, prev_number = 0; i >= 0; i--) {
            prev_number = *(splitted_numbers[i].begin()) - prev_number;
            splitted_numbers[i].insert(splitted_numbers[i].begin(), prev_number);
        }

        total_forward += splitted_numbers[0].back();

        total_backward += *(splitted_numbers[0].begin());
    }

    cout << "Part 1: " << total_forward << endl;
    cout << "Part 2: " << total_backward << endl;

    return 0;
}
