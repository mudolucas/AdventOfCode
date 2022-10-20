// https://adventofcode.com/2021/day/4 - Binary Diagnostic

#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include "../utils/Reader.h"

using namespace std;

namespace Day4 {

	struct Tile {
		int num;
		bool isMarked;

		Tile(int n, bool b = false) {
			num = n;
			isMarked = b;
		}
	};

	struct Board {
		vector<Tile> board;
		int completed_at=0;
		int board_score = 0;

		Board(ifstream& file) {
			for (int i = 0; i < 25; i++) {
				int num;
				if (file >> num) {
					board.push_back(Tile(num));
				}
			}
		}

		// Check if this is a bingo row
		bool checkRow(int start, int step) {
			int idx = start;
			for (int i = 0; i < 5;i++) {
				if (!board[idx].isMarked) {
					return false;
				}
				idx += step;
			}
			return true;
		}

		// Check if this board has won
		bool isBingo() {
			// Check rows
			for (int i = 0; i < 21;i += 5) {
				if (checkRow(i, 1)) {
					return true;
				}
			}
			// Check columns
			for (int i = 0; i < 5; i += 1) {
				if (checkRow(i, 5)) {
					return true;
				}
			}
			return false;
		}
		
		// Sum of all unmarked numbers
		int calculateScore(int last_played) {
			int sum = 0;
			for (auto tile : board) {
				if (!tile.isMarked) {
					sum += tile.num;
				}
			};
			return sum * last_played;
		}

		// <summary>
		// Check weather board contains elem
		// Returns idx if true, otherwise -1 
		// </summary>
		int contains(int num) {
			for (int i = 0; i < 25; i++) {
				if (board[i].num == num) {
					return i;
				}
			}
			return -1;
		}

		// Mark a number in the board. Check if won
		int play(int num) {
			int idx = contains(num);
			if (idx >= 0) {
				board[idx].isMarked = true;
				if (isBingo()) {
					return calculateScore(num);
				}
				return -1;
			}
		}
	};

	class Data {
	public: 
		vector<Board> boards;
		vector<int> numbersDrawn;

		Data() {
			string filename = "2021/data/day4.txt";

			ifstream file(filename);

			if (file.is_open()) {
				string line;
				file >> line;
				stringstream ss(line);
				int num;

				// Read the sequence of number drawn for this bingo game
				while (ss >> num) {
					numbersDrawn.push_back(num);
					if (ss.peek() == ',') { // ',' <> ","
						ss.ignore();
					}
				}

				// Read the bingo boards
				while (!file.eof()) {
					Board b = Board(file);
					boards.push_back(std::move(b));
				}
			}

		}
	};


	// Play one number at a time in each board until the first completes
	int main1v1() {
		Data data;

		for (int i = 0; i < data.numbersDrawn.size(); i++) {
			for (int b = 0; b < data.boards.size(); b++) {
				int answer = data.boards[b].play(data.numbersDrawn[i]);
				if (answer > 0) {
					return answer;
				}
			}
		}


		return 0;
	}

	// Play each board until completion then return the score for the first one to win
	int main1v2() {
		Data data;
		int firstBingo = 1000;
		int boardValue = 0;

		for (int b = 0; b < data.boards.size(); b++) {
			for (int i = 0; i < data.numbersDrawn.size(); i++) {
				int answer = data.boards[b].play(data.numbersDrawn[i]);
				if (answer > 0) {
					if (i < firstBingo) {
						firstBingo = i;
						boardValue = answer;
					}
				}
			}
		}

		return boardValue;
	}

	int main2() {
		Data data;
		bool exit = false;

		for (int b = 0; b < data.boards.size(); b++) {
			exit = false;
			for (int i = 0; i < data.numbersDrawn.size() && !exit; i++) {
				int answer = data.boards[b].play(data.numbersDrawn[i]);
				if (answer > 0) {
					data.boards[b].completed_at = i;
					data.boards[b].board_score = answer;
					exit = true;
				}

			}
		}


		int idx_last = 0;
		int num_moves = -1;
		for (int b = 0; b < data.boards.size(); b++) {
			if (data.boards[b].completed_at > num_moves) {
				idx_last = b;
				num_moves = data.boards[b].completed_at;
			}
		}

		return data.boards[idx_last].board_score;
		
	}

	void printAnswers() {
		cout << "Part 1 v1: " << main1v1() << "\n";
		cout << "Part 1 v2: " << main1v2() << "\n";
		cout << "--------------------------- \n";
		cout << "Part 2: " << main2() << "\n";
	}
}