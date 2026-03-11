#pragma once
#include "IHandChooser.h"

// Auto-pilih kombinasi 5 kartu terbaik dari 7 yang di-deal
// Simulasi player optimal (akan diganti dengan input manusia nanti)
class PlayerHandChooser : public IHandChooser {
public:
    void chooseHand(TurnInput& input) override;

private:
    bool nextCombination(std::vector<int>& pick, int n);
};
