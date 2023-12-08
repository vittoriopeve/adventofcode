#include "day8.h"
#include <iostream>
#include "../../baseutil.h"
#include <map>
#include <algorithm>
#include <numeric>

int day8_transform_code_number(const string& code) {
    return static_cast<int>(code[0]) * 10000 + static_cast<int>(code[1]) * 100 + static_cast<int>(code[2]);
}

template <typename Number>
Number day8_gcd(Number u, Number v) {
    while (v != 0) {
        Number r = u % v;
        u = v;
        v = r;
    }
    return u;
}

int day8_move_position(const int pos, const char direction, const string& values) {
    switch (direction) {
    case 'L':
        return day8_transform_code_number(values.substr(0, 3));
    default:
        return day8_transform_code_number(values.substr(3, 3));
    }
}

int Day8::doWork(const vector<string>& rows)
{
    string path = rows[0];
    map<int, string> values;

    for (int i = 2; i < rows.size(); i++) {
        vector<string> splitted = baseutil::splitBy(rows[i], ' ');
        values[day8_transform_code_number(splitted[0])] = splitted[2].substr(1, splitted[2].size() - 2) + splitted[3].substr(0, splitted[3].size() - 1);
    }

    int position_part_1 = day8_transform_code_number("AAA");
    
    vector<int> positions_part_2;
    for (auto val : values)
        if (val.first - ((val.first / 100) * 100) == 65)
            positions_part_2.push_back(val.first);
    
    vector<int> counters;
    for (auto pos : positions_part_2)
        counters.push_back(0);

    int counter = 0;
    while(1) {
        for (int i = 0; i < positions_part_2.size(); i++) {
            if (!counters[i]) {
                positions_part_2[i] = day8_move_position(positions_part_2[i], path[counter % path.size()], values[positions_part_2[i]]);
                if (positions_part_2[i] - ((positions_part_2[i] / 100) * 100) == 90)
                    counters[i] = counter + 1;
            }
        }
        
        if(position_part_1) position_part_1 = day8_move_position(position_part_1, path[counter % path.size()], values[position_part_1]);
        if (position_part_1 == 909090) {
            cout << "part 1: " << counter << endl;
            position_part_1 = 0;
        }

        if (positions_part_2.size() > 0 && count_if(counters.begin(), counters.end(), [](int number) {return number > 0; }) == counters.size()) {
            unsigned long long lcm = 1;
            for (auto& elem : counters)
                lcm = static_cast<unsigned long long>(elem) / day8_gcd(static_cast<unsigned long long>(elem), lcm) * lcm;
            cout << "part 2: " << lcm << endl;
            positions_part_2.clear();
        }

        if (!position_part_1 && !positions_part_2.size())
            break;

        counter++;
    }

    return 0;
}
