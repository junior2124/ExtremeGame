#pragma once

#include <string>
#include <ctime>

using namespace std;

class Card {
private:
	char suit;
	char face;
	short value;
	static bool randomizerSeeded;

public:
	// constructors and destructors
	Card();
	~Card();

	// behaviors
	string toString();
	bool flipAceToOne();

	// accessors and mutators
    inline char getSuit() { return suit; }
	inline char getFace() { return face; }
 	inline short getValue() { return value; }

};