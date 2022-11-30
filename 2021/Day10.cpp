// https://adventofcode.com/2021/day/10 - Syntax Scoring!

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>
using namespace std;

namespace Day10 {
	// #########################################################################
	// PART I

	struct CorruptSyntaxFinder {
		map<char, int> scoring = { {')', 3}, {']', 57}, {'}', 1197}, {'>', 25137} };
		int sum_;

		CorruptSyntaxFinder(string filename) {
			ifstream file(filename);
			sum_ = 0;

			if (file.is_open()) {
				while (!file.eof()) {
					string line;
					file >> line;
					int score = 0;
					
					vector<char> stack;
					for (int i = 0; i < line.length() && score == 0; i++) {
						char ch = line[i];
						// Add opening symbols to the stack
						if (ch == '{' || ch == '(' || ch == '[' || ch == '<') {
							stack.insert(stack.begin(), ch);
						}
						else {
							score = getClosingScore(stack, ch);
						}
					}
					sum_ += score;
					
				}
			}
		}

		int getSyntaxScore() {
			return sum_;
		}

		int getClosingScore(vector<char>& stack, char& ch) {
			map<char, char> pairs = { {'}', '{'}, {']', '['}, {'>','<'}, {')', '('} };

			// If closing smth that was never opened
			if (find(stack.begin(), stack.end(), pairs[ch]) == stack.end()) {
				return scoring[ch];
			}
			// If the closing tag does not match 
			else if (stack[0] != pairs[ch]) {
				return scoring[ch];
			}
			else {
				stack.erase(stack.begin());
			}
			return 0;

		}
	};


	int main1(string filename = "2021/data/day10.txt") {
		CorruptSyntaxFinder csf(filename);
		return csf.getSyntaxScore();
	}

	void test() {
		int answer = 26397;
		int my_response = main1("2021/data/day10-test.txt");
		cout << "My response: " << my_response << "  Expected: " << answer << "\n\n";
	}

	// ##################################################################################
	// PART II

	struct IncompleteSyntaxFinder {
		map<char, long> scoring = { {')', 1}, {']', 2}, {'}', 3}, {'>', 4} };
		vector<uint64_t> scores;

		IncompleteSyntaxFinder(string filename) {
			ifstream file(filename);

			if (file.is_open()) {
				while (!file.eof()) {
					string line;
					file >> line;
					bool isCorrupted = false;

					vector<char> stack;
					for (int i = 0; i < line.length() && isCorrupted == false; i++) {
						char ch = line[i];
						// Add opening symbols to the stack
						if (ch == '{' || ch == '(' || ch == '[' || ch == '<') 
							stack.insert(stack.begin(), ch);
						else 
							isCorrupted = isLineCorrupted(stack, ch);
					}
					
					if (!isCorrupted) 
						scores.push_back(getLineScore(stack));	
				}
			}
		}

		uint64_t getLineScore(vector<char>& stack) {
			map<char, char> pairs = { {'{', '}'}, {'[', ']'}, {'<','>'}, {'(', ')'} };
			uint64_t score = 0;
			for (int i = 0; i < stack.size(); i++) {
				score = (score * 5) + scoring[pairs[stack[i]]];
			}
			return score;
		}

		bool isLineCorrupted(vector<char>& stack, char& ch) {
			map<char, char> pairs = { {'}', '{'}, {']', '['}, {'>','<'}, {')', '('} };
			// If closing smth that was never opened
			if (find(stack.begin(), stack.end(), pairs[ch]) == stack.end()) 
				return true;
			// If the closing tag does not match 
			else if (stack[0] != pairs[ch]) 
				return true;
			// If appropriate closing, pop the opening char from the stack
			else if(stack[0] == pairs[ch])
				stack.erase(stack.begin());
				
			return false; 
		}

		uint64_t getMiddleScore() {
			std::sort(scores.begin(), scores.end());
			
			return scores[scores.size() / 2];
		}

	};

	uint64_t main2(string filename = "2021/data/day10.txt") {
		IncompleteSyntaxFinder isf(filename);
		return isf.getMiddleScore();
	}

	void printAnswers() {
		cout << "Validation: \n";
		test();
		cout << "First part: " << main1() << "\n";
		cout << "Second part: " << main2() << "\n";
	}
}