#include "HandEvaluator.h"
#include <algorithm>

// Base chips & mult per hand type (mirip Balatro)
// finalScore = chips * mult
static const std::map<HandType, std::pair<int,int>> BASE_VALUES = {
    { HandType::HIGH_CARD,       {  5, 1 } },
    { HandType::ONE_PAIR,        { 10, 2 } },
    { HandType::TWO_PAIR,        { 20, 2 } },
    { HandType::THREE_OF_A_KIND, { 30, 3 } },
    { HandType::STRAIGHT,        { 30, 4 } },
    { HandType::FLUSH,           { 35, 4 } },
    { HandType::FULL_HOUSE,      { 40, 4 } },
    { HandType::FOUR_OF_A_KIND,  { 60, 7 } },
    { HandType::STRAIGHT_FLUSH,  { 100,8 } },
    { HandType::ROYAL_FLUSH,     { 100,8 } },
};

HandResult HandEvaluator::evaluate(const std::vector<Card>& hand) {
    bool flush    = isFlush(hand);
    bool straight = isStraight(hand);
    auto counts   = rankCounts(hand);

    HandType type;

    if      (flush && straight && isRoyal(hand)) type = HandType::ROYAL_FLUSH;
    else if (flush && straight)                  type = HandType::STRAIGHT_FLUSH;
    else if (hasN(counts, 4))                    type = HandType::FOUR_OF_A_KIND;
    else if (hasN(counts, 3) && hasN(counts, 2)) type = HandType::FULL_HOUSE;
    else if (flush)                              type = HandType::FLUSH;
    else if (straight)                           type = HandType::STRAIGHT;
    else if (hasN(counts, 3))                    type = HandType::THREE_OF_A_KIND;
    else if (twoPair(counts))                    type = HandType::TWO_PAIR;
    else if (hasN(counts, 2))                    type = HandType::ONE_PAIR;
    else                                         type = HandType::HIGH_CARD;

    auto [chips, mult] = BASE_VALUES.at(type);
    return { type, handTypeName(type), chips, mult };
}

std::string HandEvaluator::handTypeName(HandType t) {
    switch (t) {
        case HandType::HIGH_CARD:       return "High Card";
        case HandType::ONE_PAIR:        return "One Pair";
        case HandType::TWO_PAIR:        return "Two Pair";
        case HandType::THREE_OF_A_KIND: return "Three of a Kind";
        case HandType::STRAIGHT:        return "Straight";
        case HandType::FLUSH:           return "Flush";
        case HandType::FULL_HOUSE:      return "Full House";
        case HandType::FOUR_OF_A_KIND:  return "Four of a Kind";
        case HandType::STRAIGHT_FLUSH:  return "Straight Flush";
        case HandType::ROYAL_FLUSH:     return "Royal Flush";
    }
    return "Unknown";
}

bool HandEvaluator::isFlush(const std::vector<Card>& h) {
    Suit s = h[0].suit;
    for (auto& c : h) if (c.suit != s) return false;
    return true;
}

bool HandEvaluator::isStraight(const std::vector<Card>& h) {
    std::vector<int> ranks;
    for (auto& c : h) ranks.push_back(static_cast<int>(c.rank));
    std::sort(ranks.begin(), ranks.end());

    bool normal = true;
    for (int i = 1; i < (int)ranks.size(); ++i)
        if (ranks[i] != ranks[i-1] + 1) { normal = false; break; }
    if (normal) return true;

    // Ace-low: A-2-3-4-5
    return ranks == std::vector<int>{2, 3, 4, 5, 14};
}

bool HandEvaluator::isRoyal(const std::vector<Card>& h) {
    std::vector<int> ranks;
    for (auto& c : h) ranks.push_back(static_cast<int>(c.rank));
    std::sort(ranks.begin(), ranks.end());
    return ranks == std::vector<int>{10, 11, 12, 13, 14};
}

std::map<int,int> HandEvaluator::rankCounts(const std::vector<Card>& h) {
    std::map<int,int> cnt;
    for (auto& c : h) cnt[static_cast<int>(c.rank)]++;
    return cnt;
}

bool HandEvaluator::hasN(const std::map<int,int>& cnt, int n) {
    for (auto& [r, c] : cnt) if (c == n) return true;
    return false;
}

bool HandEvaluator::twoPair(const std::map<int,int>& cnt) {
    int pairs = 0;
    for (auto& [r, c] : cnt) if (c == 2) pairs++;
    return pairs >= 2;
}
