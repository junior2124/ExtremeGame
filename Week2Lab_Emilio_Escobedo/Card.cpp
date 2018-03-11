#include "Card.h"

bool Card::randomizerSeeded = false;

Card::Card() {
	if (!randomizerSeeded)
	{
		srand(time(0));
		randomizerSeeded = true;

	}

	short min = 3;
	short max = 6;
	suit = rand() % (max - min + 1) + min;

	min = 2;
	max = 14;
	short number = rand() % (max - min + 1) + min;

	if (number >= 2 && number <= 9) {
		face = number + 48;
		value = number;
	}
	else if (number == 10) {
		face = 'T';
		value = 10;
	}
	else if (number == 11) {
		face = 'J';
		value = 10;
	}
	else if (number == 12) {
		face = 'Q';
		value = 10;
	}
	else if (number == 13) {
		face = 'K';
		value = 10;
	}
	else if (number == 14) {
		face = 'A';
		value = 11;
	}	
}

Card::~Card(){}

string Card::toString() {
	string output = "";
	output += suit;
	output += face;
	return output;
}

bool Card::flipAceToOne() {
	if (value == 11) {
		value = 1;
		return true;
	}
	else {
		return false;
	}
}