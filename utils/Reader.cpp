#include "Reader.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// Read txt file and returns a int vector
vector<int> TxtReader::readTxtFileAsInt(string filename) {
	vector<int> data;

	fstream myFile;
	myFile.open(filename, ios::in);

	if (myFile.is_open()) {
		string line;
		while (getline(myFile, line)) {
			data.insert(data.end(), stoi(line));
		}
	}

	return data;
}

// Read txt file and returns a string vector
vector<string> TxtReader::readTxtFileAsString(string filename) {
	vector<string> data;

	ifstream myFile;
	myFile.open(filename, ios::in);

	if (myFile.is_open()) {
		string line;
		while (getline(myFile, line)) {
			data.insert(data.end(), line);
		}
	}

	return data;
}