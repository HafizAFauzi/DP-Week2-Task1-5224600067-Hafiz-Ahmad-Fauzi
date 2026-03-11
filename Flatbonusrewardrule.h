#pragma once
#include "IRewardRule.h"

// Modification 2: reward = baseScore + 2
// Reward TIDAK sama dengan base score lagi (membuktikan mutable behavior).
// Menang: dapat score + 2 cash
// Kalah : dapat 1 cash (consolation, agar tetap bisa beli di shop)
//
// RunSession TIDAK diubah — hanya injeksi di main.cpp yang diganti.
class FlatBonusRewardRule : public IRewardRule {
public:
    int computeReward(int score, int round, bool win) override;
};