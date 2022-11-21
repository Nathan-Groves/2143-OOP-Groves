/*****************************************************************************
 *
 *  Author:           Nathan Groves
 *  Title:            BolNiverse Fight Club
 *  Course:           2143
 *  Semester:         Fall 2022
 *
 *  Description:
     Implements a game where two armies are made to fight each other
     until one side is fully defeated. The attackers are more numerous 
     than the defenders, and the armies of composed of wizards, warriors,
     archers, elves, and dragonBorn, each with their own varying damage.
     A random army size between 100 and 1000 that is a multiple of 100 is
     is made to be the attacking army size, while the defenders are 1/20th 
     the size. The winner and final stats are printed to an outfile after
     battle.
 *        
 *
 *  Usage:
 *   To allow the player to simulate an instance of BolNiverse Fight Club
 *
 *
 * Files: main.cpp
          dice.hpp
          fighter.hpp
          helpers.hpp
          weapon.hpp
 *****************************************************************************/


#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <fstream>


#include "dice.hpp"
#include "weapon.hpp"
#include "helpers.hpp"
#include "fighter.hpp"



//array to pick to pick a random size from
const int armySize[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};


/*
Name       : createChoiceList

Purpose    : create list of possible die
             values for a given character

Parameters : string denoting character type
             vector to hold the die choices

Returns    : nothing
            
*/
void createChoiceList(string w, vector<string> & VectorChoices);

/*
Name       : fillAArmy

Purpose    : fill attacking army with each
             character type, each with an
             appropriate distribution

Parameters : the vector of basefighters
             int size of the army
             vector of choices for unit type
             string to denote what character is added

Returns    : nothing
            
*/
void fillAArmy(vector<BaseFighter*> & Army, int armySize, vector<string> & VectorChoices, string character);

/*
Name       : fillDArmy

Purpose    : fill defending army with each
             character type, each with an
             appropriate distribution

Parameters : the vector of basefighters
             int size of the army
             vector of choices for unit type
             string to denote what character is added

Returns    : nothing
            
*/
void fillDArmy(vector<BaseFighter*> & Army, int armySize, 
  vector<string> & VectorChoices, string character);

/*
Name       : tallyRound

Purpose    : to increment the number of rounds
             and add point to who won the round

Parameters : the addresses of the variables that
             store the rounds and wins

Returns    : nothing
            
*/
void tallyRound(int & roundsFought, int & teamWhoWon);

/*
Name       : removeUnit

Purpose    : once a unit is below health,
             remove unit from battle and 
             change unit to a new one if
             the army is not empty

Parameters : vector of army units
             basefighter pointer for current fighter

Returns    : nothing
            
*/
void removeUnit(vector<BaseFighter*> & Army, BaseFighter * & Unit);

/*
Name       : printScoreboard

Purpose    : to print the final results of battle

Parameters : the values for team wins, total rounds, 
             and the winner

Returns    : nothing
            
*/
void printScoreboard(int, int, int, string, ofstream &);



int main() 
  {
    srand(time(0));

    //open outfile
    ofstream outfile;
    outfile.open("output.txt");

    //create an attacking army whose size is a multiple of
    //100 up to 1000, and create a defending army that is 1/20th that
    int ArmySizeA = armySize[rand() % 10];
    int ArmySizeD = ArmySizeA / 20;
    outfile << "Attacker army size: " << ArmySizeA << endl;
    outfile << "Defender army size: " << ArmySizeD << endl << endl;

    //create a vector for possible die rolls for each class
    vector<string>warriorChoices;
    vector<string>wizardChoices;
    vector<string>archerChoices;
    vector<string>elfChoices;
    vector<string>dragonBornChoices;

    //initialize the values for end scoreboard
    int rounds = 0;
    int teamOneWins = 0;
    int teamTwoWins = 0;
    string winner = "";


    //initialize the choice list for each class
   createChoiceList("warrior", warriorChoices);
   createChoiceList("wizard", wizardChoices);
   createChoiceList("archer", archerChoices);
   createChoiceList("elf", elfChoices);
   createChoiceList("dragonBorn", dragonBornChoices);


   //initialize a vector of basefighter pointer for each side
   vector<BaseFighter*> Defenders;
   vector<BaseFighter*> Attackers;

    //fill the attacking army ranks and shuffle them
    fillAArmy(Attackers, ArmySizeA, dragonBornChoices, "dragonBorn");
    fillAArmy(Attackers, ArmySizeA, warriorChoices, "warrior");
    fillAArmy(Attackers, ArmySizeA, wizardChoices, "wizard");
    fillAArmy(Attackers, ArmySizeA, elfChoices, "elf");
    fillAArmy(Attackers, ArmySizeA, archerChoices, "archer");
    random_shuffle(Attackers.begin(), Attackers.end());

    //fill the defending army ranks and shuffle them
    fillDArmy(Defenders, ArmySizeD, dragonBornChoices, "dragonBorn");
    fillDArmy(Defenders, ArmySizeD, warriorChoices, "warrior");
    fillDArmy(Defenders, ArmySizeD, wizardChoices, "wizard");
    fillDArmy(Defenders, ArmySizeD, elfChoices, "elf");
    fillDArmy(Defenders, ArmySizeD, archerChoices, "archer");
    random_shuffle(Defenders.begin(), Defenders.end());
    
     //create the base pointers that each army will use to
     //control who is in the fight
     BaseFighter * defender = Defenders.back();
     BaseFighter * attacker = Attackers.back();

    //runs so long as their is a warrior to fight for each side
    while (attacker->Health() > 0 && defender->Health() > 0)
      {
    //the attacker takes damage from the defender
    attacker->takeDamage(defender->attack());

    //if the attacker is still alive, they attack
    if (attacker->Health() > 0)
    {
    defender->takeDamage(attacker->attack());
    }

      //if attacker died, remove them and add a
      //new one if possible, then tally points
      if (attacker->Health() <= 0)
      {
         removeUnit(Attackers, attacker);
        tallyRound(rounds, teamOneWins);
        defender->regenHealth();
      }
      //if defender died, remove them and add a
      //new one if possible, then tally points
      else if (defender->Health() <= 0)
      {
        removeUnit(Defenders, defender);
        tallyRound(rounds, teamTwoWins);
        attacker->regenHealth();
      }
        //if neither died, let them both regen
        else
      {
        defender->regenHealth();
        attacker->regenHealth();
      }
        
      }

    //once the loop is exited, check to
    //see which side's ranks are empty
    //and determine the winner
    if (Defenders.empty())
    {
      winner = "Attackers";
    }
    else
    {
      winner = "Defenders";
    }

    //print final stats
    printScoreboard(teamOneWins, teamTwoWins, rounds, winner, outfile);

    return 0;
    
  }


void fillDArmy(vector<BaseFighter*> & Army, int armySize, vector<string> & Choices, string characterType)
{
  //make each unit a fifth of the army total
  int warriorSize = armySize / 5;
  int wizardSize = armySize / 5;
  int archerSize = armySize / 5;
  int elfSize = armySize / 5;
  int dragonBornSize = armySize / 5;

  //make a proportionate amount of characters
  if (characterType == "warrior")
  {
  for (int i = 0; i < warriorSize; i++)
    {
    Army.push_back(new Warrior(Choices));
    }
   }
   else if (characterType == "wizard")
  {
  for (int i = 0; i < wizardSize; i++)
    {
    Army.push_back(new Wizard(Choices));
    }
    }
  else  if (characterType == "archer")
  {
  for (int i = 0; i < archerSize; i++)
    {
      Army.push_back(new Archer(Choices));
    }
    }
   else if (characterType == "elf")
   {
  for (int i = 0; i < elfSize; i++)
    {
      Army.push_back(new Elf(Choices));
    }
    }
  else if (characterType == "dragonBorn")
  {
  for (int i = 0; i < dragonBornSize; i++)
    {
      Army.push_back(new DragonBorn(Choices));
    }
    }
  
}


void fillAArmy(vector<BaseFighter*> & Army, int armySize, vector<string> & Choices, string characterType)
{
  //make warriors, wizards and archers equal to
  //75% of army, and the elf and dragonborn equal
  //to the remaining amount
  int warriorSize = armySize / 4;
  int wizardSize = armySize / 4;
  int archerSize = armySize / 4;
  int elfSize = armySize / 8;
  int dragonBornSize = armySize / 8;

  //make a proportionate amount of fighters
  if (characterType == "warrior")
  {
  for (int i = 0; i < warriorSize; i++)
    {
    Army.push_back(new Warrior(Choices));
    }
   }
  else if (characterType == "wizard")
  {
  for (int i = 0; i < wizardSize; i++)
    {
    Army.push_back(new Wizard(Choices));
    }
    }
 else  if (characterType == "archer")
  {
  for (int i = 0; i < archerSize; i++)
    {
      Army.push_back(new Archer(Choices));
    }
    }
  //procs if leading number is odd, letting an elf fill
  //in the empty slot
  else if (characterType == "elf" && !(armySize % 8 == 0))
   {
  for (int i = 0; i < elfSize + 1; i++)
    {
      Army.push_back(new Elf(Choices));
    }
    }
   else if (characterType == "elf" && (armySize % 8 == 0))
    {
  for (int i = 0; i < elfSize; i++)
    {
      Army.push_back(new Elf(Choices));
    }
      }
 else if (characterType == "dragonBorn")
  {
  for (int i = 0; i < dragonBornSize; i++)
    {
      Army.push_back(new DragonBorn(Choices));
    }
    }
}

void tallyRound(int & roundsFought, int & teamWhoWon)
{
  roundsFought++;
  teamWhoWon++;
}

void removeUnit(vector<BaseFighter*> & Army, BaseFighter * & Unit)
{
  Army.pop_back();
  if (Army.size() > 0)
  {
    Unit = Army.back();
  }
}

void printScoreboard(int teamOneWins, int teamTwoWins, int roundsFought, string winner, ofstream & outfile)
{
     outfile << "Final Stats" << endl;
    outfile << "-------------------------" << endl;
    outfile << "Team One Round Wins: " << teamOneWins << endl;
    outfile << "Team Two Round Wins: " << teamTwoWins << endl;
    outfile  << "rounds fought: " << roundsFought << endl;
    outfile << "The Winner is " << winner << endl;
    outfile << "percent of battle won by Defenders: " <<
    ((double)teamOneWins / roundsFought) * 100 << "%" << endl;
    outfile << "percent of battle won by Attackers: " <<
    ((double)teamTwoWins / roundsFought) * 100 << "%";
}


void createChoiceList(string character, vector<string> & Choices)
{
  //create choice list for character type put in
  if (character == "warrior")
  {
  Choices.push_back("1.d.12");
  Choices.push_back("2.d.6");
  Choices.push_back("3.d.4");
    }
  else if (character == "wizard")
  {
  Choices.push_back("1.d.20");
  Choices.push_back("2.d.10");
  Choices.push_back("3.d.6");
  Choices.push_back("5.d.4");

  }
  else if (character == "archer")
  {
  Choices.push_back("1.d.8");
  Choices.push_back("2.d.4");
  Choices.push_back("1.d.10");
  }
  else if (character == "elf")
  {
  Choices.push_back("1.d.4");
  Choices.push_back("1.d.6");
  }
  else if (character == "dragonBorn")
  {
  Choices.push_back("1.d.6");
  Choices.push_back("1.d.8");
  }
}

