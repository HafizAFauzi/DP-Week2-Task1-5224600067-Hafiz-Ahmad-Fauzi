#include "StandardHandGenerator.h"
#include <iostream>

void StandardHandGenerator::generateHand(Deck& deck, TurnInput& input) {
    // Deck sudah di-reset & shuffle oleh RunSession sebelum fase ini
    input.dealtCards = deck.draw(7);

    std::cout << "[GENERATE] Dealt 7 cards: ";
    for (auto& c : input.dealtCards)
        std::cout << c.toString() << " ";
    std::cout << "\n";
}
