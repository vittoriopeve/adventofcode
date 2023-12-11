#include "day10.h"
#include <iostream>
#include "../../baseutil.h"
#include <set>

bool day10_check_positions(const set<pair<int, int>>& positions, const pair<int,int>& pos) {
    return positions.find(pos) == positions.end();
}

pair<int, int> day10_go_up(const pair<int, int>& pos) {
    return make_pair(pos.first - 1, pos.second);
}

pair<int, int> day10_go_left(const pair<int, int>& pos) {
    return make_pair(pos.first, pos.second - 1);
}

pair<int, int> day10_go_right(const pair<int, int>& pos) {
    return make_pair(pos.first, pos.second + 1);
}

pair<int, int> day10_go_down(const pair<int, int>& pos) {
    return make_pair(pos.first + 1, pos.second);
}

bool day10_check_up(const vector<string>& rows, const pair<int,int>& pos, const set<pair<int, int>>& positions) {
    pair<int, int> dest = day10_go_up(pos);
    if (dest.first >= 0 && day10_check_positions(positions, dest)) {
        switch (rows[dest.first][dest.second]) {
        case '|':
        case '7':
        case 'F':
            return true;
        }
    }

    return false;
}

bool day10_check_left(const vector<string>& rows, const pair<int, int>& pos, set<pair<int, int>>& positions) {
    pair<int, int> dest = day10_go_left(pos);
    if (dest.second >= 0 && day10_check_positions(positions, dest)) {
        switch (rows[dest.first][dest.second]) {
        case '-':
        case 'L':
        case 'F':
            return true;
        }
    }

    return false;
}

bool day10_check_right(const vector<string>& rows, const pair<int, int>& pos, set<pair<int, int>>& positions) {
    pair<int, int> dest = day10_go_right(pos);
    if (dest.second < rows[0].size() && day10_check_positions(positions, dest)) {
        switch (rows[dest.first][dest.second]) {
        case '-':
        case 'J':
        case '7':
            return true;
        }
    }

    return false;
}

bool day10_check_down(const vector<string>& rows, const pair<int, int>& pos, set<pair<int, int>>& positions) {
    pair<int, int> dest = day10_go_down(pos);
    if (dest.first < rows.size() && day10_check_positions(positions, dest)) {
        switch (rows[dest.first][dest.second]) {
        case '|':
        case 'L':
        case 'J':
            return true;
        }
    }

    return false;
}

int Day10::doWork(const vector<string>& rows)
{
    set<pair<int, int>> positions, initial_positions;
    for (unsigned int r = 0; r < rows.size() && positions.size() == 0; r++)
        for (unsigned int c = 0; c < rows[0].size() && positions.size() == 0; c++)
            if (rows[r][c] == 'S')
                initial_positions.insert(make_pair(r, c));
    
    int total_cycles = 0;
    while (initial_positions.size() > 0) {
        auto clone_positions = std::move(initial_positions);
        initial_positions.clear();
        for (pair<int, int> pos : clone_positions) {
            switch (rows[pos.first][pos.second]) {
            case '|': 
                if(day10_check_up(rows, pos, positions)) initial_positions.insert(day10_go_up(pos));
                if(day10_check_down(rows, pos, positions)) initial_positions.insert(day10_go_down(pos));
                break;
            case '-': 
                if(day10_check_left(rows, pos, positions)) initial_positions.insert(day10_go_left(pos));
                if(day10_check_right(rows, pos, positions)) initial_positions.insert(day10_go_right(pos));
                break;
            case 'L': 
                if(day10_check_up(rows, pos, positions)) initial_positions.insert(day10_go_up(pos));
                if(day10_check_right(rows, pos, positions)) initial_positions.insert(day10_go_right(pos));
                break;
            case 'J': 
                if(day10_check_up(rows, pos, positions)) initial_positions.insert(day10_go_up(pos));
                if(day10_check_left(rows, pos, positions)) initial_positions.insert(day10_go_left(pos));
                break;
            case '7': 
                if(day10_check_left(rows, pos, positions)) initial_positions.insert(day10_go_left(pos));
                if(day10_check_down(rows, pos, positions)) initial_positions.insert(day10_go_down(pos));
                break;
            case 'F': 
                if(day10_check_right(rows, pos, positions)) initial_positions.insert(day10_go_right(pos));
                if(day10_check_down(rows, pos, positions)) initial_positions.insert(day10_go_down(pos));
                break;
            case 'S': 
                if(day10_check_up(rows, pos, positions)) initial_positions.insert(day10_go_up(pos));
                if(day10_check_left(rows, pos, positions)) initial_positions.insert(day10_go_left(pos));
                if(day10_check_right(rows, pos, positions)) initial_positions.insert(day10_go_right(pos));
                if(day10_check_down(rows, pos, positions)) initial_positions.insert(day10_go_down(pos));
                break;
            }
        }

        if (initial_positions.size() > 0)
            total_cycles++;

        for (auto iter : initial_positions)
            positions.insert(iter);
    }

    cout << "Part 1: " << total_cycles << endl;

    return 0;
}
