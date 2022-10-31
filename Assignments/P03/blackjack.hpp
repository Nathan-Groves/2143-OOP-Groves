// necessary libraries and files
#include "colors.h"
#include <algorithm> // std::random_shuffle
#include <fstream>
#include <iostream>
#include <map>
// https : // en.cppreference.com/w/cpp/container/map
#include <stdio.h>
#include <string>

#include <vector>



using namespace std;

typedef map<string, string> printableCard;

const string spade = "♠";
const string diamond = "♦";
const string heart = "♥";
const string club = "♣";

const string suits[4] = {"♠", "♦", "♣", "♥"};

// Card labels (could be "Iron Man" or "Charmander" or "Elf" ... anything)
const string ranks[13] =
	{"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

// Lets us use the suit symbol to lookup a default color.
// You can edit this colorMap if you like.
map<string, string> colorMap{{"♠", BBLACK},
							 {"♥", BRED},
							 {"♦", BRED},
							 {"♣", BBLACK}};
/*
   ____    _    ____  ____
  / ___|  / \  |  _ \|  _ \
 | |     / _ \ | |_) | | | |
 | |___ / ___ \|  _ <| |_| |
  \____/_/   \_\_| \_\____/

*/

class Card {
protected:
	int suitNum;	 // value 0-3 : num index of suit
	int rank;		 // 0-13      : num value of rank
	int number;		 // 1-52      : unique value determines card
	int value;		 // 1-14      : numeric value used for comparison
	string suitChar; // "♠", "♦", "♣", "♥"
	string rankChar; // Ace, 1 ,2 ,3 ... Q, K
	string fcolor;   // Spade=blue, Diamond=red, etc.
	string bcolor;
	void Init(int, string, string);

public:
	Card(int);
	Card(int, string, string);

	string Repr();
	bool operator<(const Card &);
	bool operator>(const Card &);
	bool operator==(const Card &);
	bool operator!=(const Card &);

	friend ostream &operator<<(ostream &os, const Card &card);

	int getRank() {
		return rank;
	}
	string getRankChar() {
		return rankChar;
	}
	string getSuitChar() {
		return suitChar;
	}
	string getfColor() {
		return fcolor;
	}
	string getbColor() {
		return bcolor;
	}

	printableCard cardMap() {
		string content;

		// only 2 digit rank
		if (rankChar != "10") {
			content = " " + suitChar + " " + rankChar;
		} else {
			content = " " + suitChar + rankChar;
		}

		printableCard p{{"TOP", fcolor + bcolor + "┌────┐"},
						{"MID", fcolor + bcolor + "│" + content + "│"},
						{"BOT", fcolor + bcolor + "└────┘" + OFF}};

		return p;
	}
};

Card::Card(int num) {
	int color = num / 13;
	// If no color specified, then use colorMap to
	// make spades and clubs black / hearts and diamonds red
	Init(num, colorMap[suits[color]], ON_WHITE);
}

Card::Card(int num, string fgc, string bgc) {
	Init(num, fgc, bgc);
}

void Card::Init(int num, string fgc, string bgc) {
	number = num;
	suitNum = number / 13;
	suitChar = suits[suitNum];
	fcolor = fgc;
	bcolor = bgc;
	rank = number % 13;
	rankChar = ranks[rank];
}
