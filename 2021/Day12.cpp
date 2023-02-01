// https://adventofcode.com/2021/day/ - NAME!

#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <cstring>

using namespace std;

namespace Day12 {

	class Graph {
	private:
		vector<vector<string>> allValidPaths;
		unordered_map<string, vector<string>> _graph;

	public:
		Graph(string filename) {
			ifstream file(filename);

			if (file.is_open()) {
				while (!file.eof()) {
					string line;
					file >> line;
					stringstream ss(line);
					string start = line.substr(0, line.find("-"));
					string end = line.substr(line.find("-") + 1);

					_graph[start].push_back(end);
					_graph[end].push_back(start);

				}
			}
		}

		// Find all possible paths from start -> end 
		// traversing the graph in DFS fashion
		void findAllPaths(string start, string end) {
			vector<string> path;
			path.push_back(start);
			traverseGraph(start, end, path);
		}

		void traverseGraph(string curr, string dest, vector<string>& path) {
			if (curr == dest) {
				allValidPaths.push_back(path);
			}
			else {
				for (const auto& node : _graph[curr]) {
					// Recursively add all unvisited notes to curr path 
					if (_canVisitNode(node, path)) {
						path.push_back(node);
						traverseGraph(node, dest, path);
						path.pop_back();
					}
				}
			}
		}

		// A lowercase node can be visit only once. Uppercase nodes can be re-visited 
		bool _canVisitNode(string candidate, vector<string>& path) {
			char ch = candidate[0];
			// Check if it is lowercase
			if (islower(ch)) {
				// Check if its part of the path already
				if (std::find(path.begin(), path.end(), candidate) != path.end()){
					return false;
				}
			}
			return true; 
		}

		// Returns how many paths visit small caves at most once (answer to pt. 1)
		int countSmallCaves(string start = "start", string end = "end") {
			findAllPaths(start, end);

			int totalCount = 0;
			for (auto path : allValidPaths) {
				int _count = 0;
				for (int i = 1; i < path.size() - 1; i++) {
					char ch = path[i][0];
					if (islower(ch))
						_count++;
				}
				if (_count < 2)
					totalCount++;
			}

			return totalCount;
		}

	};

	int main1(string filename = "2021/data/day12.txt") {
		Graph g(filename);
		return g.countSmallCaves();
	}

	int main2(string filename = "2021/data/day12.txt") {
		return 0;
	}

	void test() {
		int answer = 7;
		int my_response = main1("2021/data/day12-test.txt");
		cout << "My response: " << my_response << "  Expected: " << answer << "\n\n";
	}

	void printAnswers() {
		cout << "Validation: \n";
		//test();
		cout << "First part: " << main1() << "\n";
		cout << "Second part: " << main2() << "\n";
	}
}