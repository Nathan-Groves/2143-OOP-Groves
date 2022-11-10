/*****************************************************************************
 *
 *  Author:           Nathan Groves
 *  Title:            RPSLS
 *  Course:           2143
 *  Semester:         Fall 2022
 *
 *  Description:
      Implements a game of Rock Paper Scissors Lizard Spock, wherein
      two players are created and assigned random hand values. The 
      values are then compared to determine a winner and a point is given       to them. Then the user is asked whether they want to play again. If       a tie occurs a new value is created for each player until a winner        is found. At program end the final score is displayed.
 *        
 *
 *  Usage:
 *   To allow the player to simulate as many rounds of RPSLS as they 
 *   wish, after providing a user input confirming they wish to
 *
 * File: main.cpp
 *****************************************************************************/

#include <iostream>
//#include "emoji.h"    //https://github.com/99x/emojicpp
#include <functional>  // needed for `bind`
#include <map>
#include <random>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

/*
Name       : compareHands

Purpose    : to look at two hand string
             values to see who wins or if
             they tie

Parameters : the two string values to be
             compared

Returns    : an int value to determine if
             player one won, player two
             won, or if they tied

*/
int compareHands(string, string);


/*
Name       : scoreAdd

Purpose    : to add to the score of a player
             based on who won the round

Parameters : the int that determines who won,
             as well as the passed-by-reference
             values of each player score

Returns    : nothing, as it changes the address
             values of the player scores within the 
             function

*/
void scoreAdd(int, int &, int &);


#define ROCK u8"\U0000270A"
#define PAPER u8"\U0000270B"
#define SCISSORS u8"\U0001F44C"
#define LIZARD u8"\U0001F918"
#define SPOCK u8"\U0001F596"

#define ROCK2 u8"\U0001F5FB"
#define PAPER2 u8"\U0001F4C3"
#define SCISSORS2 u8"\U0001F52A"
#define LIZARD2 u8"\U0001F438"
#define SPOCK2 u8"\U0001F596"

struct Emoji{
  string type;
};

class Spock: public Emoji {
  bool operator <(const Emoji other){
    if(other.type == "Lizard" || other.type == "Paper"){
      return true;
    }
    return false;
  }
  
};

class Lizard{

};

/**
 * RandRoll
 * @description: A class to implement roll playing dice rolls.
 * @methods:
 * private:
 *      int Random(Max) : returns a value between 0 and max.
 *      int Random(Min , Max) : returns a value between min and max
 *      void init(int , int)  : initialize class
 * public:
 *      DieRoll()
 *      DieRoll(int)
 *      DieRoll(int,int)
 *      void setDie(int)    : set sides
 *      int Roll(int,int)   :  NEEDS FIXING!!!!!!
 */
class DieRoll {
    int sides;

    int Random(int max) {
        return 1 + (rand() % max);
    }

    // min = 40 max = 100
    int Random(int min, int max) {
        return 1 + min + (rand() % (max - min));
    }
    void init(int _seed, int _sides) {
        sides = _sides;
        srand(_seed);
    }
public:
    DieRoll() {
        //cout << "default base" << endl;
        init(time(0), 6);
    }
    DieRoll(int _seed) {
        //cout << "overloaded const" << endl;
        init(_seed, 6);
    }
    DieRoll(int _seed, int _sides) {
        //cout << "overloaded const" << endl;
        init(_seed, _sides);
    }

    void setDie(int _sides) {
        sides = _sides;
    }

};


/**
 * RandRoll
 * @description: A random die roller using a "better" random
 *      number generator. Docs: https://www.cplusplus.com/reference/random/
 * 
 * @methods:
 *     int Roll(int)    : give the "sides" will return an int between 1 and sides inclusive.
 * 
 */
class RandRoll {
    default_random_engine           generator;
    uniform_int_distribution< int > dieMap[21];

public:
    /**
     * Constructor
     * 
     * @description: Create an stl array that has the common dice values
     *              loaded as uniform distribution types.
     * 
     *  Wasteful, as not every array location has a uniform distribution 
     *  associated with it. Could you make it less wasteful?
     */
    RandRoll() {
        dieMap[4] = uniform_int_distribution< int >(1, 4);
        dieMap[6] = uniform_int_distribution< int >(1, 6);
        dieMap[8] = uniform_int_distribution< int >(1, 8);
        dieMap[10] = uniform_int_distribution< int >(1, 10);
        dieMap[12] = uniform_int_distribution< int >(1, 12);
        dieMap[20] = uniform_int_distribution< int >(1, 20);
    }

    /**
     * Generate a random number depending on the "sides" of the dice.
     */
    int Roll(int sides) {
        int diceRoll = dieMap[sides](generator);
        return diceRoll;
    };
};

/**
 * Hands
 * 
 * @description: A static class that only has references to
 *      emojis for printing out Rock Paper Scissors Lizard Spock
 * 
 * @methods:
 *      string RandHand()   : returns a random hand (emoji) 
 *      string Rock()       : returns the emoji for "rock" 
 *      string Paper()      : returns the emoji for "paper" 
 *      string Scissors()   : returns the emoji for "scissors" 
 *      string Lizard()     : returns the emoji for "lizard" 
 *      string Spock()      : returns the emoji for "spock" 
 */
struct Hands {
    const string rock = ROCK2;
    const string paper = PAPER2;
    const string scissors = SCISSORS2;
    const string lizard = LIZARD2;
    const string spock = SPOCK2;

    static map< string, string > Emojis;  // stl map
    //         name  , emoji

    static map< string, string > Names;  // stl map
    //         emoji  , name

    static string RandHand() {
        auto it = Emojis.begin();  // iterator to front of map

        std::advance(it, rand() % Emojis.size());  // advance some random amnt
                                                   //   of steps

        string random_hand = it->second;  // grab emoji from map

        return random_hand;  // return rand emoji
    }

    static string Rock() {
        return Emojis["rock"];
    }
    static string Paper() {
        return Emojis["paper"];
    }
    static string Scissors() {
        return Emojis["scissors"];
    }
    static string Lizard() {
        return Emojis["lizard"];
    }
    static string Spock() {
        return Emojis["spock"];
    }
};

// initialize static data member for
// hands struct (class)
map< string, string > Hands::Emojis = {
    {"rock", ROCK2},
    {"paper", PAPER2},
    {"scissors", SCISSORS2},
    {"lizard", LIZARD2},
    {"spock", SPOCK2}};
// initialize static data member for
// hands struct (class)
map< string, string > Hands::Names = {
    {ROCK2, "rock"},
    {PAPER2, "paper"},
    {SCISSORS2, "scissors"},
    {LIZARD2, "lizard"},
    {SPOCK2, "spock"}};

/**
 * Rock Paper Scissors Lizard Spock
 * 
 * @description: A class to run the rock papers scissors game
 * 
 * Scissors cuts Paper
 * Paper covers Rock
 * Rock crushes Lizard
 * Lizard poisons Spock
 * Spock smashes Scissors
 * Scissors decapitates Lizard
 * Lizard eats Paper
 * Paper disproves Spock
 * Spock vaporizes Rock
 * Rock crushes Scissors
 */
class RPSLS : public DieRoll, public Hands {
public:
    RPSLS(): DieRoll(time(0)){
        string h = RandHand();
        cout<<Names[h]<<": " <<h<<endl;
    };
    RPSLS(int seed) : DieRoll(seed) {
        cout << "Rock: " << Rock() << endl;
    }
};

int main() {

    //initialize dieRoll and whether the user
    //wants to keep running the program
    DieRoll dr;
    string wantToPlay = "y";

    //keep track of the running score of each player
    int player1score, player2score = 0;
    
    //welcome message to game
    cout << "\nWelcome to Rock Paper Scissors Lizard Spock" << endl;
    cout << "=============================================" << endl;
    cout << endl;

  //run as long as the player wants to play
  while (wantToPlay == "y" || wantToPlay == "Y")
    {

    //create a random hand value for each player
    string h1 = Hands::RandHand();
    string h2 = Hands::RandHand();

    sleep(1);


    //show each player's hand
    cout << "Player One's " << h1 <<
    " vs Player Two's " << h2 <<endl << endl;

    //used to denote who won
    int numCompare = 0;

    sleep(1);

    //compare each player's hand to determine
    //who wins
    numCompare = compareHands(h1, h2);

    //add score to who won
    scoreAdd(numCompare, player1score, player2score);

    //so long as the players have tied
    //run another round of RPSLS
    while (numCompare == 0)
      {

     sleep(1);
     string h1 = Hands::RandHand();
     string h2 = Hands::RandHand();


    //show each players hand again
    cout << endl << "Player One's " << h1 <<
    " vs Player Two's " << h2 <<endl << endl;
    //compare after each new hand
    numCompare = compareHands(h1, h2);

    //add score to who won
    scoreAdd(numCompare, player1score, player2score);
      }

    //ask the player if they want to play again
    cout << endl << endl << "Enter y to run again: ";
    cin >> wantToPlay;
    cout << endl << endl << endl;

      }

    //an exit message and final score count
    cout << "Player 1's final score is " << player1score << endl;
    cout << "Player 2's final score is " << player2score << endl;
    cout << "Thank you for playing!";
  
    return 0;
}


  //function to compare each player's hand value
  //and determine who wins
  int compareHands(string Player1, string Player2)
  {
  if (Player1 == Player2)
  {
    cout << "Players have tied, run the program again" << endl;
    return 0;
  }
  else if (Player1 == Hands::Rock())
  {
    if (Player2 == Hands::Lizard() || Player2 == Hands::Scissors())
    {
      cout << "Player 1 wins";
      return 1;
    }
    else
    {
      cout << "Player 2 wins";
      return -1;
    }
  }
  else if (Player1 == Hands::Paper())
  {
    if (Player2 == Hands::Rock() || Player2 == Hands::Spock())
    {
      cout << "Player 1 wins";
      return 1;
    }
    else
    {
      cout << "Player 2 wins";
      return -1;
    }
  }
  else if (Player1 == Hands::Scissors())
  {
    if (Player2 == Hands::Paper() || Player2 == Hands::Lizard())
    {
      cout << "Player 1 wins";
      return 1;
    }
    else
    {
      cout << "Player 2 wins";
      return -1;
    }
  }
  else if (Player1 == Hands::Lizard())
  {
    if (Player2 == Hands::Paper() || Player2 == Hands::Spock())
    {
      cout << "Player 1 wins";
      return 1;
    }
    else
    {
      cout << "Player 2 wins";
      return -1;
    }
  }
  else if (Player1 == Hands::Spock())
  {
    if (Player2 == Hands::Rock() || Player2 == Hands::Scissors())
    {
      cout << "Player 1 wins";
      return 1;
    }
    else
    {
      cout << "Player 2 wins";
      return -1;
    }
  }
  }

  //used to add to the score of the player who won the round
  void scoreAdd(int numToCheck, int & firstscore, int & secondscore)
  {
  if (numToCheck == 1)
  {
    firstscore++;
  }
  else if (numToCheck == -1)
  {
    secondscore++;
  }
  }
