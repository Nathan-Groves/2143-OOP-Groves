/*****************************************************************************
 *
 *  Author:           Nathan Groves
 *  Title:            Blackjack
 *  Course:           2143
 *  Semester:         Fall 2022
 *
 *  Description:
      Implements a game of Blackjack wherein the player
      can play multiple rounds so long as they have money
      to bet. It takes in betting amounts and allows for 
      the player to play against a dealer, then asking them
      if they wish to play again.
 *        
 *
 *  Usage:
 *    To let the user/player play a game of blackjack against a dealer, while 
 *    adhering to the rules of the game
 *
 * Files: main.cpp
 * Files: blackjack.hpp
 * Files: colors.h
 *****************************************************************************/


//necessary libraries and files
#include "blackjack.hpp"
#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


using namespace std;

/**
   * Purpose - compute the value of all cards in a hand
   *
   * param cards - vector of Card pointers
   * param numOfCards - number of cards to check
   * returns: int - natural number value of hand
   */
  int checkHandValue(vector<Card *> cards, int numOfCards)
  {

  int i = 0;
  int TotalValues = 0;

  while (i < numOfCards) 
     {
       //since all face cards are 10 in blackjack, only
       // add ten to total value
      if (cards[i]->getRank() >= 10) {
        TotalValues += 10;
      }
       else {
        TotalValues += cards[i]->getRank() +1;
      }
        i++;
      }

  return TotalValues;

}

/**
   * Purpose - print a single card from a hand to console
   *
   * param cards - vector of Card pointers
   * returns: none
   */
  void printSingleCard(vector<Card *> cards) 
  {
	printableCard c;
	int index = 0;
  
  //only runs once, as only one cards needs printed
	while (index < 1) {
		for (int i = index; i < index + 1; i++) {
			c = cards[i]->cardMap();
			cout << c["TOP"] << OFF;
		}
		cout << endl;
		for (int i = index; i < index + 1; i++) {
			c = cards[i]->cardMap();
			cout << c["MID"] << OFF;
		}
		cout << endl;
		for (int i = index; i < index + 1; i++) {
			c = cards[i]->cardMap();
			cout << c["BOT"] << OFF;
		}
		cout << endl;
		index++;	
	}
  cout << endl;
  }

/**
   * Purpose - print all cards from hand to console
   *
   * param cards - vector of Card pointers
   * param cols = number of columns made when printed
   * returns: none
   */
  void printCardVector(vector<Card *> cards, int cols = 2) 
  {
	printableCard c;
	int index = 0;
	while (index < cards.size()) {
		for (int i = index; i < index + cols; i++) {
			c = cards[i]->cardMap();
			cout << c["TOP"] << OFF;
		}
		cout << endl;
		for (int i = index; i < index + cols; i++) {
			c = cards[i]->cardMap();
			cout << c["MID"] << OFF;
		}
		cout << endl;
		for (int i = index; i < index + cols; i++) {
			c = cards[i]->cardMap();
			cout << c["BOT"] << OFF;
		}
		cout << endl;
		index += cols;
		if (index + cols >= 52) {
			cols = 52 % cols;
		}
	}

  cout << endl;
  }

int main() {

  //Welcome message for blackjack, sets out rules for play
   cout << endl << "Welcome to Blackjack!" << endl
    << "Aces count as 1 & max draw count is 8" << endl
    << "You have 100 dollars to bet with" << endl;
  cout <<"----------------------------------------" << endl
    << endl;

  //variables to keep track of whether players wants to play
  //how much they bet, and how much they can bet
  string playAgain = "y";
  int amountBet = 0;
  int bettingBank = 100;

  //run so long as the player has betting money and wants to play
  while (playAgain == "y" && !(bettingBank < 1))
    {

      cout << "Enter a betting amount: ";
      cin >> amountBet;

      //make sure the amount is within acceptable range
      while (amountBet < 1 || amountBet > bettingBank)
        {
          sleep (1);
          cout << endl << "Please enter a valid amount: ";
          cin >> amountBet;
        }

    //sets the default columns to 2
  int playerColumns = 2;
  int dealerColumns = 2;

   //create instances of player and dealer cards
	srand(time(0));
	vector<Card *> Playercards;
  vector<Card *> dealerCards;

	for (int i = 0; i < 2; i++) {
		Playercards.push_back(new Card(rand()%52));
    dealerCards.push_back(new Card(rand()%52));
	}
      
  //display initial cards, 2 for player 1 for dealer
  cout << endl << endl << "Your initial cards:";
    cout << endl << endl;
  	printCardVector(Playercards, 2);
  cout << "The dealer's visible card:";
    cout << endl << endl;
    printSingleCard(dealerCards);

  // keep track of whether the player wants to keep
  // hitting, how much their hand value is
  string keepPlaying = "h";
  int HandValue = 0;

  // keep going so long as the player wants to keep hitting
  // and the hand value is not over 20
  while (keepPlaying == "h" && !(HandValue > 20))
  {

    cout << endl;
    cout << "Enter h to hit or anything else to stand: ";
    cin >> keepPlaying;
    cout << endl;

    // if the player wants to hit, give them a new card
    // and print it out
      if (keepPlaying == "h")
      {
       cout << "Your new hand" << endl << endl;
       playerColumns++;
       Playercards.push_back(new Card(rand()%52));

        // if the card count has reached 10, divide columns by 2
        if (playerColumns > 9 && playerColumns % 2 == 0)
         {
         	printCardVector(Playercards, playerColumns /2);
         }
            
         else 
         {
          printCardVector(Playercards,playerColumns);
         }
        }

      // compute the new value of the player's hand
      HandValue = checkHandValue(Playercards, playerColumns);

      }

  // compute the player's final hand value, and dealer's current
  // hand value
  int dealerCardVals = checkHandValue(dealerCards, dealerColumns);  
  int playerFinalValue = checkHandValue(Playercards, playerColumns);

  sleep (1);
      
  // if the player has 21, they instantly win
  if (checkHandValue(Playercards, playerColumns) == 21)
  {
    cout << endl << "You Win!";
    bettingBank += amountBet;
    cout << endl << "Your new balance is: " << bettingBank
      << endl;
  }

  // if the player has more than 21, they instantly lose
  else if (checkHandValue(Playercards, playerColumns) > 21)
  {
    cout << endl << "You have busted!";
    bettingBank -= amountBet;
    cout << endl << "Your new balance is: " << bettingBank
      << endl;
  }

  // if the player has neither 21 nor > 21, then the dealer
  // must try to get 21
  else 
  {
    
  // clear the console to get rid of clutter
         cout.flush();
        system("clear");
    
  // display the player's final cards, and the dealer's
  // fully revealed initial 2 cards
    cout << endl << "Your final cards: " << endl;
    printCardVector(Playercards, playerColumns);
    cout << endl << "The dealer's revealed cards: " << endl;
    printCardVector(dealerCards, dealerColumns);

    // while the dealer's hand value is less than 16 and 
    // not more than 20, he will keep hitting and printing
    // out his new hand
    while (dealerCardVals <= 16 && !(dealerCardVals > 20))
    {
        sleep(3);
        dealerColumns++;
        dealerCards.push_back(new Card(rand()%52));
        cout << "The dealer's new hand" << endl;
        printCardVector(dealerCards, dealerColumns);
        dealerCardVals = checkHandValue(dealerCards, dealerColumns);
    }
        sleep(2);
    
    // if the dealer has more than 21, they lose
    if (dealerCardVals > 21)
    {
      cout << endl << "The dealer busted, you win!" << endl;
      bettingBank += amountBet;
      cout << "Your new balance is: " << bettingBank
        << endl;
    }
    // if the dealer has more than the player, they win
     else if (dealerCardVals > playerFinalValue)
     {
      cout << endl << "The dealer has won" << endl;
      bettingBank -= amountBet;
      cout << "Your new balance is: " << bettingBank
         << endl;
     }
    // if the dealer has the same as the player, they tie
    else if (dealerCardVals == playerFinalValue)
     {
       cout << endl << "You have tied" << endl;
       cout << "Your balance is: " << bettingBank
        << endl;
     }
    // if the player has more than the dealer, they win
    else 
    {
      cout << endl << "You won!" << endl;
      bettingBank += amountBet;
      cout << "Your new balance is: " << bettingBank
        << endl;
    }

    }

      sleep (2);

    // if the player has more money, they are asked whether
    // they want to play again
      if (bettingBank > 0)
      {
      cout << endl;
      cout << "Enter y to play again or anything else to stop: ";
      cin >> playAgain;
      cout << endl << endl;
        }
    // if the player has no more money, they exit the while loop,
    // ending the program
      else 
      {
      cout << endl;
      cout <<"Come back again when you have more money!";
      cout << endl << endl;
      sleep(2);
      }

      // clear the screen when leaving the program or
      // when playing another round
        cout.flush();
        system("clear");
    
  }

    sleep(1);

  // end game and tell player their end balance
  cout << "Thank you for playing!" << endl;
  cout << "Your end balance is " << bettingBank;

  return 0;
}
