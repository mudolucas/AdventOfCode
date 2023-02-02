// https://adventofcode.com/2021/day/8 - NAME!

#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <vector>

using namespace std;

namespace Day8 {
	// PART 1 

	int main1(string filename = "2021/data/day8.txt") {
		map<int, int> nums = { {2,0},{3,0},{4,0},{7,0} };
		ifstream file(filename);

		if (file.is_open()) {
			while (!file.eof()) {
				string line;
				file >> line;

				// Continue iterating until we reach | 
				if (line == "|") {
					for (int i = 0;i < 4;i++) {
						file >> line;
						int len = line.length();
						if (nums.find(len) != nums.end()) {
							nums[len] += 1;
						}
					}

				}
			}
		}
		// Iterating over the map using Iterator till end of map.
		map<int, int>::iterator it = nums.begin();
		int sum = 0;
		while (it != nums.end()) {
			sum += it->second;
		}

		return sum;
	}

	// -----------------------------------------------------------------
	// PART 2

	int basicDecoder(string s) {
		int len = s.length();
		if (len == 2)
			return 1;
		else if (len == 3)
			return 7;
		else if (len == 4)
			return 4;
		else if (len == 7)
			return 8;
		return -1;
	}

	int intersection(string s1, string s2) {
		int _res = 0;
		for (auto ch : s1) {
			for (auto ch2 : s2) {
				if (ch == ch2) {
					_res += 1;
				}
			}
		}
		return _res;
	}

	int findNum(map<string, int>& nums, string num) {
		for (auto i = nums.begin(); i != nums.end(); i++) {
			if (intersection(i->first, num) == num.length() && num.length() == i->first.length()) {
				return i->second;
			}
		}
	}

	void fiveDigitsDecoder(map<int, string>& modelNums, map<string, int>& nums, string toDecode) {
		// Is it 2?
		if (intersection(toDecode, modelNums[1]) == 1 && intersection(toDecode, modelNums[4]) == 2) {
			nums[toDecode] = 2;
		}
		// Is it 3?
		else if (intersection(toDecode, modelNums[1]) == 2 && intersection(toDecode, modelNums[4]) == 3){
			nums[toDecode] = 3;
		}
		// Can only be 5
		else 
			nums[toDecode] = 5;
	}

	void sixDigitsDecoder(map<int, string>& modelNums, map<string, int>& nums, string toDecode) {
		// Is it 6?
		if (intersection(toDecode, modelNums[1]) == 1 && intersection(toDecode, modelNums[4]) == 3) {
			nums[toDecode] = 6;
		}
		// Is it 9?
		else if (intersection(toDecode, modelNums[1]) == 2 && intersection(toDecode, modelNums[4]) == 4) {
			nums[toDecode] = 9;
		}
		// Can only be 0
		else
			nums[toDecode] = 0;
	}

	void completeDecoder(map<int, string>& modelNums, map<string, int>& nums, vector<string> toDecode) {
		for (int i = 0; i < toDecode.size(); i++) {
			string curr = toDecode[i];
			int curr_length = curr.length();

			// Decoding either 2, 3 or 5
			if (curr_length == 5) {
				fiveDigitsDecoder(modelNums, nums, curr);
			}
			else if (curr_length == 6) {	
				sixDigitsDecoder(modelNums, nums, curr);
			}
		}

	}

	int main2(string filename = "2021/data/day8.txt") {
		ifstream file(filename);
		int sum = 0;

		if (file.is_open()) {
			while (!file.eof()) {
				map<string, int> nums;
				map<int, string> modelNums;
				vector<string> toDecode;
				string line;

				// Read the 10 nums
				for (int i = 0;i < 10; i++) {
					file >> line;
					auto _num = basicDecoder(line);
					if (_num > 0){
						modelNums[_num] = line;
						nums[line] = _num;
					}
					else
						toDecode.push_back(line);
				}

				// Decode the 10 nums
				completeDecoder(modelNums, nums, toDecode);
				file >> line;
				// Decode the 4 digits input
				int decodedNum = 0;
				if (line == "|") {
					int exp = 3;
					for (int i = 0;i < 4;i++) {
						file >> line;
						decodedNum += (findNum(nums, line) * pow(10, exp));
						exp -= 1;
					}
				}

				sum += decodedNum;
			}
		}
		return sum;
	}

	void test() {
		int answer = 0;
		int my_response = main1("2021/data/day8-test.txt");
		cout << "My response: " << my_response << "  Expected: " << answer << "\n\n";
	}

	void printAnswers() {
		cout << "Validation: \n";
		//test();
		//cout << "First part: " << main1() << "\n";
		cout << "Second part: " << main2() << "\n";
	}
}