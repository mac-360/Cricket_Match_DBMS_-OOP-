#pragma once


#include<iostream>

#include<string>

#include<fstream>

#include<sstream>

#include<vector>

#include <windows.h>

using namespace std;

class Player {

protected:

	string playerName;

	string playerRole;

	string playerTeamName;

	int Runs;

	int Wickets;

	int ID;

	double PlayerStrikeRate;



public:
	Player()
	{

		playerName = "xyz";

		playerRole = "role";

		playerTeamName = "teamname";

		ID = 0000;

		Runs = 0000;

		Wickets = 0000;

	}

	Player(string name, string role, string teamname, int id, int runs, int wickets, double PlayerStrikeRate)
	{

		playerName = name;

		playerRole = role;

		playerTeamName = teamname;

		ID = id;

		Runs = runs;

		Wickets = wickets;

		this->PlayerStrikeRate = PlayerStrikeRate;
	}


	void AddData(void)

	{

		string temp = "";

		cout << endl;

		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, 11);

		cout << "Enter the Following Information to Store Player Record" << endl;

		cout << "Enter Player ID : ";
		bool check = true;
		while (check) {
			cin >> this->ID;
			check = checkIDExists(this->ID);

		}

		getchar();

		SetConsoleTextAttribute(h, 11);

		cout << "Enter Player Name : ";

		getline(cin, temp);

		this->playerName = temp;

		SetConsoleTextAttribute(h, 11);

		cout << "Select Player Primary Role : " << endl;

		cout << "1. Batsmen" << endl;

		cout << "2. Bowler" << endl;

		cout << "3. Wicket Keeper" << endl;

		cout << "4. All Rounder" << endl;



		cout << "Enter Your Choice : ";

		int choice;

		cin >> choice;

		getchar();



		switch (choice)

		{

		case 1:

			this->playerRole = "Batsmen";

			break;

		case 2:

			this->playerRole = "Bowler";

			break;

		case 3:

			this->playerRole = "WicketKeeper";

			break;

		case 4:

			this->playerRole = "AllRounder";

			break;



		default:
			SetConsoleTextAttribute(h, 12);
			cout << "You Have Provided Invalid Choice !" << endl;

			return;

		}

		SetConsoleTextAttribute(h, 11);

		cout << "Enter Player Team Name : ";

		getline(cin, temp);

		this->playerTeamName = temp;

		cout << "Enter number of wickets taken : ";

		cin >> Wickets;

		cout << "Enter number of runs scored : ";

		cin >> Runs;

		cout << "Enter Strike Rate : ";
		cin >> PlayerStrikeRate;
		// Open the file to append data

		ofstream file("playerList.txt", ios::app);

		if (file.is_open()) {

			file << this->ID << " " << this->playerName << " " << this->playerRole << " " << Wickets << " " << Runs << " " << this->playerTeamName << " " << this->PlayerStrikeRate << endl;

			SetConsoleTextAttribute(h, 11);

			cout << "Player record added successfully!" << endl;

		}

		else {
			SetConsoleTextAttribute(h, 12);
			cout << "Failed to open file!" << endl;

		}

		file.close();

	}

	void viewData() {

		int playerID;

		bool found = false;


		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, 11);

		cout << "Enter Unique ID of Player: ";

		cin >> playerID;



		ifstream file("playerList.txt");



		if (file.is_open()) {

			string line;

			while (getline(file, line)) {

				istringstream iss(line);

				int id;

				string name, role, teamName, runs, wickets;
				double StrRate;
				if (iss >> id >> name >> role >> wickets >> runs >> teamName >> StrRate) {

					if (id == playerID) {

						found = true;


						SetConsoleTextAttribute(h, 11);

						cout << "-----------------------------------\n";

						cout << "Player Details are as follows:\n";

						cout << "Name: " << name << "\n";

						cout << "Player Details are as follows:\n";

						cout << "Name: " << name << "\n";

						cout << "Role: " << role << "\n";

						cout << "TeamName: " << teamName << "\n";

						cout << "ID: " << id << "\n";

						cout << "Wickets taken : " << wickets << "\n";

						cout << "Runs Scored : " << runs << "\n";

						cout << "Strike Rate : " << StrRate << "\n";

						cout << "-----------------------------------\n";

						break;

					}

				}

			}

			file.close();

		}



		if (!found) {


			SetConsoleTextAttribute(h, 12);

			cout << "Player not found in records\n";

		}

	}

	void removeData(void)

	{

		int playerID;

		bool found = false;

		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, 11);

		cout << "Enter Unique id of Player : ";

		cin >> playerID;

		getchar();



		string filename = "playerList.txt";

		ifstream file(filename);

		ofstream tempFile("temp.txt");



		if (file.is_open() && tempFile.is_open()) {

			string line;

			while (getline(file, line)) {

				istringstream iss(line);

				int id;

				string name, role, teamName, runs, wickets;
				double StrRate;
				if (iss >> id >> name >> role >> wickets >> runs >> teamName >> StrRate) {

					if (id == playerID) {

						found = true;

						SetConsoleTextAttribute(h, 10);

						cout << "Record Deleted Successfully\n";

					}

					else {

						tempFile << line << "\n";

					}

				}

			}

			file.close();

			tempFile.close();

			remove(filename.c_str());

			rename("temp.txt", filename.c_str());

		}



		if (!found) {

			SetConsoleTextAttribute(h, 12);
			cout << "Player not found in records\n";

		}

		SetConsoleTextAttribute(h, 11);

		cout << "Press Any key to go back to menu\n";

		getchar();

	}

	void updateData()

	{

		fstream file("playerList.txt");

		ofstream tempFile("temp.txt");

		string line;

		bool found = false;

		if (file.is_open() && tempFile.is_open())

		{
			HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(h, 11);
			cout << "Enter the player ID to update: ";

			int id;

			cin >> id;

			cin.ignore();

			while (getline(file, line))

			{

				istringstream ss(line);

				string playerName, playerRole, playerTeamName;

				string playerRuns, playerWickets, StrikeRate;

				int playerID;

				ss >> playerID;

				getline(ss, playerName, ' ');

				getline(ss, playerName, ' ');

				getline(ss, playerRole, ' ');

				getline(ss, playerWickets, ' ');

				getline(ss, playerRuns, ' ');

				getline(ss, playerTeamName, ' ');

				getline(ss, StrikeRate, ' ');





				if (playerID == id)

				{

					found = true;


					SetConsoleTextAttribute(h, 11);
					cout << "Enter the field to update (1. Name, 2. Role, 3. Team, 4. Runs, 5. Wickets,6.Strike Rate): ";

					int field;

					cin >> field;

					cin.ignore();



					switch (field)

					{

					case 1:
						SetConsoleTextAttribute(h, 6);
						cout << "Enter the new name: ";

						getline(cin, playerName);

						break;

					case 2:
						SetConsoleTextAttribute(h, 6);
						cout << "Enter the new role: ";

						getline(cin, playerRole);

						break;

					case 3:
						SetConsoleTextAttribute(h, 6);
						cout << "Enter the new team: ";

						getline(cin, playerTeamName);

						break;

					case 4:
						SetConsoleTextAttribute(h, 6);
						cout << "Enter the new runs: ";

						cin >> playerRuns;

						break;

					case 5:
						SetConsoleTextAttribute(h, 6);
						cout << "Enter the new wickets: ";

						cin >> playerWickets;

						break;
					case 6:
						SetConsoleTextAttribute(h, 6);
						cout << "Enter the new strike rate: ";

						cin >> StrikeRate;

						break;

					default:


						SetConsoleTextAttribute(h, 12);
						cout << "Invalid field!" << endl;

						break;

					}



					tempFile << playerID << " " << playerName << " " << playerRole << " " << playerWickets << " " << playerRuns << " " << playerTeamName << " " << StrikeRate << endl;

					SetConsoleTextAttribute(h, 10);
					cout << "Player data updated successfully!" << endl;

				}

				else

				{

					tempFile << line << endl;

				}

			}



			file.close();

			tempFile.close();



			if (!found)

			{

				SetConsoleTextAttribute(h, 12);
				cout << "Player with ID " << id << " not found!" << endl;

			}

			else

			{

				remove("playerList.txt");

				rename("temp.txt", "playerList.txt");

			}

		}

		else

		{
			HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(h, 12);
			cout << "Error opening file!" << endl;

		}

	}



	bool checkIDExists(int id)

	{

		ifstream file("playerList.txt");

		string line;

		bool found = false;

		if (file.is_open())

		{

			while (getline(file, line))

			{

				istringstream ss(line);

				string playerName, playerRole, playerTeamName;

				int playerID;

				ss >> playerID;
				if (playerID == id)

				{
					cout << "Player id already exist\nEnter a valid id : ";
					found = true;

					break;

				}

			}



			file.close();

		}

		else

		{
			HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(h, 12);
			cout << "Error opening file!" << endl;

		}



		return found;

	}





};
