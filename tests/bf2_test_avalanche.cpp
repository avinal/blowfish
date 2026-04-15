// SPDX-FileCopyrightText: 2025 Avinal Kumar avinal.xlvii@gmail.com
// SPDX-License-Identifier: MIT

#include "test_framework.h"
#include <blowfish/blowfish2.h>

static int hamming128(uint64_t a1, uint64_t b1, uint64_t a2, uint64_t b2) {
  return __builtin_popcountll(a1 ^ a2) + __builtin_popcountll(b1 ^ b2);
}

// Check that flipping one bit in plaintext
// causes large, unpredictable changes in ciphertext.
TEST("Blowfish2 Plaintext Avalanche Effect") {
  Blowfish2 bf("key-for-avalanche");

  uint64_t L = 0x1122334455667788ULL;
  uint64_t R = 0x99AABBCCDDEEFF00ULL;

  uint64_t L0 = L, R0 = R;
  bf.encrypt(L0, R0);

  for (int bit = 0; bit < 64; ++bit) {
    uint64_t Lf = L ^ (1ULL << bit);
    uint64_t Rf = R;

    uint64_t L1 = Lf, R1 = Rf;
    bf.encrypt(L1, R1);

    int hd = hamming128(L0, R0, L1, R1);

    // Expect large hamming distance: ideally >40 for Blowfish2
    EXPECT_TRUE(hd > 40);
  }
}

// Check that flipping one bit in the key
// causes large, unpredictable changes in ciphertext.
TEST("Blowfish2 Key Avalanche Effect") {
  uint8_t basekey[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
  uint64_t L = 0x1122334455667788ULL;
  uint64_t R = 0x99AABBCCDDEEFF00ULL;

  Blowfish2 bf_base;
  bf_base.initialize(basekey, 8);
  uint64_t L0 = L, R0 = R;
  bf_base.encrypt(L0, R0);

  for (int byte = 0; byte < 8; ++byte) {
    for (int bit = 0; bit < 8; ++bit) {
      uint8_t flipped[8];
      std::copy(basekey, basekey + 8, flipped);
      flipped[byte] ^= (1u << bit);

      Blowfish2 bf_flip;
      bf_flip.initialize(flipped, 8);

      uint64_t L1 = L, R1 = R;
      bf_flip.encrypt(L1, R1);

      int hd = hamming128(L0, R0, L1, R1);
      EXPECT_TRUE(hd > 40);
    }
  }
}
