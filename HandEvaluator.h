#pragma once
#include "Card.h"
#include <vector>
#include <string>
#include <map>

enum class HandType {
    HIGH_CARD = 0,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    STRAIGHT_FLUSH,
    ROYAL_FLUSH
};

// Hasil evaluasi hand: chips dan mult terpisah seperti Balatro
// finalScore = chips * mult
struct HandResult {
    HandType    type;
    std::string name;
    int         chips;       // base chips dari hand type
    int         mult;        // base multiplier dari hand type
    int         finalScore() const { return chips * mult; }
};

class HandEvaluator {
public:
    static HandResult evaluate(const std::vector<Card>& hand);

    // Untuk ShopSystem: ambil nama hand type sebagai string key
    static std::string handTypeName(HandType t);

private:
    static bool             isFlush   (const std::vector<Card>& h);
    static bool             isStraight(const std::vector<Card>& h);
    static bool             isRoyal   (const std::vector<Card>& h);
    static std::map<int,int> rankCounts(const std::vector<Card>& h);
    static bool             hasN      (const std::map<int,int>& cnt, int n);
    static bool             twoPair   (const std::map<int,int>& cnt);
};
