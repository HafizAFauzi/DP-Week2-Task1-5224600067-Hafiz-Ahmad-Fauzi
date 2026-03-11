#pragma once

// Interface untuk menghitung reward (cash gain) dari base score.
// Dipisah dari IScoringRule karena reward adalah fase tersendiri
// dalam game loop — sesuai dokumen: fase 3 (Compute Score) dan
// fase 5 (Count Cash) adalah dua hal yang berbeda.
//
// Mutable: bisa diganti formulanya tanpa menyentuh RunSession.
class IRewardRule {
public:
    virtual ~IRewardRule() = default;

    // Hitung cash yang didapat dari score pada round tertentu
    // win = false berarti player kalah round ini
    virtual int computeReward(int score, int round, bool win) = 0;
};