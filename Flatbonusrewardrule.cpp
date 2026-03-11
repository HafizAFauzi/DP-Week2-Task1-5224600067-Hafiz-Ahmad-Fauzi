#include "FlatBonusRewardRule.h"
#include <iostream>

int FlatBonusRewardRule::computeReward(int score, int round, bool win) {
    if (!win) {
        std::cout << "[REWARD]   Lost round — consolation: $1\n";
        return 1;
    }

    int reward = score + 2;
    std::cout << "[REWARD]   " << score << " + 2 = $" << reward << "\n";
    return reward;
}