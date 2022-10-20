#include <iostream>
#include <vector>
#include <string>

using namespace std;

class TxtReader {
public:
	static vector<int> readTxtFileAsInt(string filename);
	static vector<string> readTxtFileAsString(string filename);

};