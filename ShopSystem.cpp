#include "ShopSystem.h"
#include <iostream>

ShopSystem::ShopSystem(IScoringRule* rule) : scoringRule(rule) {
    buildCatalog();
}

void ShopSystem::buildCatalog() {
    // Setiap item memberi bonus chips atau mult untuk hand type tertentu
    // Bonus ini akan permanen selama satu run (persist di IScoringRule)
    catalog = {
        { "High Card  +10 Chips",  2, HandType::HIGH_CARD,       10, 0 },
        { "One Pair   +15 Chips",  3, HandType::ONE_PAIR,        15, 0 },
        { "One Pair   +2  Mult",   4, HandType::ONE_PAIR,         0, 2 },
        { "Two Pair   +20 Chips",  4, HandType::TWO_PAIR,        20, 0 },
        { "Two Pair   +2  Mult",   5, HandType::TWO_PAIR,         0, 2 },
        { "Three Kind +25 Chips",  5, HandType::THREE_OF_A_KIND, 25, 0 },
        { "Three Kind +3  Mult",   6, HandType::THREE_OF_A_KIND,  0, 3 },
        { "Straight   +3  Mult",   6, HandType::STRAIGHT,         0, 3 },
        { "Flush      +30 Chips",  6, HandType::FLUSH,            30, 0 },
        { "Flush      +3  Mult",   7, HandType::FLUSH,             0, 3 },
    };
}

void ShopSystem::runShop(int& money) {
    std::cout << "[SHOP] ============================\n";
    std::cout << "[SHOP] Money: $" << money << "\n";
    std::cout << "[SHOP] Available items:\n";

    // Tampilkan 3 item acak dari catalog (sederhana: ambil berdasarkan money)
    // Untuk base implementation: tampilkan item 0-2
    int shown = 3;
    for (int i = 0; i < shown && i < (int)catalog.size(); ++i) {
        displayItem(catalog[i], i + 1, money);
    }
    std::cout << "[SHOP] ----------------------------\n";

    // Beli item selama masih ada uang
    bool keepShopping = true;
    while (keepShopping) {
        std::cout << "[SHOP] Enter item number to buy (0 to leave): ";
        int choice;
        std::cin >> choice;

        if (choice == 0) {
            keepShopping = false;
        } else if (choice >= 1 && choice <= shown) {
            ShopItem& item = catalog[choice - 1];
            if (money >= item.cost) {
                money -= item.cost;
                applyItem(item);
                std::cout << "[SHOP] Bought: " << item.name
                          << " | Money left: $" << money << "\n";
            } else {
                std::cout << "[SHOP] Not enough money! Need $"
                          << item.cost << ", have $" << money << "\n";
            }
        } else {
            std::cout << "[SHOP] Invalid choice.\n";
        }

        // Refresh display
        if (keepShopping) {
            std::cout << "[SHOP] Money: $" << money << "\n";
            for (int i = 0; i < shown && i < (int)catalog.size(); ++i)
                displayItem(catalog[i], i + 1, money);
            std::cout << "[SHOP] ----------------------------\n";
        }
    }
    std::cout << "[SHOP] Left shop. Money: $" << money << "\n";
    std::cout << "[SHOP] ============================\n";
}

void ShopSystem::displayItem(const ShopItem& item, int idx, int money) const {
    std::string afford = (money >= item.cost) ? "" : " [can't afford]";
    std::cout << "[SHOP]   " << idx << ". " << item.name
              << " | Cost: $" << item.cost << afford << "\n";
}

void ShopSystem::applyItem(const ShopItem& item) {
    if (item.bonusChips > 0)
        scoringRule->addChipsBonus(item.targetHand, item.bonusChips);
    if (item.bonusMult > 0)
        scoringRule->addMultBonus(item.targetHand, item.bonusMult);
}
