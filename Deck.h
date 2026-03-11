#pragma once
#include "Card.h"
#include <vector>

class Deck {
private:
    std::vector<Card> cards;
    int topIndex = 0;

public:
    Deck();

    void reset();
    void shuffle(unsigned seed);
    void shuffle();          // uses random_device

    Card              draw();
    std::vector<Card> draw(int n);
    int               remaining() const;
};
