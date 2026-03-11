#include "RunSession.h"
#include "StandardHandGenerator.h"
#include "PlayerHandChooser.h"
#include "StandardScoringRule.h"
#include "ShopSystem.h"

// main hanya:
// 1. Buat implementasi konkret
// 2. Inject ke RunSession
// 3. Jalankan run
// Tidak ada game logic di sini
int main() {
    StandardHandGenerator generator;
    PlayerHandChooser     chooser;
    StandardScoringRule   scoringRule;

    // ShopSystem di-inject IScoringRule yang sama
    // agar bisa langsung modifikasi bonus saat player beli item
    ShopSystem shop(&scoringRule);

    RunSession session(&generator, &chooser, &scoringRule, &shop);
    session.run();

    return 0;
}
