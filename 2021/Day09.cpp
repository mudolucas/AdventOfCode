// https://adventofcode.com/2021/day/9 - NAME!

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include <algorithm>
using namespace std;

namespace Day9 {

	struct Tubes {
		vector<vector<int>> grid;
		
		Tubes(string filename) {
			ifstream file(filename);

			if (file.is_open()) {
				while (!file.eof()){
					string line;
					file >> line;
					vector<int> temp;
					for (auto ch : line) {
						temp.push_back(int(ch) -48);
					}
					grid.push_back(temp);
				}
			}
		}

		bool isLowPoint(int i, int j) {
			bool answer = true;
			if (i + 1 <= 99) {
				answer = answer && grid[i][j] < grid[i + 1][j];
			}
			if (i - 1 >= 0) {
				answer = answer && grid[i][j] < grid[i - 1][j];
			}
			if (j + 1 <= 99) {
				answer = answer && grid[i][j] < grid[i][j + 1];
			}
			if (j - 1 >=0) {
				answer = answer && grid[i][j] < grid[i][j - 1];
			}
			return answer;
		}

		int sumLowPoints() {
			int sum = 0;
			for (int i = 0; i < grid.size(); i++) {
				for (int j = 0; j < grid[0].size(); j++) {
					if (isLowPoint(i, j)) {
						sum += grid[i][j] + 1;
					}
				}
			}
			return sum;
		}

		string _str(int i, int j) {
			return to_string(i) + "." + to_string(j);
		}

		// Starting at the low point
		// Recursevely look for elements that can be part of the current basin
		// While keeping track of the points visited 
		void findBasinMembers(int i, int j, set<string>& curr_basin) {
			if (i + 1 <= 99 && grid[i+1][j] != 9 && curr_basin.find(_str(i+1,j)) == curr_basin.end()) {
				curr_basin.insert(_str(i + 1, j));
				findBasinMembers(i + 1, j, curr_basin);
			}
			if (i - 1 >= 0 && grid[i-1][j] != 9 && curr_basin.find(_str(i - 1, j)) == curr_basin.end()) {
				curr_basin.insert(_str(i - 1, j));
				findBasinMembers(i - 1, j, curr_basin);
			}
			if (j + 1 <= 99 && grid[i][j+1] != 9 && curr_basin.find(_str(i, j+1)) == curr_basin.end()) {
				curr_basin.insert(_str(i, j+1));
				findBasinMembers(i, j+1, curr_basin);
			}
			if (j - 1 >= 0 && grid[i][j - 1] != 9 && curr_basin.find(_str(i, j-1)) == curr_basin.end()) {
				curr_basin.insert(_str(i, j-1));
				findBasinMembers(i, j-1, curr_basin);
			}

		}

		int getBasinSize(int i, int j) {
			set<string> curr_basin = { _str(i,j) };
			findBasinMembers(i, j, curr_basin);
			return curr_basin.size();
		}

		// Find all basins in the grid. 
		// Returns the product of the top 3 basins' size
		int basins() {
			int sum = 0;
			vector<int> sizes;
			for (int i = 0; i < grid.size(); i++) {
				for (int j = 0; j < grid[0].size(); j++) {
					if (isLowPoint(i, j)) {
						int size = getBasinSize(i, j);
						sizes.push_back(size);
					}
				}
			}
			sort(sizes.begin(), sizes.end());
			int len = sizes.size();
			return sizes[len-1]*sizes[len-2]*sizes[len-3];
		}
	};// end struct

	int main1(string filename = "2021/data/day9.txt") {
		Tubes tubes(filename);

		return tubes.sumLowPoints();
	}

	int main2(string filename = "2021/data/day9.txt") {
		Tubes tubes(filename);

		return tubes.basins();
	}

	void test() {
		int answer = 0;
		int my_response = main1("2021/data/day9-test.txt");
		cout << "My response: " << my_response << "  Expected: " << answer << "\n\n";
	}

	void printAnswers() {
		cout << "Validation: \n";
		//test();
		//cout << "First part: " << main1() << "\n";
		cout << "Second part: " << main2() << "\n";
	}
}