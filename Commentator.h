#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include<cstdlib>
#include<ctime>

using namespace std;
class Commentatator {
protected:
	string scr;
	string comment;
public:
	Commentatator() {
		this->scr = '\0';
		this->comment = '\0';
	}
	void setScore(string score) {
		this->scr = score;
	}
	void CommentGenerator() {
		if (scr == "0") {
			srand(time(0));
			int random0 = 0;
			random0 = rand() % 3;
			if (random0 == 0) {
				comment = "Scoring zero on a ball is a learning opportunity.\n";
				cout << comment << endl;
			}
			else if (random0 == 1) {
				comment = "Every point counts, so don't underestimate the importance of avoiding a zero score.\n";
				cout << comment << endl;
			}
			else {
				comment = "Practice good sportsmanship and resilience, even if you don't score any points on a ball.\n";
				cout << comment << endl;
			}
		}
		else if (scr == "1") {
			srand(time(0));
			int random0 = 0;
			random0 = rand() % 3;
			if (random0 == 0) {
				comment = "Playing singles can be a great way to improve your individual skills and strategy.\n";
				cout << comment << endl;
			}
			else if (random0 == 1) {
				comment = "In singles, you have complete control over your performance, which can be both empowering and challenging.\n";
				cout << comment << endl;
			}
			else {
				comment = "Singles requires a different mindset and approach than doubles, so be prepared to adjust your tactics accordingly.\n";
				cout << comment << endl;
			}

		}
		else if (scr == "2") {
			srand(time(0));
			int random0 = 0;
			random0 = rand() % 3;
			if (random0 == 0) {
				comment = " Playing doubles requires effective communication and teamwork.\n";
				cout << comment << endl;
			}
			else if (random0 == 1) {
				comment = " In doubles, you have a partner to rely on and can work together to achieve success.\n";
				cout << comment << endl;
			}
			else {
				comment = "Doubles can be a more social and enjoyable experience, as you get to share the game with a friend or teammate.\n";
				cout << comment << endl;
			}
		}
		else if (scr == "3") {
			srand(time(0));
			int random0 = 0;
			random0 = rand() % 3;
			if (random0 == 0) {
				comment = " Triples is like a three-ring circus, with each player bringing their unique skills and personalities to create a show-stopping performance.\n";
				cout << comment << endl;
			}
			else if (random0 == 1) {
				comment = " Playing triples is like being part of a secret agent team - you have to work together, communicate in code, and execute your mission flawlessly.\n";
				cout << comment << endl;
			}
			else {
				comment = "Triples is like a game of three-dimensional chess, with multiple layers of strategy and coordination required to outmaneuver your opponents and claim victory.\n";
				cout << comment << endl;
			}
		}
		else if (scr == "4") {
			srand(time(0));
			int random0 = 0;
			random0 = rand() % 3;
			if (random0 == 0) {
				comment = " Wow, what a shot! That ball absolutely raced to the boundary like a greyhound chasing a rabbit!\n";
				cout << comment << endl;
			}
			else if (random0 == 1) {
				comment = "The fielders had no chance of catching that one - it flew off the bat and raced to the boundary like a cheetah chasing down its prey!\n";
				cout << comment << endl;
			}
			else {
				comment = "That ball was hit with such force and precision that it rocketed to the boundary like a speeding bullet from a gun!\n";
				cout << comment << endl;
			}
		}

		else if (scr == "5") {
			srand(time(0));
			int random0 = 0;
			random0 = rand() % 3;
			if (random0 == 0) {
				comment = "What a fantastic shot! That ball sailed over the fielder's head and went for five runs, like a majestic eagle soaring through the sky!\n";
				cout << comment << endl;
			}
			else if (random0 == 1) {
				comment = "Five runs! The crowd erupts with excitement as the batsman drives the ball past the boundary, like a rocket blasting off into space!\n";
				cout << comment << endl;
			}
			else {
				comment = " That's the way to do it! The batsman smashes the ball with all their might and it flies to the boundary for a glorious five runs, like a speeding train charging down the tracks!\n";
				cout << comment << endl;
			}
		}

		else if (scr == "6") {
			srand(time(0));
			int random0 = 0;
			random0 = rand() % 6;
			if (random0 == 0) {
				comment = " The ball is out of the roof !!!\n";
				cout << comment << endl;
			}
			else if (random0 == 1) {
				comment = "That's just smashed out of the ground.\n";
				cout << comment << endl;
			}
			else if (random0 == 2) {
				comment = "That's a big hit into the stands. Phenomenal\n";
				cout << comment << endl;
			}
			else if (random0 == 3) {
				comment = "What a hit! The ball clears the boundary by a mile, sailing into the stands like a fireworks display on the Fourth of July!\n";
				cout << comment << endl;
			}
			else if (random0 == 4) {
				comment = "Six runs! The batsman swings with all their might and the ball rockets off the bat, flying high into the air like a bird taking flight!\n";
				cout << comment << endl;
			}
			else if (random0 == 5) {
				comment = "It's outta here! The crowd goes wild as the ball soars over the fence for a magnificent six runs, like a home run in baseball!\n";
				cout << comment << endl;
			}
		}
		else if (scr == "wide") {
			srand(time(0));
			int random0 = 0;
			random0 = rand() % 3;
			if (random0 == 0) {
				comment = " Ugh, a wide ball! The bowler looks disappointed as the ball sails wide of the wicket, like a driver losing control on a winding road.\n";
				cout << comment << endl;
			}
			else if (random0 == 1) {
				comment = "That one got away from the bowler! The batsman watches with a smile as the ball veers off course for a frustrating wide, like a lost hiker wandering off the trail.\n";
				cout << comment << endl;
			}
			else {
				comment = "Come on, bowler! The fielders groan in unison as the ball flies wide of the wicket for an annoying wide, like a misfiring cannon missing its target.\n";
				cout << comment << endl;
			}
		}
		else if (scr == "noball") {
			srand(time(0));
			int random0 = 0;
			random0 = rand() % 3;
			if (random0 == 0) {
				comment = " Oh no, a no ball! The bowler looks dejected as the ball crosses the line, like a student failing a crucial exam.\n";
				cout << comment << endl;
			}
			else if (random0 == 1) {
				comment = "That's not what the team needed! The batsman grins as the ball sails over their head for a no ball, like a runaway train hurtling off the tracks.\n";
				cout << comment << endl;
			}
			else {
				comment = "You've got to be kidding me! The fielders throw their hands up in exasperation as the ball goes beyond the boundary for a no ball, like a ship drifting aimlessly in the ocean.\n";
				cout << comment << endl;
			}
		}

		else if (scr == "out") {
			srand(time(0));
			int random0 = 0;
			random0 = rand() % 3;
			if (random0 == 0) {
				comment = " Oh, what a shame! The batsman trudges off the field, head down, after getting out, like a runner collapsing at the finish line.\n";
				cout << comment << endl;
			}
			else if (random0 == 1) {
				comment = " That was a close one! The fielders breathe a sigh of relief as they realize they've taken a crucial wicket, like a soldier narrowly escaping enemy fire.\n";
				cout << comment << endl;
			}
			else {
				comment = "You win some, you lose some. The batsman looks disappointed as they make their way back to the pavilion, like a defeated warrior leaving the battlefield.\n";
				cout << comment << endl;
			}
		}
	}
	void CommentFileOutput() {
		ofstream file("Commentator.txt", ios::app);
		file << scr << "\t" << this->comment;
		file.close();
	}
};
