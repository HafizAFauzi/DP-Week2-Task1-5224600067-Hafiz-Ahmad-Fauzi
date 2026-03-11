#include "RunSession.h"
#include "RandomInputGenerator.h"   // Mod 1: ganti generator
#include "PlayerHandChooser.h"
#include "StandardScoringRule.h"
#include "FlatBonusRewardRule.h"     // Mod 2: reward = score + 2
#include "ShopSystem.h"

// main hanya:
// 1. Buat implementasi konkret
// 2. Inject ke RunSession
// 3. Jalankan run
// RunSession tidak diubah sama sekali untuk kedua modifikasi ini.
int main() {
    RandomInputGenerator  generator;    // Mod 1: straight-biased
    PlayerHandChooser     chooser;
    StandardScoringRule   scoringRule;
    FlatBonusRewardRule   rewardRule;   // Mod 2: reward = score + 2

    ShopSystem shop(&scoringRule);

    RunSession session(&generator, &chooser, &scoringRule, &rewardRule, &shop);
    session.run();

    return 0;
}