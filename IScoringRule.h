#pragma once
#include "TurnInput.h"
#include "HandEvaluator.h"
#include <map>
#include <string>

// Interface scoring rule
// ShopSystem bisa langsung panggil addChipsBonus / addMultBonus
// untuk memodifikasi state bonus per hand type
class IScoringRule {
public:
    virtual ~IScoringRule() = default;

    // Hitung final score dari chosen hand (chips * mult + bonus)
    virtual int computeScore(const TurnInput& input) = 0;

    // Dipanggil ShopSystem untuk memberi bonus ke hand type tertentu
    virtual void addChipsBonus(HandType type, int chips) = 0;
    virtual void addMultBonus (HandType type, int mult)  = 0;

    // Untuk display di shop: lihat bonus yang sudah aktif
    virtual int getChipsBonus(HandType type) const = 0;
    virtual int getMultBonus (HandType type) const = 0;
};
