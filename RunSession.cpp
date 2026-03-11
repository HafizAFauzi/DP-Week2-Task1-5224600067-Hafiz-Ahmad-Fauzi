#include "RunSession.h"
#include <iostream>

RunSession::RunSession(IHandGenerator* gen,
                       IHandChooser*   cho,
                       IScoringRule*   sc,
                       IRewardRule*    rr,
                       ShopSystem*     sh)
    : generator(gen), chooser(cho), scoringRule(sc), rewardRule(rr), shop(sh) {}

// ── Implementasi tiap fase ────────────────────────────────────────

TurnInput RunSession::phase_generateHand(Deck& deck) {
    TurnInput input;
    generator->generateHand(deck, input);
    return input;
}

void RunSession::phase_chooseHand(TurnInput& input) {
    chooser->chooseHand(input);
}

int RunSession::phase_computeScore(const TurnInput& input) {
    return scoringRule->computeScore(input);
}

bool RunSession::phase_checkWin(int score, int target) {
    bool win = score >= target;
    std::cout << "[WIN]      " << score
              << (win ? " >= " : " < ")
              << target << " (target) → "
              << (win ? "WIN!" : "LOSE!") << "\n";
    return win;
}

void RunSession::phase_countCash(int score, int round, bool win) {
    // Reward logic didelegasikan sepenuhnya ke IRewardRule
    // RunSession tidak tahu formula reward — itu urusan implementasi
    int gained = rewardRule->computeReward(score, round, win);
    money += gained;
    std::cout << "[CASH]     +$" << gained
              << " | Total: $" << money << "\n";
}

void RunSession::phase_shop() {
    shop->runShop(money);
}

// ─────────────────────────────────────────────────────────────────

int RunSession::getTargetScore(int round) const {
    int targets[] = { 20, 60, 150 };
    return targets[round - 1];
}

void RunSession::run() {
    Deck deck;
    std::cout << "=== RUN START ===\n\n";

    for (int round = 1; round <= TOTAL_ROUNDS; ++round) {
        std::cout << "━━━ Round " << round << " ━━━━━━━━━━━━━━━━━━━━\n";
        std::cout << "[TARGET]   Score needed: " << getTargetScore(round) << "\n";

        deck.reset();
        deck.shuffle();

        // INVARIANT PHASE ORDER — tidak boleh diubah
        TurnInput input  = phase_generateHand(deck);
        phase_chooseHand(input);
        int  score = phase_computeScore(input);
        bool win   = phase_checkWin(score, getTargetScore(round));
        phase_countCash(score, round, win);
        phase_shop();

        std::cout << "\n";
    }

    std::cout << "=== RUN END ===\n";
    std::cout << "Final money: $" << money << "\n";
}