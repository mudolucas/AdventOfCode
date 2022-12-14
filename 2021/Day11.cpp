// https://adventofcode.com/2021/day/ - NAME!

#include <fstream>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

namespace Day11 {

	struct Posi {
		int i;
		int j;

		Posi(int _i, int _j) {
			i = _i;
			j = _j;
		}
	};

	struct DumboOctopus {
		int value;
		bool hasFlashed;

		DumboOctopus(int val, bool flash) {
			value = val;
			hasFlashed = flash;
		};
	};

	struct Cavern {
		vector<vector<DumboOctopus>> grid;

		Cavern(string filename) {
			ifstream file(filename);

			if (file.is_open()) {
				while (!file.eof()) {
					string line;
					file >> line;
					vector<DumboOctopus> temp;
					for (auto ch : line) {
						DumboOctopus octo(int(ch) - 48, false);
						temp.push_back(std::move(octo));
					}
					grid.push_back(temp);
				}
			}
		}
		
		// Advance a step in the simulation. 
		// Returns the number of octopi that have flashed in this step
		int step() {
			int flashed = 0;
			queue<Posi> q;
			
			// The energy of each octopus is increased by 1
			for (int i = 0; i < grid.size(); i++) {
				for (int j = 0; j < grid[0].size(); j++) {
					grid[i][j].value += 1;
					if (grid[i][j].value > 9) {
						q.push(Posi(i,j));
					}
				}
			}

			while (!q.empty()) {
				Posi curr = q.front();
				q.pop();

				auto& octopi = grid[curr.i][curr.j];

				if (!octopi.hasFlashed){
					flashed += 1;
					octopi.hasFlashed = true;
					octopi.value = 0;

					updateNeighbors(curr.i, curr.j, q);
				}
			}
			resetFlashes();
			return flashed;
		}

		void updateNeighbors(int i, int j, queue<Posi>& q) {
			for (int dx = -1; dx <= 1; dx++)
				for (int dy = -1; dy <= 1; dy++)
					if (dx || dy) {
						int x = i + dx, y = j + dy;
						if (x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size()) 
							if (!grid[x][y].hasFlashed) {
								grid[x][y].value += 1;
								if (grid[x][y].value > 9)
									q.push(Posi(x,y));
							}
					}
		}

		void resetFlashes() {
			for (int i = 0; i < grid.size(); i++) 
				for (int j = 0; j < grid[0].size(); j++) 
					grid[i][j].hasFlashed = false;

		}

		int simulateNSteps(int nSteps) {
			int total_flashes = 0;
			for (int s = 0; s < nSteps; s++) 
				total_flashes += step();
			
			return total_flashes;
		}

		int simusteneousFlash() {
			int flashes = -1;
			int steps = 0;
			int num_fishes = 100;

			while (flashes != num_fishes) {
				flashes = step();
				steps++;
			}

			return steps;
		}
	};

	int main1(string filename="2021/data/day11.txt") {
		Cavern c1(filename);
		return c1.simulateNSteps(100);
	}

	int main2(string filename = "2021/data/day11.txt") {
		Cavern c2(filename);
		return c2.simusteneousFlash();
	}

	void test() {
		int answer = 0;
		int my_response = main1("2021/data/day11-test.txt");
		cout << "My response: " << my_response << "  Expected: " << answer << "\n\n";
	}

	void printAnswers() {
		cout << "Validation: \n";
		test();
		cout << "First part: " << main1() << "\n";
		cout << "Second part: " << main2() << "\n";
	}
}