#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include<cstdlib>
#include<ctime>
#include <chrono>
#include <thread>
using namespace std;

class Highlights {

public:

	void Previous_match() {
		ifstream file1("Match.txt");
		if (!file1.is_open()) {
			cerr << "Error: Unable to open Match.txt" << endl;
			return;
		}

		ifstream file2("Commentator.txt");
		if (!file2.is_open()) {
			cerr << "Error: Unable to open Commentator.txt" << endl;
			return;
		}

		string line1;
		string line2;
		bool check1 = false, check2 = false;

		while (getline(file1, line1)) {
			if (line1.find("Team 1") != std::string::npos && !check1) {
				check1 = true;
				continue;
			}
			if (line1.find("Team 2") != std::string::npos && !check2) {
				system("cls");
				check2 = true;
			}
			cout << line1 << endl;
			if (getline(file2, line2)) {
				cout << line2 << endl;
			}

			this_thread::sleep_for(chrono::seconds(2));

		}

		file1.close();
		file2.close();
	}

};