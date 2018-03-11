/* 
 Programmer: Emilio Escobedo
 Date: 03/05/2018
 Program: Black Jack for Console
*/

#include <iostream>
#include <string>
#include <conio.h>
#include "Card.h"
#include <vector>

using namespace std;

string showCards(vector<Card> cards);
short sumCardValues(vector<Card> cards);
void playHand(short &cash);

int main() {
	short cash = 100;

	cout << "Welcome to BlackJack Extreme!" << endl;
	cout << "\nYou are starting out with $" << cash << endl;

	cout << "\nPress any key to continue...";
	_getch();

	short choice = 0;

	do {
		system("cls");
		cout << "Menu\n" << endl;
		cout << "1) Play a hand" << endl;
		cout << "2) Show current cash balance" << endl;
		cout << "3) Exit" << endl;

		cout << "\nEnter your choice:";
		cin >> choice;

		switch (choice)
		{
		case 1:
			playHand(cash);
			break;
		case 2:
			cout << "\nYour current cash balance: $" << cash << endl;
			break;
		case 3:
			cout << "\nThank you for playing Extreme BlackJack!" << endl;
			cout << "\nYour final cash position: $" << cash << endl;
			break;
		default:
			cout << "Error. Please select from the menu." << endl;
			break;
		}

		cout << "n\Press any key to continue...";
		_getch();

	} 
	while (choice != 3);

	return 0;
}

string showCards(vector<Card> cards)
{
	string output = "";
	for each (Card c in cards)
	{
		output += c.toString() + " ";
	}

	return output;
}

short sumCardValues(vector<Card> cards) {
	short total = 0;

	for each (Card c in cards) {
		total += c.getValue();
	}

	return total;
}

void playHand(short &cash) {
	// create two ArrayLists that can hold Card objects
	// an ArrayList is a resizable array in C++, the ArrayList is called a vector
	vector<Card> dealerCards;
	vector<Card> playerCards;
	short dealerCardsTotal = 0;
	short playerCardsTotal = 0;

	// get bet amount
	short bet = 0;
	cout << "\nEnter bet amount: ";
	cin >> bet;

	// create two cards for the dealer and show the first one
	Card card1;
	Card card2;
	dealerCards.push_back(card1);
	dealerCards.push_back(card2);
	dealerCardsTotal = sumCardValues(dealerCards);

	cout << "\nDealer is showing: " << dealerCards[0].toString() << endl;

	// create two cards for the player and show them both
	playerCards.push_back(Card()); // create the card and put it directly into the arraylist (vector)
	playerCards.push_back(Card());
	playerCardsTotal = sumCardValues(playerCards);

	cout << "\nHere are your cards: " << showCards(playerCards) << endl;

	// give cards to the player until they stand ('S')
	char answer = '?';

	do
	{
		cout << "\nDo you want to hit or stand (H/S)? ";
		cin.sync(); // flush the input stream (keyboard buffer)
		cin >> answer;
		cin.sync();

		if (toupper(answer) == 'H')
		{
			// give a card to the player
			Card c;
			cout << "\nYou were dealt this card: " << c.toString() << endl;
			playerCards.push_back(c); // add card to player's hand
			
			// sum up the card values
			playerCardsTotal = sumCardValues(playerCards);

			// did the player bust?
			if (playerCardsTotal > 21)
			{
				// do you have an Ace that can be dropped to a 1 value
				for each (Card c in playerCards)
				{
					if (c.getValue() == 11)
					{
						cout << "\nYour total is " << playerCardsTotal << endl;
						c.flipAceToOne();
						cout << "However, you have an Ace that was converted to a '1' vlaue" << endl;
						playerCardsTotal = sumCardValues(playerCards);
						cout << "\nYour new total is " << playerCardsTotal << endl;

						// if we are good now, break out of the loop. otherwise, keep looking for an ace
						if (playerCardsTotal <= 21)
							break;
					}
				}
			}

			// show the cards and the total
			cout << "\nHere are your cards: " << showCards(playerCards) << endl;
			cout << "Your total is " << playerCardsTotal << endl;

			// if busted, stop the loop
			if (playerCardsTotal > 21)
				answer = 'S';
		}
	}while(toupper(answer) != 'S');

	// if player's cardTotal is more than 21, the player busted so take money away
	if (playerCardsTotal > 21)
	{
		cout << "\nYou busted!" << endl;
		cash = cash - bet;
	}
	else
	{
		// player stands so the dealer hits until 17 or greater
		do {
			if (dealerCardsTotal < 17)
			{
				Card c;
				cout << "\nDealer was dealt: " << c.toString() << endl;
				dealerCards.push_back(c); // add the cards to the dealer's hand
				cout << "\nDealer cards: " << showCards(dealerCards) << endl;
				dealerCardsTotal = sumCardValues(dealerCards);
				cout << "\nDealer total:" << dealerCardsTotal << endl;
			}
		} while (dealerCardsTotal < 17);

		// show the cards for the dealer and the player
		cout << "\nYour cards: " << showCards(playerCards) << " (" << playerCardsTotal << ")" << endl;
		cout << "\nDealer cards: " << showCards(dealerCards) << " (" << dealerCardsTotal << ")" << endl;

		// who wins?
		if (dealerCardsTotal > 21)
		{
			cout << "\nDealer busted!" << endl;
			cash = cash + bet;
		}
		else if (dealerCardsTotal > playerCardsTotal)
		{
			cout << "\nDealer wins!" << endl;
			cash = cash - bet;
		}
		else if (playerCardsTotal > dealerCardsTotal)
		{
			cout << "\nYou win!" << endl;
			cash = cash + bet;
		}
		else
		{
			cout << "\nYou pushed the dealer (tie)." << endl;
		}
	}

	// show the current cash postion
	cout << "\nYour current cash balance: $" << cash << endl;
}