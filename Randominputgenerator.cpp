#include "RandomInputGenerator.h"
#include <iostream>
#include <algorithm>
#include <random>

void RandomInputGenerator::generateHand(Deck& deck, TurnInput& input) {
    std::mt19937 rng(std::random_device{}());

    // Bangun full deck manual agar bisa kita manipulasi sebelum deal
    std::vector<Card> allCards;
    for (Suit s : {Suit::HEARTS, Suit::DIAMONDS, Suit::CLUBS, Suit::SPADES}) {
        for (int r = 2; r <= 14; ++r) {
            allCards.push_back({s, static_cast<Rank>(r)});
        }
    }

    // ── Bias: pilih anchor rank (2–10) agar masih ada ruang 5 rank ke depan
    std::uniform_int_distribution<int> anchorDist(2, 10);
    int anchor = anchorDist(rng);

    // Kumpulkan semua kartu yang rank-nya masuk window [anchor, anchor+4]
    std::vector<Card> window, rest;
    for (auto& c : allCards) {
        int r = static_cast<int>(c.rank);
        if (r >= anchor && r <= anchor + 4)
            window.push_back(c);
        else
            rest.push_back(c);
    }

    // Shuffle keduanya secara terpisah
    std::shuffle(window.begin(), window.end(), rng);
    std::shuffle(rest.begin(),   rest.end(),   rng);

    // Ambil 5 kartu dari window (bahan straight) + 2 dari rest
    // Jika window kurang dari 5 (jarang terjadi), ambil semua & tambal dari rest
    input.dealtCards.clear();
    int fromWindow = std::min(5, (int)window.size());
    for (int i = 0; i < fromWindow; ++i)
        input.dealtCards.push_back(window[i]);
    for (int i = 0; (int)input.dealtCards.size() < 7 && i < (int)rest.size(); ++i)
        input.dealtCards.push_back(rest[i]);

    std::cout << "[GENERATE] (straight-biased) anchor=" << anchor
              << " Dealt 7: ";
    for (auto& c : input.dealtCards)
        std::cout << c.toString() << " ";
    std::cout << "\n";
}