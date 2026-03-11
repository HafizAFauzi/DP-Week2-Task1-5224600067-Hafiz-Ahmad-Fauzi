#pragma once
#include "TurnInput.h"
#include "Deck.h"

class IHandGenerator {
public:
    virtual ~IHandGenerator() = default;
    virtual void generateHand(Deck& deck, TurnInput& input) = 0;
};
