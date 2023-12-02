#include <string>
#include <vector>

using namespace std;

class Day1 {
public:
	vector<string> litteral;

	int doWork(const vector<string>& rows);
private:
	int getFirstNumber(string s);
	int getLastNumber(string s);
};