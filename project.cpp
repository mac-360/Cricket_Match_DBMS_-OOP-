#include <iostream>
#include "player.h"
#include "Commentator.h"
#include "highlights.h"
#include <cstring>
#include <fstream>
#include<cstdlib>
#include<ctime>
#include <windows.h>
#include <chrono>
#include <thread>
#include<iomanip>
#include<algorithm>


using namespace std;



class Match :public Player, public Commentatator, public Highlights
{

protected:
	string team1;	//Name of team A
	string team2;			//Name of team B
	int Overs, NoofMatches;	//Stores Overs & no of matches
	int BallsPlayed = 0;

	vector < int >PlayerTeam1Score;

	vector < int >PlayerTeam2Score;

	vector < double >StrikeRateTeam1;

	vector < double >StrikeRateTeam2;

	vector < string > PlayersofTeam1;

	vector < string > PlayersofTeam2;

	vector < int >Wickets_Of_Bowlers_Team2;

	vector < int >Wickets_Of_Bowlers_Team1;

public:
	Match()
	{

		//Default Constructor
		team1 = "Pakistan";

		team2 = "India";

		this->Overs = 20;

		this->NoofMatches = 0;




	}
	void OpenWelcome()
	{				//Opening file


		//Displaying a welcoming Screen 

		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(h, 4);

		cout << "Opening file" << endl;


		cout << "------------" << endl;


		cout << "ORGANISING MATCH" << endl;


		cout << " Match rules:-\n";


	}
	void GetName()
	{

		/*Setting Team1 and team2 name and make it all lower case check for teamid */
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(h, 11);


		cout << "Enter name of Team 1 :" << endl;

		cin >> this->team1;

		team1 = ToLower(team1);

		ofstream file1(team1);

		TeamIDExists(team1);

		SetConsoleTextAttribute(h, 11);

		cout << "\nEnter name of Team 2 :" << endl;

		cin >> team2;

		team2 = ToLower(team2);

		ofstream file2(team2);

		TeamIDExists(team2);


	}
	void rules()
	{

		//Display what to enter for what 
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(h, 14);

		cout << "commands\t-\tused for" << endl;

		cout << "noball\t-\tfor Noball" << endl;

		cout << "out\t-\tfor Out" << endl;

		cout << "wide\t-\tfor Wide ball" << endl;


	}
	void TeamIDExists(string team)

	{

		/*Checks whether team exist or not if not it calls RemaingPlayer function which take the input foe the rest of the team */

		ifstream file("playerList.txt");


		string line;

		int count = 0;		//to check if playerlist have 11 player minimum;
		while (!file.eof())
		{

			if (file.is_open())

			{



				while (getline(file, line))

				{

					istringstream ss(line);


					string playerName, playerRole, playerTeamName,
						playerwickets, playerruns, StrikeRate;

					int playerID;

					ss >> playerID;

					string skip;

					getline(ss, skip, ' ');

					getline(ss, playerName, ' ');

					getline(ss, playerRole, ' ');

					getline(ss, playerwickets, ' ');

					getline(ss, playerruns, ' ');

					getline(ss, playerTeamName, ' ');

					getline(ss, StrikeRate, ' ');

					if (playerTeamName == team)

					{

						ofstream file(team, ios::app);

						count++;

						if (file.is_open())
						{


							file << playerID << " " << playerName << " " <<
								playerRole << " " << playerwickets << " " <<
								playerruns << " " << playerTeamName << " " <<
								StrikeRate << endl;

							HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

							SetConsoleTextAttribute(h, 13);

							cout << "Player record added successfully!" << endl;


						}


						else
						{

							cout << "Failed to open file!" << endl;

						}




						break;


					}


				}



			}

		}

		//calling Remaining Players
		if (count < 11)
		{

			RemainingPlayers(count, team);

		}

	}

	void RemainingPlayers(int count, string TeamName)
	{

		/*Adds the rest of the player to playerList.txt */
		for (int i = count; i < 11; i++)
		{

			cout << "Enter the player details of " << i + 1 << endl;

			Player::AddData();

		}
		//Checks again
		TeamIDExists(TeamName);

	}
	vector < int >Display_Team_Stats_From_File(string team)
	{

		// Displays Stats from team file 
		ifstream file(team, ios::app);

		vector < string > Team1;

		vector < int >Team1ID;

		string line;

		static bool CheckTeam = false;


		while (!file.eof())
		{

			if (file.is_open())
			{

				while (getline(file, line))

				{

					istringstream ss(line);


					string playerName, playerRole, playerTeamName,
						playerwickets, playerruns, StrStrikeRate;

					int playerID;

					ss >> playerID;

					string skip;

					getline(ss, skip, ' ');

					getline(ss, playerName, ' ');

					getline(ss, playerRole, ' ');

					getline(ss, playerwickets, ' ');

					getline(ss, playerruns, ' ');

					getline(ss, playerTeamName, ' ');

					getline(ss, StrStrikeRate, ' ');

					Team1.push_back(playerName);

					Team1ID.push_back(playerID);

					if (!CheckTeam)
					{

						PlayerTeam1Score.push_back(stoi(playerruns));

						StrikeRateTeam1.push_back(stod(StrStrikeRate));

					}

					else if (CheckTeam)
					{

						PlayerTeam2Score.push_back(stoi(playerruns));

						StrikeRateTeam2.push_back(stod(StrStrikeRate));

					}

				}

			}


		}

		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(h, 11);

		std::
			cout << "---------------------------------------------------------\n";

		SetConsoleTextAttribute(h, 15);

		std::cout << "|ID NAME                     RUNS SCORED   STRIKERATE |\n";

		SetConsoleTextAttribute(h, 11);

		std::
			cout << "---------------------------------------------------------\n";

		SetConsoleTextAttribute(h, 11);

		if (!CheckTeam)
		{

			for (int j = 0; j < 11; j++)
			{

				int width = 30;

				std::cout << "| " << std::setw(2) << std::left << j + 1 << " "
					<< std::setw(24) << std::left << Team1[j]
					<< std::setw(12) << std::left << PlayerTeam1Score[j]
					<< std::setw(16) << std::left << StrikeRateTeam1[j] << " |\n";

				SetConsoleTextAttribute(h, 11);

				std::
					cout <<
					"---------------------------------------------------------\n";

			}
		}

		if (CheckTeam)
		{

			for (int j = 0; j < 11; j++)
			{

				int width = 30;

				std::cout << "| " << std::setw(2) << std::left << j + 1 << " "
					<< std::setw(24) << std::left << Team1[j]
					<< std::setw(12) << std::left << PlayerTeam2Score[j]
					<< std::setw(16) << std::left << StrikeRateTeam2[j] << " |\n";

				SetConsoleTextAttribute(h, 11);

				std::
					cout <<
					"---------------------------------------------------------\n";

			}
		}


		SetConsoleTextAttribute(h, 15);

		CheckTeam = true;

		return Team1ID;


	}

	string ToLower(string str)
	{

		//Conversion
		for (int i = 0; str[i] != '\0'; i++)
		{

			if (str[i] >= 'A' && str[i] <= 'Z')
			{

				str[i] += 32;

			}

		}

		return str;

	}

	void toss()
	{

		//Toss Simulation using Srand
		srand(time(0));

		int toss, side;

		side = rand() % 2;

		toss = rand() % 2;

		char choice;

		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);


		if (side == 0 && toss == 0)
		{


			SetConsoleTextAttribute(h, 11);

			cout << endl << team1 << " has TAILS\n";

			cout << endl << team2 << " has HEADS\n";

			SetConsoleTextAttribute(h, 10);

			this_thread::sleep_for(chrono::seconds(3));

			system("cls");


			cout << "\n\n\t\t\t----COIN FLIPPING---" << endl;

			this_thread::sleep_for(chrono::seconds(3));

			SetConsoleTextAttribute(h, 11);

			cout << "TEAM 1 has won the toss.\n";

			SetConsoleTextAttribute(h, 10);

			cout << "\nChoose \n a) BAT \\ b)  FIELD";

			cout << "\n Enter (B or F)   = ";

			cin >> choice;

			if (choice == 'b' || choice == 'B')
			{

				SetConsoleTextAttribute(h, 11);

				cout << "\n TEAM 1 has decided to BAT first\n";

			}

			else
			{

				SetConsoleTextAttribute(h, 11);

				cout << "\n TEAM 1 has decided to FEILD first\n";

				swap(team1, team2);

			}

		}

		else if (side == 0 && toss == 1)
		{


			SetConsoleTextAttribute(h, 11);

			cout << endl << team1 << " has TAILS\n";

			cout << endl << team2 << " has HEADS\n";

			SetConsoleTextAttribute(h, 11);

			this_thread::sleep_for(chrono::seconds(3));

			system("cls");


			cout << "\n\n\t\t\t----COIN FLIPPING---" << endl;

			this_thread::sleep_for(chrono::seconds(3));

			SetConsoleTextAttribute(h, 10);

			cout << "TEAM 2 has won the toss.";

			cout << "choose \n a) BAT \\ b)  FIELD";

			cout << "\n Enter (B or F)   = ";

			cin >> choice;

			if (choice == 'b' || choice == 'B')
			{

				SetConsoleTextAttribute(h, 11);

				cout << "\n TEAM 2 has decided to BAT first\n";

				swap(team1, team2);

			}

			else
			{

				SetConsoleTextAttribute(h, 10);

				cout << "\n TEAM 2 has decided to FEILD first\n";


			}

		}

		else if (side == 1 && toss == 0)
		{


			SetConsoleTextAttribute(h, 11);

			cout << endl << team1 << " has HEADS\n";

			cout << endl << team2 << " has TAILS\n";

			SetConsoleTextAttribute(h, 10);

			this_thread::sleep_for(chrono::seconds(3));

			system("cls");


			cout << "\n\n\t\t\t----COIN FLIPPING---" << endl;

			this_thread::sleep_for(chrono::seconds(3));

			SetConsoleTextAttribute(h, 11);

			cout << "TEAM 1 has won the toss.";

			cout << "choose \n a) BAT \\ b)  FIELD";

			cout << "\n Enter (B or F)   = ";

			cin >> choice;

			if (choice == 'b' || choice == 'B')
			{

				SetConsoleTextAttribute(h, 10);

				cout << "\n TEAM 1 has decided to BAT first\n";

			}

			else
			{

				SetConsoleTextAttribute(h, 10);

				cout << "\n TEAM 1 has decided to FEILD first\n";

				swap(team1, team2);

			}

		}

		else if (side == 1 && toss == 1)
		{

			SetConsoleTextAttribute(h, 11);

			cout << endl << team1 << " has HEADS\n";

			cout << endl << team2 << " has TAILS\n";

			SetConsoleTextAttribute(h, 10);

			this_thread::sleep_for(chrono::seconds(3));

			system("cls");


			cout << "\n\n\t\t\t----COIN FLIPPING---" << endl;

			this_thread::sleep_for(chrono::seconds(3));

			SetConsoleTextAttribute(h, 11);

			cout << "TEAM 2 has won the toss.";

			cout << "choose \n a) BAT \\ b)  FIELD";

			cout << "\n Enter (B or F)   = ";

			cin >> choice;

			if (choice == 'b' || choice == 'B')
			{

				SetConsoleTextAttribute(h, 10);

				cout << "\n TEAM 2 has decided to BAT first\n";

				swap(team1, team2);

			}

			else
			{

				SetConsoleTextAttribute(h, 10);

				cout << "\n TEAM 2 has decided to FEILD first\n";

			}

		}








	}

	void WicketCalculator(string team, vector < string >& Bowler,vector < int >& wickets)
	{

		//checks if Player is Allrounder or Bowler and displays it accordingly
		ifstream file(team, ios::app);

		string line;

		while (!file.eof())
		{

			if (file.is_open())
			{

				while (getline(file, line))

				{

					istringstream ss(line);


					string playerName, PlayerRole;

					int playerID, playerwickets;


					ss >> playerID;

					string skip;

					getline(ss, skip, ' ');

					getline(ss, playerName, ' ');

					getline(ss, PlayerRole, ' ');

					ss >> playerwickets;

					getline(ss, skip, ' ');

					if (PlayerRole == "All-Rounder" || PlayerRole == "Bowler")
					{

						Bowler.push_back(playerName);


					}

					wickets.push_back(playerwickets);



				}

			}


		}

		int columnWidth = 15;	// Width for the columns
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(h, 13);

		cout << "________________________________\n";

		SetConsoleTextAttribute(h, 13);

		std::cout << "|" << std::left << std::
			setw(columnWidth) << "Bowler" << "|" << std::
			setw(columnWidth) << "Wickets" << "|" << std::endl;

		SetConsoleTextAttribute(h, 10);

		cout << "________________________________\n";

		for (size_t i = 0; i < Bowler.size(); i++)
		{

			SetConsoleTextAttribute(h, 10);

			std::cout << "|" << std::left << std::
				setw(columnWidth) << Bowler[i] << "|" << std::
				setw(columnWidth) << wickets[i] << "|" << std::endl;

			cout << "________________________________\n";

		}


		// Reset the width to the default value (0)
		std::cout << std::setw(0);


	}

	void Update(const string& team, int playerScore[11],const vector < int >& PlayerIDs, vector < int >& wickets,double StrikeRate[11])
	{

		//Update the file after the program terminates
		fstream file("playerList.txt", ios::in | ios::out);


		if (!file)
		{

			cerr << "Failed to open the file." << std::endl;

			return;

		}


		string line;

		vector < string > updatedRecords;

		int i = 0;


		while (getline(file, line))
		{

			istringstream ss(line);


			int playerID;

			string playerName, playerRole, playerTeamName;

			int playerruns, playerwickets;

			double StrRate = 0;

			ss >> playerID;

			ss >> playerName;

			ss >> playerRole;

			ss >> playerwickets;

			ss >> playerruns;

			ss >> playerTeamName;

			ss >> StrRate;



			if (PlayerIDs[i % PlayerIDs.size()] == playerID)
			{

				playerruns += playerScore[i % PlayerIDs.size()];

				playerwickets = wickets[i % PlayerIDs.size()];

				playerTeamName = playerTeamName;

				StrRate = (StrRate + StrikeRate[i % PlayerIDs.size()]) / 2.0;

			}


			string updatedRecord =
				std::to_string(playerID) + " " + playerName + " " + playerRole +
				" " + to_string(playerwickets) + " " + to_string(playerruns) +
				" " + playerTeamName + " " + to_string(StrRate);

			updatedRecords.push_back(updatedRecord);


			i++;

		}


		file.close();


		std::ofstream outFile("playerList.txt");

		if (!outFile)
		{

			std::cerr << "Failed to open the file for writing." << std::endl;

			return;

		}


		for (const auto& record : updatedRecords)
		{

			outFile << record << std::endl;

		}

		outFile.close();


		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(h, 13);

		cout << "Player records updated successfully!" << std::endl;

	}
	void StrikeRateCalculator(int BallFacedT1[11], int player_t1[11],double StrikeRateT1[11])
	{

		//Calculates StrikeRate
		for (int i = 0; i < 11; i++)
		{

			if (BallFacedT1[i] == 0)
			{

				StrikeRateT1[i] = 0.0;

			}

			else
			{

				StrikeRateT1[i] = (player_t1[i] * 100) / (BallFacedT1[i] * 1.0);

			}

		}


	}

	float RunRateCalculator(int Score, int balls)
	{

		//Calculates RunRate
		float runRate = 0.0f;

		if (balls - 1 == 0)
		{

			return 0.0;

		}

		else
		{

			runRate = static_cast <float>(Score) / (balls - 1);

		}

		return runRate;

	}

	float calculateRequiredRunRate(int targetScore, int remainingBalls,int currentScore)
	{

		//Calculates RequiredRunRate
		int remainingRuns = targetScore - currentScore;


		if (remainingBalls <= 0 || remainingRuns <= 0)
		{

			return 0.0f;		// No runs required or no balls remaining
		}


		float requiredRunRate =
			static_cast <float>(remainingRuns) / remainingBalls * 6;

		return requiredRunRate;

	}

	void WicketAdder(string WicketTaker, vector < string >& Bowler,vector < int >& wicket)
	{

		bool check = false;

		//Add the wicket for the player who took the wicket
		for (int i = 0; i < Bowler.size(); i++)
		{

			if (Bowler[i] == WicketTaker)
			{

				wicket[i] = wicket[i] + 1;

				check = true;

				return;

			}

		}

		while (check == false)
		{

			cout << "Enter Wicket Taker again : ";

			cin >> WicketTaker;

			WicketAdder(WicketTaker, Bowler, wicket);

		}

	}

	vector < int >DisplayTeam1(string team, int playerscore[11],double StrikeRate[11],vector < string >& TeamPlayers)
	{

		ifstream file(team, ios::app);

		vector < int >Team1ID;

		string line;


		while (!file.eof())
		{

			if (file.is_open())
			{

				while (getline(file, line))

				{

					istringstream ss(line);


					string playerName, playerRole, playerTeamName,
						playerwickets, playerruns;

					int playerID;

					ss >> playerID;

					string skip;

					getline(ss, skip, ' ');

					getline(ss, playerName, ' ');

					getline(ss, playerRole, ' ');

					getline(ss, playerwickets, ' ');

					getline(ss, playerruns, ' ');

					getline(ss, playerTeamName, ' ');

					TeamPlayers.push_back(playerName);

					Team1ID.push_back(playerID);


				}
			}


		}
		Display(playerscore, StrikeRate, TeamPlayers);

		return Team1ID;

	}

	void Display(int playerscore[11], double StrikeRate[11],vector < string >& TeamPlayers)
	{

		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(h, 11);

		std::
			cout << "---------------------------------------------------------\n";

		SetConsoleTextAttribute(h, 15);

		std::cout << "|ID NAME RUNS SCORED STRIKERATE |\n";

		SetConsoleTextAttribute(h, 11);

		std::
			cout << "---------------------------------------------------------\n";

		SetConsoleTextAttribute(h, 11);


		for (int j = 0; j < TeamPlayers.size(); j++)
		{

			int width = 30;

			std::cout << "| " << std::setw(2) << std::left << j + 1 << " "
				<< std::setw(23) << std::left << TeamPlayers[j]
				<< std::setw(10) << std::left << playerscore[j]
				<< std::setw(12) << std::left << "\t" << StrikeRate[j] << " |\n";

			SetConsoleTextAttribute(h, 11);

			std::
				cout <<
				"---------------------------------------------------------\n";

		}
		SetConsoleTextAttribute(h, 15);

	}
	void NoOfOvers()		// Input of Overs

	{

		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(h, 11);


		cout << "Enter number of overs" << endl;


		cin >> Overs;


	}
	int Series()
	{


		NoofMatches = 0;


		while (NoofMatches % 2 == 0)
		{


			HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

			SetConsoleTextAttribute(h, 11);


			cout << "Enter an odd number of matches : \n";


			cin >> NoofMatches;


		}

		return NoofMatches;

	}

	void virtual ScoreRecord()
	{

		//string team,vector<string> Bowler,vector<int> wickets
		static bool Superover = false;

		vector < string > Bowler1;

		vector < string > Bowler2;

		static string Namet1 = team1;

		static string Namet2 = team2;

		int balls[2];		// created array [0]=team1 and [1]=team2
		int player[2];

		player[0] = 10;

		player[1] = player[0];

		static int score[2];	//static used to initialized score =0
		vector < int >PlayerID1;

		vector < int >PlayerID2;


		int BallFacedT1[11] = { 0 };

		int BallFacedT2[11] = { 0 };

		double StrikeRateT1[11] = { 0 };

		double StrikeRateT2[11] = { 0 };

		int player_t1[11];

		int player_t2[11];

		float RequiredRunRate = 0;

		int Score = 0;

		float CurrentRunRate;

		rules();

		OpenWelcome();



		if (!Superover)
		{

			GetName();

			NoOfOvers();


		}


		if (Superover)
		{

			this->Overs = 1;

			team1 = Namet1;

			team2 = Namet2;


		}

		balls[0] = Overs * 6;

		balls[1] = balls[0];

		toss();


		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(h, 13);


		fstream Match("Match.txt", ios::in | ios::out);

		Match << "Start of the Match" << endl;



		for (int i = 0; i < 11; i++)
		{

			player_t1[i] = 0;

		}

		for (int i = 0; i < 11; i++)
		{

			player_t2[i] = 0;

		}
		cout << team1 << endl;

		PlayerID1 =
			DisplayTeam1(team1, player_t1, StrikeRateT1, PlayersofTeam1);

		this_thread::sleep_for(chrono::seconds(5));

		system("cls");

		WicketCalculator(team1, Bowler1, Wickets_Of_Bowlers_Team1);

		this_thread::sleep_for(chrono::seconds(5));

		system("cls");


		cout << team2 << endl;

		PlayerID2 =
			DisplayTeam1(team2, player_t2, StrikeRateT2, PlayersofTeam2);

		this_thread::sleep_for(chrono::seconds(5));

		system("cls");

		WicketCalculator(team2, Bowler2, Wickets_Of_Bowlers_Team2);

		this_thread::sleep_for(chrono::seconds(5));

		int s1 = 0, s2 = 1, x = 0;

		int turn = 0;


		for (int j = 0; j < 2; j++)	//loop for two innings
		{



			turn = 0;

			s1 = 0;

			s2 = 1;


			if (j == 0)
			{

				system("cls");

				HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

				SetConsoleTextAttribute(h, 11);

				cout << "Batting :" << team1 << "\t Bowling :" << team2 << endl;	// shows which team is playing
				Match << "Team 1 : " << team1 << "\tBatting" << endl;

				ofstream file("Commentator.txt", ios::app);

				file << team1 << endl;

				file.close();


			}

			if (j == 1)
			{

				system("cls");


				SetConsoleTextAttribute(h, 13);

				cout << "Target : " << score[0] << endl;

				cout << "Batting :" << team2 << " Bowling :" << team1 << endl;

				Match << "Team 2 : " << team2 << "\tBatting" << endl;

				ofstream file("Commentator.txt", ios::app);

				file << team2 << endl;


				file.close();


			}

			rules();



			for (int i = 1; i <= balls[j]; i++)	//Inputs score and conditions for adding score
			{

				if (score[1] > score[0] || player[1] == 0)
				{
					break;
				}

				int b;

				int c;

				b = i / 6;

				c = i % 6;

				BallsPlayed = i;

				if (turn == 1)
				{

					x = s2;

				}

				if (turn == 0)
				{

					x = s1;

				}


				SetConsoleTextAttribute(h, 11);

				if (j == 1)
				{

					RequiredRunRate =
						calculateRequiredRunRate(score[0], balls[j] - i, score[1]);


				}

				CurrentRunRate = RunRateCalculator(Score, i);

				cout << "Over : " << b << "." << c << "\t" << " Score : " <<
					score[j] << " No of wickets : " << 10 -
					player[j] << "\tRun Rate : " << RunRateCalculator(Score,
						i) <<
					" Projected Score : " << static_cast <
					int>(ProjectedScore(CurrentRunRate, Score, i));

				if (j == 1)
				{

					cout << "\tRequired Run Rate : " << RequiredRunRate;

				}

				cout << endl;

				cout << "Enter score :" << endl;

				cin >> scr;

				system("cls");



				SetConsoleTextAttribute(h, 13);

				if (scr == "0")
				{

					score[j] = score[j] + 0;

					system("cls");

					Match << "Score : " << score[j] << "\tBalls : " << i << endl;

					setScore(this->scr);

					CommentGenerator();

					CommentFileOutput();



					if (j == 0)
					{


						player_t1[x] += 0;

						BallFacedT1[x] += 1;

					}

					if (j == 1)
					{

						BallFacedT2[x] += 1;

						player_t2[x] += 0;

					}

					continue;

				}


				if (scr == "1")

				{

					system("cls");

					score[j] = score[j] + 1;

					Score += 1;

					setScore(this->scr);

					CommentGenerator();

					CommentFileOutput();

					if (turn == 0)
					{

						turn = 1;

					}

					else
					{

						turn = 0;

					}


					if (j == 0)
					{

						BallFacedT1[x] += 1;

						player_t1[x] += 1;

					}

					if (j == 1)
					{

						BallFacedT2[x] += 1;

						player_t2[x] += 1;

					}


				}

				else if (scr == "2")

				{

					system("cls");

					score[j] = score[j] + 2;

					Score += 2;

					setScore(this->scr);

					CommentGenerator();

					CommentFileOutput();


					if (j == 0)
					{


						player_t1[x] += 2;

						BallFacedT1[x] += 1;

					}

					if (j == 1)
					{

						BallFacedT2[x] += 1;

						player_t2[x] += 2;

					}

				}

				else if (scr == "3")

				{

					system("cls");

					score[j] = score[j] + 3;

					Score += 3;

					setScore(this->scr);

					CommentGenerator();

					CommentFileOutput();

					if (turn == 0)
					{

						turn = 1;

					}

					else
					{

						turn = 0;

					}

					if (j == 0)
					{

						BallFacedT1[x] += 1;

						player_t1[x] += 3;

					}

					if (j == 1)
					{

						BallFacedT2[x] += 1;

						player_t2[x] += 3;

					}

				}

				else if (scr == "4")

				{

					system("cls");

					score[j] = score[j] + 4;

					Score += 4;

					setScore(this->scr);

					CommentGenerator();

					CommentFileOutput();

					turn = 0;

					if (j == 0)
					{

						BallFacedT1[x] += 1;

						player_t1[x] += 4;

					}

					if (j == 1)
					{

						BallFacedT2[x] += 1;

						player_t2[x] += 4;

					}

				}

				else if (scr == "5")

				{

					system("cls");

					score[j] = score[j] + 5;

					Score += 5;

					setScore(this->scr);

					CommentGenerator();

					CommentFileOutput();

					if (turn == 0)
					{

						turn = 1;

					}

					else
					{

						turn = 0;

					}

					if (j == 0)
					{

						BallFacedT1[x] += 1;

						player_t1[x] += 5;

					}

					if (j == 1)
					{

						BallFacedT2[x] += 1;

						player_t2[x] += 5;

					}

				}

				else if (scr == "6")

				{

					system("cls");

					score[j] = score[j] + 6;

					Score += 6;

					setScore(this->scr);

					CommentGenerator();

					CommentFileOutput();

					turn = 0;

					if (j == 0)
					{

						BallFacedT1[x] += 1;

						player_t1[x] += 6;

					}

					if (j == 1)
					{

						BallFacedT2[x] += 1;

						player_t2[x] += 6;

					}

				}

				else if (scr == "wide")

				{

					system("cls");

					score[j] = score[j] + 1;

					Score += 1;

					i = i - 1;

					setScore(this->scr);

					CommentGenerator();

					CommentFileOutput();


					Match << "wide" << endl;

				}

				else if (scr == "noball")

				{

					system("cls");

					score[j] = score[j] + 1;

					Score += 1;

					i = i - 1;

					setScore(this->scr);

					CommentGenerator();

					CommentFileOutput();


					Match << "noball" << endl;

				}

				else if (scr == "out")

				{

					system("cls");

					string WicketTaker;

					cout << "Who took the wicket : ";

					cin.ignore();

					cin.clear();

					getline(cin, WicketTaker);

					WicketTaker = ToLower(WicketTaker);

					if (j == 0)
					{

						WicketAdder(WicketTaker, PlayersofTeam2,
							Wickets_Of_Bowlers_Team2);

					}

					if (j == 1)
					{

						WicketAdder(WicketTaker, PlayersofTeam1,
							Wickets_Of_Bowlers_Team1);

					}

					player[j] = player[j] - 1;

					setScore(this->scr);

					CommentGenerator();

					CommentFileOutput();

					Match << "out" << endl;



					if (turn == 0)
					{

						if (s1 == s2 - 1)

							s1 += 2;


						else if (s1 < s2 && s1 != s2 - 1)

							s1 = (s2 - s1) + 1;


						else if (s1 > s2)

							s1 += 1;


					}

					if (turn == 1)
					{


						if (s2 == (s1 - 1))

							s2 += 2;


						else if (s2 < s1 && s2 != s1 - 1)

							s2 = (s1 - s2) + 1;


						else if (s2 > s1)

							s2 += 1;


					}


				}

				else if (player[j] == 0)

				{

					system("cls");

					cout << "All out" << endl;

					cout << score[j] << endl;

					break;

				}

				else if (scr == "score")

				{

					cout << "The Score is : " << score[j] << endl;;

					i = i - 1;

				}

				else if (j == 1 && score[0] <= score[1])

				{

					if (score[0] == score[1])
					{

						cout << "Its already draw" << endl;

					}

					else

						break;

				}

				else if (scr == "F" || scr == "f")
				{

					FastTrack(j, score);

					cout << score[j];

					break;

				}

				else

				{


					SetConsoleTextAttribute(h, 12);

					cout << "Please enter correct value" << endl;

					i = i - 1;

				}


				Match << "Score : " << score[j] << "\tBalls : " << i << endl;

			}


			if (j == 0)
			{




				SetConsoleTextAttribute(h, 15);

				cout << "Players contribution in 1st Innings\n";

				StrikeRateCalculator(BallFacedT1, player_t1, StrikeRateT1);

				Display(player_t1, StrikeRateT1, PlayersofTeam1);



				SetConsoleTextAttribute(h, 15);



				this_thread::sleep_for(chrono::seconds(5));

				system("cls");

				SetConsoleTextAttribute(h, 11);

				cout <<
					"\033[2m***************INNING BREAK***************\033[2m" <<
					endl;

				this_thread::sleep_for(chrono::seconds(5));

				Score = 0;

			}



			if (j == 1)
			{



				SetConsoleTextAttribute(h, 15);

				cout << "Players contribution in 2nd Innings\n";

				StrikeRateCalculator(BallFacedT2, player_t2, StrikeRateT2);

				Display(player_t2, StrikeRateT2, PlayersofTeam2);

			}



		}




		if (score[1] > score[0])
		{


			SetConsoleTextAttribute(h, 11);

			cout << "Match completed :" << team2 << " won by" << endl;	//condition for wining
			cout << score[1] - score[0] << endl;

		}

		if (score[1] < score[0])
		{


			SetConsoleTextAttribute(h, 11);

			cout << "Match completed :" << team1 << " won by " << endl;

			cout << score[0] - score[1] << endl;

		}

		if (score[1] == score[0])
		{

			HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

			SetConsoleTextAttribute(h, 11);

			cout << "Match completed, its a draw" << endl;

			cout << score[0] << endl;

			Update(team1, player_t1, PlayerID1, Wickets_Of_Bowlers_Team1,
				StrikeRateT1);

			Update(team2, player_t2, PlayerID2, Wickets_Of_Bowlers_Team2,
				StrikeRateT2);

			SetConsoleTextAttribute(h, 11);

			cout << "Lets go for a Super over !! " << endl;;

			this_thread::sleep_for(chrono::seconds(5));

			Superover = true;


			ScoreRecord();

		}


		SetConsoleTextAttribute(h, 11);

		Match << "End !!! see you tommorow" << endl << endl;

		Match.close();





		Update(team1, player_t1, PlayerID1, Wickets_Of_Bowlers_Team1,
			StrikeRateT1);

		Update(team2, player_t2, PlayerID2, Wickets_Of_Bowlers_Team2,
			StrikeRateT2);


	}

	int ProjectedScore(float CurrentRunRate, int Score, int NoOfBallsPlayed)
	{

		int RemaingOvers =
			Overs - static_cast <int>((NoOfBallsPlayed - 1) / 6);

		return Score + (CurrentRunRate * RemaingOvers);

		//Total Runs + (Current Run Rate * Remaining Overs)
	}

	~Match()
	{
	}

	void FastTrack(int j, int scr[])
	{

		int runs = scr[j];

		srand(time(nullptr));	// Seed the random number generator with the current time
		int Players = 11;

		for (int i = 1; i <= Overs * 6; i++)
		{

			if (Players == 1)
			{

				return;

			}

			int probability = 100;	// Starting probability

			int randomValue1 = rand() % 100;	// Generate a random value between 0 and 99
			if (randomValue1 < probability)
			{

				int event = rand() % 10;	// Generate a random event between 0 and 9

				if (event == 0)
				{

					std::cout << "Out!" << std::endl;

					Players--;

				}

				else if (event == 1)
				{

					std::cout << "No ball!" << std::endl;

					i--;

					runs++;

				}

				else if (event == 2)
				{

					std::cout << "Wide!" << std::endl;

					i--;

					runs++;

				}

				else
				{

					int score = rand() % 7;	// Generate a random score between 0 and 6
					std::cout << "Scored: " << score << std::endl;

					runs += score;

				}

				probability -= 10;	// Decrease the probability for the next event
				if (probability < 10)
				{

					probability = 10;	// Ensure the probability doesn't go below 10
				}

			}

		}


		// Update scr[j] with the final runs
		scr[j] = runs;

	}


};




int
main()
{



	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(h, 11);


	cout << "\n WELCOME TO \n";


	SetConsoleTextAttribute(h, 13);


	cout << " ____   ___     _____   ____    \n";

	cout << "/  __| |    \\  |_   _| /  __|   \n";

	cout << "| |    |   _/    | |   | |      \n";

	cout << "| |__  | |\\ \\   _| |_  | |__    \n";

	cout << " \\___| |_| \\_\\ |_____| \\____|   \n";


	SetConsoleTextAttribute(h, 14);


	cout << "    _____   __     _   _____    _____   \n";

	cout << "   |_   _| |   \\  | | |  ___|  /     \\  \n";

	cout << "     | |   | |\\ \\ | | | |__   |       | \n";

	cout << "    _| |_  | | \\ \\| | |  __|  |       | \n";

	cout << "   |_____| |_|  \\ __| |_|      \\_____/  \n\n";



	SetConsoleTextAttribute(h, 11);

	int choice;


	Player player("", "", "", 0, 0, 0, 0.0);	// initialize with default values

	do
	{


		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(h, 9);



		cout << "\t\tSelect an option:" << endl;


		cout << "\t\t1. Add a player record" << endl;


		cout << "\t\t2. View a player record" << endl;


		cout << "\t\t3. Remove a player record" << endl;


		cout << "\t\t4. Update a player record" << endl;


		cout << "\t\t5. Exit" << endl;


		cout << "\t\tEnter your choice: ";


		cin >> choice;


		getchar();		// consume the newline character



		switch (choice)
		{


		case 1:


			player.AddData();


			break;


		case 2:


			player.viewData();


			break;


		case 3:


			player.removeData();


			break;


		case 4:


			player.updateData();


			break;


		case 5:


			cout << "Exiting program..." << endl;


			break;


		default:



			SetConsoleTextAttribute(h, 12);

			cout << "Invalid choice! Please try again." << endl;


			break;


		}


	} while (choice != 5);



	SetConsoleTextAttribute(h, 14);


	int a;

	cout << "1 - Organise A Match\n";

	cout << "2 - Watch previous highlights\n";

	cin >> a;


	Match M;


	if (a == 1)
	{

		int series = M.Series();

		for (int i = 0; i < series; i++)
		{

			SetConsoleTextAttribute(h, 14);

			cout << "Match no : " << i + 1;

			M.ScoreRecord();

		}

	}

	else
	{

		M.Previous_match();

	}



}
