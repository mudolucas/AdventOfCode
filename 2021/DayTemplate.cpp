// https://adventofcode.com/2021/day/ - NAME!

#include <fstream>
#include <iostream>

using namespace std;

namespace DayTemplate {

	int main1(string filename="2021/data/dayXX.txt") {

		return 0;
	}

	int main2(string filename = "2021/data/dayXX.txt") {
		return 0;
	}

	void test() {
		int answer = 0;
		int my_response = main1("2021/data/dayXX-test.txt");
		cout << "My response: " << my_response << "  Expected: " << answer << "\n\n";
	}

	void printAnswers() {
		cout << "Validation: \n";
		test();
		cout << "First part: " << main1() << "\n";
		cout << "Second part: " << main2() << "\n";
	}
}