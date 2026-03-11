# Task 1 — Balatro-Like Run (Base Implementation)
# A. Game Structure Requirement

## How to Build & Run

```bash
g++ *.cpp 
  -o balatro

./balatro
```



## File Structure

```
Task1/
├── main.cpp                    # Entry point, dependency injection only
│
├── Card.h / Card.cpp           # Card struct: Suit, Rank, toString
├── Deck.h / Deck.cpp           # Full 52-card deck with shuffle/draw
├── TurnInput.h                 # Data container flowing between phases
│
├── HandEvaluator.h / .cpp      # Poker hand detection → Chips × Mult
│
├── IHandGenerator.h            # Interface: generate dealt cards from deck
├── IHandChooser.h              # Interface: select 5 from 7 dealt cards
├── IScoringRule.h              # Interface: compute score + accept shop bonuses
│
├── StandardHandGenerator.h/.cpp  # Concrete: uniform random deal
├── PlayerHandChooser.h/.cpp      # Concrete: auto-selects best 5-card combo
├── StandardScoringRule.h/.cpp    # Concrete: (chips + bonus) × (mult + bonus)
│
├── ShopSystem.h / ShopSystem.cpp # Shop phase — injects bonuses into IScoringRule
├── RunSession.h / RunSession.cpp # INVARIANT game loop
└── README.md
```



## Scoring System (Chips × Mult)

Setiap hand type punya base Chips dan base Mult:

| Hand Type       | Base Chips | Base Mult | Base Score |
|-----------------|------------|-----------|------------|
| High Card       | 5          | ×1        | 5          |
| One Pair        | 10         | ×2        | 20         |
| Two Pair        | 20         | ×2        | 40         |
| Three of a Kind | 30         | ×3        | 90         |
| Straight        | 30         | ×4        | 120        |
| Flush           | 35         | ×4        | 140        |
| Full House      | 40         | ×4        | 160        |
| Four of a Kind  | 60         | ×7        | 420        |
| Straight Flush  | 100        | ×8        | 800        |
| Royal Flush     | 100        | ×8        | 800        |

**Final Score = (baseChips + bonusChips) × (baseMult + bonusMult)**

Bonus chips/mult dibeli dari shop dan persist selama satu run.



## Shop System

Shop muncul setiap round setelah Count Cash.
Player bisa beli item yang menambah Chips atau Mult untuk hand type tertentu.
Bonus langsung disimpan ke `IScoringRule` dan aktif mulai round berikutnya.

Contoh item:
- `One Pair +15 Chips` → $3
- `One Pair +2 Mult`   → $4
- `Flush +30 Chips`    → $6

## Architecture

### Invariant Phase Order (RunSession)

```
untuk setiap round:
  1. Generate Hand   ← IHandGenerator
  2. Choose Hand     ← IHandChooser
  3. Compute Score   ← IScoringRule
  4. Check Win/Lose  ← fixed logic
  5. Count Cash      ← fixed logic
  6. Shop Phase      ← ShopSystem (modifies IScoringRule)
```



## B. Required Modifications

### Modification 1 — RandomInputGenerator

Dibuat class baru `RandomInputGenerator` yang menggantikan `StandardHandGenerator`.

**Perbedaan behavior:**
- `StandardHandGenerator` → pure uniform random, semua 52 kartu peluang sama
- `RandomInputGenerator` → bias straight: pilih anchor rank acak (2–10), lalu deal 5 kartu dari window rank `[anchor, anchor+4]` + 2 kartu benar-benar acak dari sisa deck

**Bukti invariant terjaga:** `RunSession` tidak menyebut `RandomInputGenerator` atau `StandardHandGenerator` sama sekali. Satu-satunya perubahan adalah di `main.cpp`, baris:
```cpp
// Sebelum:  StandardHandGenerator generator;
RandomInputGenerator generator;   // ganti satu baris ini
```

### Modification 2 — FlatBonusRewardRule

Dibuat interface `IRewardRule` dan implementasi `FlatBonusRewardRule`.

**Formula baru:** `reward = score + 2` (menang) / `$1` consolation (kalah)

Reward tidak lagi sama dengan base score, dan `RunSession` tidak tahu formulanya — ia hanya memanggil `rewardRule->computeReward(score, round, win)`.

**Bukti invariant terjaga:** Tidak ada formula `score + 2` di dalam `RunSession`. Untuk mengganti reward formula lagi di masa depan, cukup buat implementasi baru dari `IRewardRule` dan inject di `main.cpp`.



`RunSession` hanya orchestrate — tidak ada satu pun game logic di dalamnya.

### Kenapa .h dan .cpp dipisah?

- `.h` = deklarasi (apa yang ada: nama class, signature fungsi)
- `.cpp` = definisi (bagaimana implementasinya)

Pemisahan ini penting untuk project yang akan berkembang karena:
1. Compilation unit terpisah — hanya `.cpp` yang berubah yang perlu di-recompile
2. Header bisa di-include di banyak tempat tanpa duplicate definition
3. Lebih mudah dibaca: `.h` cukup untuk tahu kontrak sebuah class

---

## Reflection

### 1. Apa invariant structure dalam program ini?

Invariant adalah **urutan 6 fase** di dalam `RunSession::run()`. Fase Generate → Choose → Score → CheckWin → CountCash → Shop harus selalu berjalan dalam urutan itu setiap round tanpa pengecualian. Urutan ini adalah kontrak fundamental game: tidak mungkin scoring dilakukan sebelum hand dipilih, dan shop tidak mungkin terjadi sebelum cash dihitung.

### 2. Bagian mana yang mutable?

Bagian mutable adalah **implementasi konkret** yang di-inject ke `RunSession`:
- `IHandGenerator` → bisa diganti untuk distribusi deck berbeda (flush-heavy, boss-rigged, dll.)
- `IHandChooser` → bisa diganti untuk mekanik Boss yang lock 1 kartu secara acak
- `IScoringRule` → bisa diganti untuk menambah Joker, modifier, atau rule baru

State bonus di `StandardScoringRule` (dari pembelian shop) juga mutable dan terakumulasi sepanjang run.

### 3. Kenapa RunSession tidak berubah saat InputGenerator diganti?

Karena `RunSession` hanya memanggil `generator->generateHand(deck, input)` — ia berkomunikasi dengan **interface**, bukan implementasi spesifik. Tidak peduli apakah generatornya `StandardHandGenerator`, `RandomInputGenerator`, atau `FlushBiasedGenerator`. Satu-satunya yang berubah ketika ganti generator adalah baris injeksi di `main.cpp`.

### 4. Apa yang terjadi jika scoring logic ada di RunSession?

`RunSession` menjadi rapuh. Setiap kali ada Joker baru, modifier berubah, atau bonus dari shop perlu ditambahkan, `RunSession` harus dimodifikasi — berarti kita menyentuh invariant hanya karena behavior mutable berubah. Ini melanggar Single Responsibility Principle dan membuat sistem sulit di-extend, di-test, dan di-maintain.
