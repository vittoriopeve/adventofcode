#include <iostream>
#include "day1.h"

int Day1::getFirstNumber(string s) {
    for (int i = 0; i < s.size(); i++) {
        string sub = s.substr(i);
        if (sub[0] >= '0' && sub[0] <= '9') {
            return static_cast<int>(sub[0] - '0');
        }
        for (int l = 0; l < litteral.size(); l++) {
            if (sub.size() >= litteral[l].size()) {
                if (sub.substr(0, litteral[l].size()) == litteral[l]) {
                    return l;
                }
            }
        }
    }
}

int Day1::getLastNumber(string s) {
    for (int i = s.size() - 1; i >= 0; i--) {
        string sub = s.substr(0, i + 1);
        if (sub[sub.size() - 1] >= '0' && sub[sub.size() - 1] <= '9') {
            return static_cast<int>(sub[sub.size() - 1] - '0');
        }
        for (int l = 0; l < litteral.size(); l++) {
            if (sub.size() >= litteral[l].size()) {
                if (sub.substr(sub.size() - litteral[l].size(), litteral[l].size()) == litteral[l]) {
                    return l;
                }
            }
        }
    }
}

int Day1::doWork(const vector<string>& rows)
{
    litteral.insert(litteral.end(), { "zero","one","two","three","four","five","six","seven","eight","nine" });

    int total = 0;
    for (string s : rows)
        total += getFirstNumber(s) * 10 + getLastNumber(s);

    cout << total;
    return 0;
}
