// https://adventofcode.com/2021/day/3 - Binary Diagnostic

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../utils/Reader.h"

using namespace std;

namespace Day3{

	void updateCounts(vector<int> & counts, string line) {
		int i = 0;
		for (char const &c : line) {
			counts[i] += int(c) -48;
			i++;
		}
	}

	void getRates(vector<int>& counts, int treshhold, int& gamma_rate, int& episilon_rate) {
		int expo = 11;
		for (int i = 0; i < 12; i++) {
			// 1 is the most common digit in the position i
			if (counts[i] > treshhold) {
				gamma_rate += pow(2, expo);
			}
			else {
				episilon_rate += pow(2, expo);
			}
			expo--;
		}
	}

	int main1() {
		int num_lines = 0;
		int gamma_rate = 0;
		int episilon_rate = 0;
		string filename = "2021/data/day3.txt";
		vector<int> counts(12);

		fstream myFile;
		myFile.open(filename, ios::in);

		if (myFile.is_open()) {
			string line;
			while (getline(myFile, line)) {
				updateCounts(counts, line);
				num_lines++;
			}
		}

		getRates(counts, int(num_lines * 0.5), gamma_rate, episilon_rate);

		return gamma_rate * episilon_rate;
	}

	// ------------------------------ DAY 2 -----------------

	int binaryToInt(string binary_num) {
		int num = 0;
		int expo = 11;
		for (int i = 0; i < 12; i++) {
			// 1 is the most common digit in the position i
			if (binary_num[i] == '1') {
				num += pow(2, expo);
			}
			expo--;
		}

		return num;
	}

	vector<string> mostCommon(vector<string> data, int posi) {
		if (data.size() == 1) {
			return data;
		}
		vector<string> ones;
		vector<string> zeros;
		for (auto line : data) {
			if (line[posi] == '1') {
				ones.push_back(line);
			}
			else {
				zeros.push_back(line);
			}
		}
		if (ones.size() >= zeros.size()) {
			return mostCommon(ones, posi + 1);
		}
		else { 
			return  mostCommon(zeros, posi + 1);
		}

	}

	vector<string> leastCommon(vector<string> data, int posi) {
		if (data.size() == 1) {
			return data;
		}
		vector<string> ones;
		vector<string> zeros;
		for (auto line : data) {
			if (line[posi] == '1') {
				ones.push_back(line);
			}
			else {
				zeros.push_back(line);
			}
		}
		if (ones.size() >= zeros.size()) {
			return leastCommon(zeros, posi + 1);
		}
		else {
			return  leastCommon(ones, posi + 1);
		}

	}

	

	int main2() {
		string filename = "2021/data/day3.txt";
		vector<string> data;

		fstream myFile;
		myFile.open(filename, ios::in);

		if (myFile.is_open()) {
			string line;
			while (getline(myFile, line)) {
				data.insert(data.end(), line);
			}
		}

		string oxygen_binary = mostCommon(data, 0)[0];
		string co2_binary = leastCommon(data, 0)[0];

		int oxygen_rating = binaryToInt(oxygen_binary);
		int co2_rating = binaryToInt(co2_binary);
		
		
		return oxygen_rating * co2_rating;
	
		
		
	}

	void printAnswers() {
		cout << "Part 1:" << main1() << "\n";
		cout << "Part 2:" << main2() << "\n";
	}
	
}