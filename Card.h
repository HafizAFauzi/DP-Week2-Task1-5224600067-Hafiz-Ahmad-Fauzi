#pragma once
#include <string>

enum class Suit { HEARTS, DIAMONDS, CLUBS, SPADES };

enum class Rank {
    TWO=2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT,
    NINE, TEN, JACK, QUEEN, KING, ACE
};

struct Card {
    Suit suit;
    Rank rank;

    std::string suitName() const;
    std::string rankName() const;
    std::string toString() const;
    int         value()    const;
};
