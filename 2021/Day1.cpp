// https://adventofcode.com/2021/day/1 - Sonar Sweep 

#include "../utils/Reader.h"

namespace Day1{

int main1() {
	vector<int> data = TxtReader::readTxtFileAsInt("2021/data/day1.txt");
	int count = 0;

	for (int i = 1; i < data.size(); i++) {
		if (data[i] > data[i - 1]){
			count++;
		}
	}
	return count;
}

int main2() {
	vector<int> data = TxtReader::readTxtFileAsInt("2021/data/day1.txt");
	int count = 0;

	for (int i = 3; i < data.size(); i++) {
		int sum1 = data[i - 1] + data[i - 2] + data[i - 3];
		int sum2 = data[i] + data[i - 1] + data[i - 2];

		if (sum2 > sum1) {
			count++;
		}
	}

	return count;

}

}