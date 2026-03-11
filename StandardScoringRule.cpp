#include "StandardScoringRule.h"
#include <iostream>

int StandardScoringRule::computeScore(const TurnInput& input) {
    HandResult base = HandEvaluator::evaluate(input.chosenCards);

    int totalChips = base.chips + getChipsBonus(base.type);
    int totalMult  = base.mult  + getMultBonus (base.type);
    int final      = totalChips * totalMult;

    std::cout << "[SCORE]    Hand  : " << base.name << "\n";
    std::cout << "[SCORE]    Chips : " << base.chips;
    if (getChipsBonus(base.type) > 0)
        std::cout << " (+" << getChipsBonus(base.type) << " bonus)";
    std::cout << " = " << totalChips << "\n";

    std::cout << "[SCORE]    Mult  : " << base.mult;
    if (getMultBonus(base.type) > 0)
        std::cout << " (+" << getMultBonus(base.type) << " bonus)";
    std::cout << " = " << totalMult << "\n";

    std::cout << "[SCORE]    Final : " << totalChips << " x "
              << totalMult << " = " << final << "\n";

    return final;
}

void StandardScoringRule::addChipsBonus(HandType type, int chips) {
    chipsBonus[type] += chips;
}

void StandardScoringRule::addMultBonus(HandType type, int mult) {
    multBonus[type] += mult;
}

int StandardScoringRule::getChipsBonus(HandType type) const {
    auto it = chipsBonus.find(type);
    return (it != chipsBonus.end()) ? it->second : 0;
}

int StandardScoringRule::getMultBonus(HandType type) const {
    auto it = multBonus.find(type);
    return (it != multBonus.end()) ? it->second : 0;
}
