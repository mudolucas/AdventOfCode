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
		int allValidPathsCounter;
		unordered_map<string, vector<string>> _graph;
		bool isPart2;

	public:
		Graph(string filename, bool part2 = false) {
			isPart2 = part2;
			allValidPathsCounter = 0;
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
			unordered_map<string, int> visit_counts;
			traverseGraph(start, end, visit_counts);
		}

		void traverseGraph(string curr, string dest, unordered_map<string, int>& visit_counts) {
			if (curr == dest) {
				allValidPathsCounter++;
			}
			else {
				for (const auto& node : _graph[curr]) {
					// Recursively add all unvisited notes to curr path 
					if (_canVisitNode(node, visit_counts)) {
						visit_counts[node]++;
						traverseGraph(node, dest, visit_counts);
						visit_counts[node]--;
					}
				}
			}
		}

		// A lowercase node can be visit only once. Uppercase nodes can be re-visited 
		bool _canVisitNode(string candidate, unordered_map<string, int>& visit_counts) {
			if (candidate == "start") {
				return false;
			}
			// Check for small caves
			char ch = candidate[0];
			// In part 2 one can only visit a *single* small cave twice. 
			int visitsAllowed = isPart2 ? (isAnySmallCaveVisitedTwice(visit_counts) ? 1 : 2) : 1;
			if (islower(ch) && visit_counts.find(candidate) != visit_counts.end()) {
				if (visit_counts[candidate] < visitsAllowed)
					return true;
				else
					return false;
			}
			return true; 
		}
		
		// Returns true if a small cave has already been visited twice in the curr path
		bool isAnySmallCaveVisitedTwice(unordered_map<string, int>& visit_counts) {
			for (auto& it : visit_counts) {
				if (islower(it.first[0]) && it.second > 1)
					return true;
			}
			return false;
		
		}

		// Returns how many paths visit small caves at most once (answer to pt. 1)
		int getPathsCount() {
			if (allValidPathsCounter == 0)
				findAllPaths("start", "end");
			
			return allValidPathsCounter;
		}

	};

	int main1(string filename = "2021/data/day12.txt") {
		Graph g(filename, false);
		return g.getPathsCount();
	}

	int main2(string filename = "2021/data/day12.txt") {
		Graph g(filename, true);
		return g.getPathsCount();
	}

	void test() {
		int answer = 19;
		int my_response = main1("2021/data/day12-test.txt");
		cout << "My response: " << my_response << "  Expected: " << answer << "\n\n";
	}

	void printAnswers() {
		cout << "Validation: \n";
		test();
		cout << "First part: " << main1() << "\n";
		cout << "Second part: " << main2() << "\n";
	}
}