#pragma once
#include "Card.h"
#include <vector>

// Data container yang mengalir dari Generate → Choose → Score
// RunSession tidak peduli isinya, hanya meneruskan antar fase
struct TurnInput {
    std::vector<Card> dealtCards;   // hasil Generate Hand (7 kartu)
    std::vector<Card> chosenCards;  // hasil Choose Hand (5 kartu)
};
