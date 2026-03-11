#pragma once
#include "IHandGenerator.h"

// Modification 1: RandomInputGenerator
// Berbeda dari StandardHandGenerator yang pure random,
// generator ini bias ke straight dengan cara:
// 1. Pilih rank anchor secara acak (2–10)
// 2. Ambil 5 kartu dengan rank anchor s/d anchor+4 dari suits acak
// 3. Tambah 2 kartu benar-benar acak dari sisa deck
// Hasilnya: dealt hand lebih sering mengandung bahan straight,
// tapi tidak guarantee karena suit & urutan tetap acak.
//
// RunSession TIDAK diubah — hanya injeksi di main.cpp yang diganti.
class RandomInputGenerator : public IHandGenerator {
public:
    void generateHand(Deck& deck, TurnInput& input) override;
};