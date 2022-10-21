// https://adventofcode.com/2021/day/6 - Lanternfish!

#include <fstream>
#include <iostream>
#include <sstream>
#include <map>

using namespace std;

namespace Day6 {

	struct Lanterfishes {
		map<long, unsigned long long int> fishes = { {0,0},{ 1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0} };
		int day_count = 0;

		Lanterfishes(string filename) {
			ifstream file(filename);

			if (file.is_open()) {
				string line;
				file >> line;
				stringstream ss(line);
				int num;

				while (ss >> num) {
					fishes[num] += 1;
					if (ss.peek() == ',') {
						ss.ignore();
					}
				}

			}
		}

		void showFishDistribution() {
			cout << "Day " << day_count << ": \n";
			for (auto i = fishes.begin(); i != fishes.end(); i++) {
				cout << i->first << ": " << i->second << endl;
			}
		}

		void stepDay() {
			map<long, unsigned long long int> next_fishes = { {0,0},{ 1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0} };
			for (auto i = fishes.rbegin(); i != fishes.rend(); i++) {
				if (i->first == 0) {
					next_fishes[8] += i->second;
					next_fishes[6] += i->second;
				}
				else {
					if (i->second > 0) {
						next_fishes[i->first - 1] = i->second;
					}
				}
			}
			fishes = move(next_fishes);
			day_count += 1;
		}

		void stepNDays(int N, bool debug=false) {
			if (debug)
				showFishDistribution();

			for (int i = 0; i < N; i++) {
				stepDay();
				if (debug)
					showFishDistribution();
			}
		}

		unsigned long long int countFishes() {
			unsigned long long int num_fishes = 0;
			for (auto i = fishes.begin(); i != fishes.end(); i++) {
				num_fishes += i->second;
			}

			return num_fishes;

		}
	};

	 int main1() {
		string filename = "2021/data/day6.txt";
		
		Lanterfishes data(filename);
		data.stepNDays(80);

		return data.countFishes();
	}

	unsigned long long int main2() {
		string filename = "2021/data/day6.txt";

		Lanterfishes data(filename);
		data.stepNDays(256);

		return data.countFishes();
	}

	void validate() {
		string filename = "2021/data/day6-test.txt";
		int answer = 5934;

		Lanterfishes data(filename);
		data.stepNDays(80);

		long my_response = data.countFishes();
		cout << "My response: " << my_response << "  Expected: " << answer << "\n\n";
	}

	void printAnswers() {
		cout << "Validation: \n";
		validate();
		cout << "First part: " << main1() << "\n";
		cout << "Second part: " << main2() << "\n";
	}
}