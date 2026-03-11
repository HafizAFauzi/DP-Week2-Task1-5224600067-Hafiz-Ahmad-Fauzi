#include "Card.h"

std::string Card::suitName() const {
    switch (suit) {
        case Suit::HEARTS:   return "H";
        case Suit::DIAMONDS: return "D";
        case Suit::CLUBS:    return "C";
        case Suit::SPADES:   return "S";
    }
    return "?";
}

std::string Card::rankName() const {
    int v = static_cast<int>(rank);
    if (v >= 2 && v <= 10) return std::to_string(v);
    switch (rank) {
        case Rank::JACK:  return "J";
        case Rank::QUEEN: return "Q";
        case Rank::KING:  return "K";
        case Rank::ACE:   return "A";
        default:          return "?";
    }
}

std::string Card::toString() const {
    return rankName() + suitName();
}

int Card::value() const {
    int v = static_cast<int>(rank);
    if (v > 10) return 10;
    return v;
}
