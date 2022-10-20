// https://adventofcode.com/2021/day/5 - NAME!

#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;

namespace Day5 {

	struct Field {
		vector<vector<int>> grid;
		int N;

		// int vec[1000][1000]; // <- stack overflow, should use heap (e.g. new)

		Field(int n) {
			N = n;
			for (int i = 0; i < N;i++) {
				vector<int> temp;
				for (int j = 0; j < N;j++) {
					temp.push_back(0);
				}
				grid.push_back(temp);
			}
		}

		void updateLinesAndDiagonals(vector<int> coord, bool shouldUpdateDiagnonals) {
			// Unpack coordinates to more redable var names
			int x1 = coord[0], y1 = coord[1], x2 = coord[2], y2 = coord[3];

			// Row
			if (y1 == y2) {
				int min = (x1 > x2) ? x2 : x1;
				int max = (x1 > x2) ? x1 : x2;

				for (int j = min; j <= max; j++) {
					grid[y1][j] += 1;
				}
			}
			// Column
			else if (x1 == x2) {
				int min = (y1 > y2) ? y2 : y1;
				int max = (y1 > y2) ? y1 : y2;

				for (int i = min; i <= max; i++) {
					grid[i][x1] += 1;
				}
			}
			else if (shouldUpdateDiagnonals) {
				vector<int> xs;
				if (x1 > x2) {
					for (int x = x1; x >= x2; x--) {
						xs.push_back(x);
					}
				}
				else {
					for (int x = x1; x <= x2; x++) {
						xs.push_back(x);
					}
				}

				vector<int> ys;
				if (y1 > y2) {
					for (int y = y1; y >= y2; y--) {
						ys.push_back(y);
					}
				}
				else {
					for (int y = y1; y <= y2; y++) {
						ys.push_back(y);
					}
				}

				for (int i = 0; i < xs.size(); i++) {
					grid[ys[i]][xs[i]] += 1;
				}
			}
		}

		int findOverlaps() {
			int count_overlap = 0;
			for (int i = 0; i < N;i++) {
				for (int j = 0; j < N;j++) {
					if (grid[i][j] >= 2) {
						count_overlap += 1;
					}
				}
			}
			return count_overlap;
		}
	};

	void readData(Field& f, string filename, bool shouldUpdateDiagonals) {
		ifstream file(filename);

		if (file.is_open()) {
			while (!file.eof()) {
				vector<int> coord = { -1,-1,-1,-1 };
				int x, y;
				char ch;
				int i = 0;

				while (coord[3] == -1) {
					string line;
					file >> line;
					stringstream ss(line);

					if (line != "->") {
						ss >> x;
						ss >> ch;
						ss >> y;
						coord[i] = x;
						coord[i + 1] = y;
						i += 2;
					}
				}
				f.updateLinesAndDiagonals(coord, shouldUpdateDiagonals);
			}
		}
	}

	void test() {
		int answer = 5;
		Field f(10);
		readData(f, "2021/data/day5-test.txt", false);
		int my_response = f.findOverlaps();
		cout << "My response: " << my_response << "  Expected: " << answer << "\n\n";
	}

	int main1() {
		Field f(1000);
		readData(f, "2021/data/day5.txt", false);
		return f.findOverlaps();
	}

	int main2() {
		Field f(1000);
		readData(f, "2021/data/day5.txt", true);
		return f.findOverlaps();
	}

	void printAnswers() {
		cout << "Validation: \n";
		test();
		cout << "First part: " << main1() << "\n";
		cout << "Second part: " << main2() << "\n";
	}
}