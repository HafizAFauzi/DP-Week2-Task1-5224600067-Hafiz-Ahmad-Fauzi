#pragma once
#include "IScoringRule.h"
#include <vector>
#include <string>

// Item yang dijual di shop: bonus chips atau mult untuk hand type tertentu
struct ShopItem {
    std::string name;
    int         cost;
    HandType    targetHand;   // hand type yang kena bonus
    int         bonusChips;   // 0 jika bukan chips bonus
    int         bonusMult;    // 0 jika bukan mult bonus
};

// ShopSystem tidak punya interface karena behavior-nya fixed.
// Tapi ia butuh referensi ke IScoringRule untuk langsung inject bonus
// ketika player membeli item.
class ShopSystem {
private:
    std::vector<ShopItem> catalog;
    IScoringRule*         scoringRule;  // injected — bukan dimiliki ShopSystem

    void buildCatalog();

public:
    explicit ShopSystem(IScoringRule* rule);

    // Jalankan shop phase: tampilkan item, tanya beli/skip, kurangi money
    // return: jumlah uang yang dibelanjakan (agar RunSession bisa log)
    void runShop(int& money);

private:
    void displayItem(const ShopItem& item, int idx, int money) const;
    void applyItem  (const ShopItem& item);
};
