/*	YAHTZEE.cpp
	
	Ryan Pickelsimer
	Programming 1 Section 1
	May 26, 2014

	This program simulates the game of YAHTZEE. The game can be played with one ore more players and
	is over when all scorecard categories are filled in. The final results are displayed in ranking order.
 */

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Scorecard contains a player name and thirteen scoring categories.
class Scorecard {

	int aces, twos, threes, fours, fives, sixes, threeKind, fourKind;
	int fullHouse, smallStrt, largeStrt, chance;

public:
	string name;
	int yahtzee;
	Scorecard(string);
	~Scorecard() {};
	void setScore(int, int);
	int getTotalScore();
	void printScorecard();
	void check(int);
};

//Scorecard constructor
Scorecard::Scorecard(string playerName) {
	name = playerName;
	aces = 0;
	twos = 0;
	threes = 0;
	fours = 0;
	fives = 0;
	sixes = 0;
	threeKind = 0;
	fourKind = 0;
	fullHouse = 0;
	smallStrt = 0;
	largeStrt = 0;
	yahtzee = 0;
	chance = 0;
}

// getTotalScore() returns an integer value equal to a player's total points.
int Scorecard::getTotalScore() {
	int total = 0;
	total = aces + twos + threes + fours + fives + sixes + threeKind +
		fourKind + fullHouse + smallStrt + largeStrt + yahtzee + chance;
	return total;
}

// setScore() updates a player's score.
void Scorecard::setScore(int selection, int score) {
	switch (selection) {
	case 1:
		aces = score;
		break;
	case 2:
		twos = score;
		break;
	case 3:
		threes = score;
		break;
	case 4:
		fours = score;
		break;
	case 5:
		fives = score;
		break;
	case 6:
		sixes = score;
		break;
	case 7:
		threeKind = score;
		break;
	case 8:
		fourKind = score;
		break;
	case 9:
		fullHouse = score;
		break;
	case 10:
		smallStrt = score;
		break;
	case 11:
		largeStrt = score;
		break;
	case 12:
		yahtzee = score;
		break;
	case 13:
		chance = score;
		break;
	default: cout << "/nYour score was not properly recorded.";
	}
}

// printScorecard() displays a player's scorecard.
void Scorecard::printScorecard() {
	cout << "\n\n\t\tPlayer " << name << " Scorecard\n";
	cout << "\n1) Aces  2) Twos  3) Threes  4) Fours  5) Fives  6) Sixes";
	cout << "\n    ";
	check(aces);
	cout << "\t     ";
	check(twos);
	cout << "\t       ";
	check(threes);
	cout << "\t  ";
	check(fours);
	cout << "\t    ";
	check(fives);
	cout << "\t      ";
	check(sixes);
	cout << "\n\n7) 3 of  8) 4 of  9) Full  10) Small  11) Large";
	cout << "\n  a Kind   a Kind    House    Straight   Straight  12) YAHTZEE  13) Chance";
	cout << "\n    ";
	check(threeKind);
	cout << "\t      ";
	check(fourKind);
	cout << "\t       ";
	check(fullHouse);
	cout << "\t ";
	check(smallStrt);
	cout << "\t    ";
	check(largeStrt);
	cout << "\t          ";
	check(yahtzee);
	cout << "\t      ";
	check(chance);
	cout << "\n";
	cout << "\n14) Enter a zero in a category\n";
}

void Scorecard::check(int inty) {

	if (inty == 0) {
		cout << ' ';
	}
	else {
		cout << inty;
	}
}

int diceRoller();
void showDice(int[]);
int calcUpperScore(int hand[], int diceToScore);
int diceTotaler(int hand[]);
int rollOption();

// _tmain() holds the game control loop.
int _tmain(int argc, _TCHAR* argv[])
{
	const int NUM_DICE = 5, TURN = 3, ROUNDS = 13;
	int round = 0;
	int numPlayer;
	string playerName;
	vector<Scorecard> players;
	int hand[NUM_DICE];


	// player setup
	cout << "\tWelcome to the game of YAHTZEE!";
	cout << "\n\nHow many people will be playing? ";
		cin >> numPlayer;
	for (int i = 0; i < numPlayer; i++) {	
		cout << "\nEnter Player " << i + 1 << " Name: ";
		cin.ignore();
		getline(cin, playerName);		
		Scorecard player(playerName);
		players.push_back(player);
	}

	// 13 round game loop
	while (round < ROUNDS) {
		round++;
		cout << "\n\tRound " << round;
		cout << "\n\t--------";
		srand(static_cast<unsigned int>(time(0)));

		// player loop
		for (int p = 0; p < numPlayer; p++) {			
			cout << "\n\nAre you ready, " << players[p].name << "? ";
			cin.ignore();
			string s;
			getline(cin, s);

			// turn loop
			int choice, sel, score;
			int keepRolling = 1;

			for (int i = 0; i < NUM_DICE; i++){
				hand[i] = diceRoller();
			}
			showDice(hand);

			while (keepRolling < TURN) {
				choice = rollOption();

				if (choice == 1) {
					keepRolling++;
					int keep;
						cout << "\nHow many dice would you like to keep? ";
					cin >> keep;
					int numRolls = NUM_DICE - keep;
					if (keep == 0) {
						for (int i = 0; i < NUM_DICE; i++){
							hand[i] = diceRoller();
						}
						showDice(hand);
					}
					else {
						int in;
						cout << "\nWhich " << keep <<" dice would you like to save?";
						cout << "\nEnter the face values with no spaces: ";
						cin >> in;
						for (int i = 0; i < NUM_DICE; i++) {
							if (i < keep) {
								hand[i] = in % 10;
								in = in/10;
							}
							else {
								hand[i] = diceRoller();
							}
						}
						showDice(hand);
					}
				}
				else if (choice == 2) {
					keepRolling = TURN;
				}
			}

			// player score
			cout << "\n";
			players[p].printScorecard();
			cout << "\n\nIn what category would you like to record your score? ";
				cin >> sel;			
			if (sel == 12)
				if (players[p].yahtzee != 0) {
					players[p].yahtzee += 100;
					cout << "\nTo which category would you like to apply the Joker Rules? ";
						cin >> sel;
				}
			if (sel < 7)
				score = calcUpperScore(hand, sel);
			else if (sel == 7 || sel == 8 || sel == 13)
				score = diceTotaler(hand);
			else if (sel == 9)
				score = 25;
			else if (sel == 10)
				score = 30;
			else if (sel == 11)
				score = 40;
			else if (sel == 12)
				score = 50;
			else if (sel == 14) {
				score = 0;
				cout << "\n\nIn what category would you like to record a zero? ";
					cin >> sel;
			}
			players[p].setScore(sel, score);
			players[p].printScorecard();
		}
	}

	// display results
	cout << "\n\n\n\tFinal Scores";
	cout << "\n-----------------------\n";
	int temp1, temp2;
	int index = 0;
	int ceiling = 2000;
	for (int i = 0; i < numPlayer; i++){		
		temp1 = 0;
		for (int j = 0; j < numPlayer; j++) {
			temp2 = players[j].getTotalScore();
			if ((temp2 < ceiling) && (temp2 > temp1)) {
				temp1 = temp2;
				index = j;
			}
		}
		cout << "\n" << players[index].name << "\t" << players[index].getTotalScore();
		ceiling = temp1;
	}
	cin.sync();
	cin.get();
	return 0;
}

// diceRoller() uses a RNG to generate a given number of dice rolls.

int diceRoller(){
		
	int ranNum;
	ranNum = (rand() % 6) + 1;
	return ranNum;
}

// showDice() displays the current hand.
void showDice(int hand[]) {
	cout << "\n";
	for (int i = 0; i < 5; i++)
		cout << hand[i] << " ";
}

// calcUpperScore() adds all dice with a given number in a hand.
int calcUpperScore(int hand[], int diceToScore) {
	int score = 0;
	if (diceToScore < 7)
	for (int i = 0; i < 5; i++)
	if (hand[i] == diceToScore)
		score = score + diceToScore;
	return score;
}

// diceTotaler() returns the total face value of a hand.
int diceTotaler(int hand[]) {
	int diceTotal = 0;
	for (int i = 0; i < 5; i++)
		diceTotal = diceTotal + hand[i];
	return diceTotal;
}

// rollOption() returns a user response from a turn decision.
int rollOption() {
	int sel;
	cout << "\n\nWould You Like To";
	cout << "\n\n\t1) Roll Again";
	cout << "\n\t2) Record Score" << endl;
	cin >> sel;
	return sel;
}
