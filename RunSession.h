#pragma once
#include "TurnInput.h"
#include "Deck.h"
#include "IHandGenerator.h"
#include "IHandChooser.h"
#include "IScoringRule.h"
#include "IRewardRule.h"
#include "ShopSystem.h"

// RunSession adalah INVARIANT:
// Urutan 6 fase tidak boleh berubah.
// Tidak berisi scoring, reward, atau input generation logic.
class RunSession {
private:
    static constexpr int TOTAL_ROUNDS = 3;

    IHandGenerator* generator;
    IHandChooser*   chooser;
    IScoringRule*   scoringRule;
    IRewardRule*    rewardRule;     // Mod 2: reward dipisah ke interface sendiri
    ShopSystem*     shop;

    int money = 5;   // starting money untuk bisa beli item pertama di shop

    // ── Fase-fase (urutan ini adalah invariant) ───────────────────
    TurnInput phase_generateHand(Deck& deck);
    void      phase_chooseHand  (TurnInput& input);
    int       phase_computeScore(const TurnInput& input);
    bool      phase_checkWin    (int score, int target);
    void      phase_countCash   (int score, int round, bool win);
    void      phase_shop        ();
    // ─────────────────────────────────────────────────────────────

    int getTargetScore(int round) const;

public:
    RunSession(IHandGenerator* gen,
               IHandChooser*   cho,
               IScoringRule*   sc,
               IRewardRule*    rr,
               ShopSystem*     sh);

    void run();
};