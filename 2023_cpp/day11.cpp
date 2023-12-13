#include "day11.h"
#include <iostream>
#include "../../baseutil.h"
#include <set>

int Day11::doWork(const vector<string>& rows)
{
    long long total = 0, total2 = 0;
    int space_expansion = 1, space_expansion2 = 999999;

    set<int> rows_expanded;
    for (int r = 0; r < rows.size(); r++) {
        if (find(rows[r].begin(), rows[r].end(), '#') == rows[r].end())
            rows_expanded.insert(r);
    }

    set<int> cols_expanded;
    for (int c = 0; c < rows[0].size(); c++) {
        bool found = false;
        for (string row : rows) {
            if (row[c] == '#') {
                found = true;
                break;
            }
        }
        if (!found)
            cols_expanded.insert(c);
    }

    vector<pair<int, int>> galaxies;
    for (unsigned int r = 0; r < rows.size(); r++)
        for (unsigned int c = 0; c < rows[0].size(); c++)
            if (rows[r][c] == '#')
                galaxies.push_back(make_pair(r, c));

    set<pair<int, int>> galaxies_matches;
    for (unsigned int gorig = 0; gorig < galaxies.size(); gorig++) {
        for (unsigned int gdest = 0; gdest < galaxies.size(); gdest++) {
            if (gorig == gdest)
                continue;

            if (galaxies_matches.find(make_pair(gdest, gorig)) == galaxies_matches.end()
                && galaxies_matches.find(make_pair(gorig, gdest)) == galaxies_matches.end()) {
                int row_multiplier = 0;
                int col_multiplier = 0;
                
                for (auto i = (galaxies[gorig].first < galaxies[gdest].first ? galaxies[gorig].first : galaxies[gdest].first); 
                    i <= (galaxies[gorig].first > galaxies[gdest].first ? galaxies[gorig].first : galaxies[gdest].first); i++)
                    if (rows_expanded.find(i) != rows_expanded.end())
                        row_multiplier++;
                
                for (auto i = (galaxies[gorig].second < galaxies[gdest].second ? galaxies[gorig].second : galaxies[gdest].second);
                    i <= (galaxies[gorig].second > galaxies[gdest].second ? galaxies[gorig].second : galaxies[gdest].second); i++)
                    if (cols_expanded.find(i) != cols_expanded.end())
                        col_multiplier++;

                total += abs(galaxies[gorig].first - galaxies[gdest].first);
                total += abs(galaxies[gorig].second - galaxies[gdest].second);
                total += (space_expansion * row_multiplier);
                total += (space_expansion * col_multiplier);

                total2 += abs(galaxies[gorig].first - galaxies[gdest].first);
                total2 += abs(galaxies[gorig].second - galaxies[gdest].second);
                total2 += (space_expansion2 * row_multiplier);
                total2 += (space_expansion2 * col_multiplier);

                galaxies_matches.insert(make_pair(gdest, gorig));
            }
        }
    }

    cout << "Part 1: " << total << endl;
    cout << "Part 2: " << total2 << endl;

    return 0;
}
