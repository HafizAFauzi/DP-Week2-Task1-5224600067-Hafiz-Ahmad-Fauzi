#pragma once
#include "IScoringRule.h"
#include <map>

// Implementasi scoring standar: (baseChips + bonusChips) * (baseMult + bonusMult)
// Bonus diakumulasi dari pembelian di ShopSystem
class StandardScoringRule : public IScoringRule {
private:
    std::map<HandType, int> chipsBonus;   // bonus chips per hand type dari shop
    std::map<HandType, int> multBonus;    // bonus mult  per hand type dari shop

public:
    int  computeScore  (const TurnInput& input)        override;
    void addChipsBonus (HandType type, int chips)       override;
    void addMultBonus  (HandType type, int mult)        override;
    int  getChipsBonus (HandType type) const            override;
    int  getMultBonus  (HandType type) const            override;
};
