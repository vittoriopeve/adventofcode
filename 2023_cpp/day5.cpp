#include "day5.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include "../../baseutil.h"

bool isNum2(char c) {
    return c >= '0' && c <= '9';
}

/*double getNumber(string s) {
    if (s.size() > 5) {
        return stod(s.substr(0, s.size() - 5) + "." + s.substr(4));
    }
    else {
        return stod("0." + std::string(5 - s.length(), '0') + s);
    }

    return 0.0;
}*/

long long getNumber(string s) {
    return std::stoll(s);
}

int Day5::doWork(const vector<string>& rows)
{
    vector<string> splitted = baseutil::splitBy(rows[0], ' ');
    vector<vector<vector<double>>> listconverted;

    for (auto row : rows) {
        if (row.empty() || !isNum2(row[0])) {
            if (listconverted.size() == 0 || listconverted[listconverted.size() - 1].size() > 0)
                listconverted.push_back({});
            continue;
        }

        vector<string> rsplit = baseutil::splitBy(row, ' ');

        vector<double> fill;
        fill.push_back(getNumber(rsplit[0]));
        fill.push_back(getNumber(rsplit[1]));
        fill.push_back(getNumber(rsplit[2]));

        listconverted[listconverted.size() - 1].push_back(fill);
    }

    long long min_val = LONG_MAX;
    long long min_val_range = LONG_MAX;

    long long seedval_min = 0;
    long long seedval_max = LONG_MAX;

    for (string seed : splitted) {
        if (!isNum2(seed[0]))
            continue;

        long long seedval = getNumber(seed);
        
        for (auto block : listconverted) {
            for (auto lines : block) {
                if (seedval >= lines[1] && seedval <= lines[1] + lines[2]) {
                    seedval = (seedval - lines[1]) + lines[0];
                    break;
                }
            }
        }

        if (min_val > seedval)
            min_val = seedval;

        if (seedval_min == 0 || seedval_max != LONG_MAX) {
            seedval_min = getNumber(seed);
            seedval_max = LONG_MAX;
        }
        else if (seedval_min > 0 && seedval_max == LONG_MAX) {
            seedval_max = getNumber(seed);
            for (auto l = seedval_min; l < seedval_min + seedval_max; l++) {
                auto seedval_range = l;
                for (auto block : listconverted) {
                    for (auto lines : block) {
                        if (seedval_range >= lines[1] && seedval_range <= lines[1] + lines[2]) {
                            seedval_range = (seedval_range - lines[1]) + lines[0];
                            break;
                        }
                    }
                }

                if (min_val_range > seedval_range)
                    min_val_range = seedval_range; 
            }
        }
    }

    cout << /*std::setprecision(std::numeric_limits<double>::max_digits10) << */min_val << " and " << min_val_range << endl;

    return 0;
}
