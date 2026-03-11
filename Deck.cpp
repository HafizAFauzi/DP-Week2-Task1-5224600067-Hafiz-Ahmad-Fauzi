#include "Deck.h"
#include <algorithm>
#include <random>
#include <stdexcept>

Deck::Deck() { reset(); }

void Deck::reset() {
    cards.clear();
    topIndex = 0;
    for (Suit s : {Suit::HEARTS, Suit::DIAMONDS, Suit::CLUBS, Suit::SPADES}) {
        for (int r = 2; r <= 14; ++r) {
            cards.push_back({s, static_cast<Rank>(r)});
        }
    }
}

void Deck::shuffle(unsigned seed) {
    std::mt19937 rng(seed);
    std::shuffle(cards.begin(), cards.end(), rng);
    topIndex = 0;
}

void Deck::shuffle() {
    shuffle(std::random_device{}());
}

Card Deck::draw() {
    if (topIndex >= (int)cards.size())
        throw std::runtime_error("Deck is empty!");
    return cards[topIndex++];
}

std::vector<Card> Deck::draw(int n) {
    std::vector<Card> hand;
    for (int i = 0; i < n; ++i)
        hand.push_back(draw());
    return hand;
}

int Deck::remaining() const {
    return (int)cards.size() - topIndex;
}
