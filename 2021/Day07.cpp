// https://adventofcode.com/2021/day/7 - The Treachery of Whales!

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

namespace Day7 {

	struct Crabs {
		vector<int> horizontal_pos;
		size_t size;
		double mean;
		double median;
		double sd;

		Crabs(string filename) {
			ifstream file(filename);

			if (file.is_open()) {
				string line;
				file >> line;
				stringstream ss(line);
				int num;

				while (ss >> num) {
					horizontal_pos.push_back(num);
					if (ss.peek() == ',') {
						ss.ignore();
					}
				}
			}

			size = horizontal_pos.size();
			mean = getMean();
			median = getMedian();
			sd = getSD();
		}

		double getMean() {
			int sum = 0;
			for (int i = 0; i < size; i++)
				sum += horizontal_pos[i];
			return (double)sum / (double)size;
		}
		

		double getMedian() {
			std::sort(horizontal_pos.begin(), horizontal_pos.end());
			if (size % 2 == 0){
				return (horizontal_pos[size / 2 - 1] + horizontal_pos[size / 2]) / 2;
			}
			else{
				return horizontal_pos[size / 2];
			}
		}

		double getSD() {
			double var = 0.0; 

			for (int i = 0; i < size; i++) {
				var += pow(horizontal_pos[i] - mean, 2);
			}

			return sqrt(var/mean);

		}

		int calculateFuel(int destination, bool isPart2=false) {
			int fuel_cost = 0;
			if (!isPart2){
				for (int i = 0; i < size; i++) {
					int delta = horizontal_pos[i] - destination;
					fuel_cost += (delta > 0) ? delta : -delta;
				}
			}
			else {
				for (int i = 0; i < size; i++) {
					int delta = horizontal_pos[i] - destination;
					delta = (delta > 0) ? delta : -delta;
					fuel_cost += (1 + delta) * delta / 2;
				}
				
			}
			
			return fuel_cost;
		}

		int tryCandidates(int start, int end, bool isPart2 = false) {
			int lowest_cost = pow(2, 30);
			int lowest_cost_posi = 0;
			int cost;
			for (int posi = start; posi < end; posi++) {
				cost = calculateFuel(posi, isPart2);
				if (cost < lowest_cost) {
					lowest_cost = cost;
					lowest_cost_posi = posi;
				}
			}
			cout << "Position: "<< lowest_cost_posi << "\n";

			return lowest_cost;
		}
	};

	int main1(string filename = "2021/data/day7.txt") {
		Crabs crabs(filename);

		double median = crabs.median;
		double mean = crabs.mean;

		int start = 0;
		int end = 0;

		cout << "Mean: " << mean << " Median: " << median << "\n";
		// Data is right-skewed 
		if (mean >  median){
			start = (int)floor(median);
			end = (int)ceil(mean)+crabs.sd;
			
		}
		// Data is Left-skewed 
		else if (mean < median){
			start = (int)floor(mean);
			end = (int)ceil(median)+ crabs.sd;
		}
		cout << "Start: " << start << " End: " << end << "\n";
		int answer = crabs.tryCandidates(start, end);


		return answer;
	}

	int main2(string filename = "2021/data/day7.txt") {
		Crabs crabs(filename);

		double median = crabs.median;
		double mean = crabs.mean;

		int start = 0;
		int end = 0;

		cout << "Mean: " << mean << " Median: " << median << "\n";
		// Data is right-skewed 
		if (mean > median) {
			start = (int)floor(median);
			end = (int)ceil(mean) + crabs.sd;

		}
		// Data is Left-skewed 
		else if (mean < median) {
			start = (int)floor(mean);
			end = (int)ceil(median) + crabs.sd;
		}
		cout << "Start: " << start << " End: " << end << "\n";
		int answer = crabs.tryCandidates(start, end, true);


		return answer;
	}

	void test() {
		int answer = 37;
		int my_response = main1("2021/data/day7-test.txt");

		cout << "My response: " << my_response << "  Expected: " << answer << "\n\n";
	}

	void printAnswers() {
		cout << "Validation: \n";
		test();
		cout << "First part: " << main1() << "\n\n";
		cout << "Second part: " << main2() << "\n";
	}
}