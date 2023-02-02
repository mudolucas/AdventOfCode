// https://adventofcode.com/2021/day/2 - Dive!

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

namespace Day2 {

	int main1() {
		int horizontal_pos = 0;
		int depth = 0;
		string filename = "2021/data/day2.txt";

		fstream myFile;
		myFile.open(filename, ios::in);

		if (myFile.is_open()) {
			string line;
			while (getline(myFile, line)) {
				// Parse the line
				int num = stoi(line.substr(line.length() - 1));
				string op = line.substr(0, line.length() - 2);

				if (op == "up") {
					depth -= num;
				}
				else if (op == "down") {
					depth += num;
				}
				else if (op == "forward") {
					horizontal_pos += num;
				}
			}
		}

		return horizontal_pos * depth;
	}

	int main2() {
		int horizontal_pos = 0;
		int depth = 0;
		int aim = 0;
		string filename = "2021/data/day2.txt";

		fstream myFile;
		myFile.open(filename, ios::in);

		if (myFile.is_open()) {
			string line;
			while (getline(myFile, line)) {
				// Parse the line
				int num = stoi(line.substr(line.length() - 1));
				string op = line.substr(0, line.length() - 2);

				if (op == "up") {
					aim -= num;
				}
				else if (op == "down") {
					aim += num;
				}
				else if (op == "forward") {
					horizontal_pos += num;
					depth += (aim * num);
				}
			}
		}
		return depth * horizontal_pos;
	}

	void printAnswers() {
		cout << "First part: " << main1() << "\n";
		cout << "Second part: " << main2() << "\n";
	}
}