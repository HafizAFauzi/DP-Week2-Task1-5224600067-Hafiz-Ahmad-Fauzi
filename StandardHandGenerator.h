#pragma once
#include "IHandGenerator.h"

// Implementasi standar: uniform random deal 7 kartu
class StandardHandGenerator : public IHandGenerator {
public:
    void generateHand(Deck& deck, TurnInput& input) override;
};
