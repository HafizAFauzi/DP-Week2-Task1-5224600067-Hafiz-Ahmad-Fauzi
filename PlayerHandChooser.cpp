#include "PlayerHandChooser.h"
#include "HandEvaluator.h"
#include <iostream>
#include <numeric>

void PlayerHandChooser::chooseHand(TurnInput& input) {
    auto& dealt = input.dealtCards;

    int              bestScore = -1;
    std::vector<Card> bestHand;

    // Coba semua C(7,5) = 21 kombinasi, pilih yang finalScore tertinggi
    std::vector<int> pick(5);
    std::iota(pick.begin(), pick.end(), 0);

    do {
        std::vector<Card> candidate;
        for (int i : pick) candidate.push_back(dealt[i]);

        HandResult res = HandEvaluator::evaluate(candidate);
        if (res.finalScore() > bestScore) {
            bestScore = res.finalScore();
            bestHand  = candidate;
        }
    } while (nextCombination(pick, (int)dealt.size()));

    input.chosenCards = bestHand;

    std::cout << "[CHOOSE]   Best 5: ";
    for (auto& c : input.chosenCards)
        std::cout << c.toString() << " ";
    std::cout << "\n";
}

bool PlayerHandChooser::nextCombination(std::vector<int>& pick, int n) {
    int k = (int)pick.size();
    int i = k - 1;
    while (i >= 0 && pick[i] == n - k + i) --i;
    if (i < 0) return false;
    ++pick[i];
    for (int j = i + 1; j < k; ++j) pick[j] = pick[j-1] + 1;
    return true;
}
