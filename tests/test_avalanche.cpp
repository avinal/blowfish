// SPDX-FileCopyrightText: 2025 Avinal Kumar avinal.xlvii@gmail.com
// SPDX-License-Identifier: MIT

#include "test_framework.h"
#include <blowfish/blowfish.h>

static int hamming(uint64_t a, uint64_t b) {
  return __builtin_popcountll(a ^ b);
}

// Check that flipping one bit in plaintext
// causes large, unpredictable changes in ciphertext.
TEST("Blowfish Plaintext Avalanche Effect") {
  Blowfish bf("key");

  uint32_t L = 0x11223344, R = 0x55667788;
  uint32_t Lc = L, Rc = R;

  bf.encrypt(Lc, Rc);
  uint64_t C1 = (uint64_t(Lc) << 32) | Rc;

  for (int bit = 0; bit < 32; ++bit) {
    uint32_t Lflip = L ^ (1u << bit);
    uint32_t Rflip = R;

    uint32_t L2 = Lflip, R2 = Rflip;
    bf.encrypt(L2, R2);

    uint64_t C2 = (uint64_t(L2) << 32) | R2;

    int hd = hamming(C1, C2);
    EXPECT_TRUE(hd > 20); // Strong avalanche threshold
  }
}

// Check that flipping one bit in the key
// causes large, unpredictable changes in ciphertext.
TEST("Blowfish Key Avalanche Effect") {
  uint8_t basekey[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
  uint32_t L = 0x11223344, R = 0x55667788;

  Blowfish bf_base;
  bf_base.initialize(basekey, 8);
  uint32_t Lc = L, Rc = R;
  bf_base.encrypt(Lc, Rc);
  uint64_t C1 = (uint64_t(Lc) << 32) | Rc;

  for (int byte = 0; byte < 8; ++byte) {
    for (int bit = 0; bit < 8; ++bit) {
      uint8_t flipped[8];
      std::copy(basekey, basekey + 8, flipped);
      flipped[byte] ^= (1u << bit);

      Blowfish bf_flip;
      bf_flip.initialize(flipped, 8);

      uint32_t L2 = L, R2 = R;
      bf_flip.encrypt(L2, R2);
      uint64_t C2 = (uint64_t(L2) << 32) | R2;

      int hd = hamming(C1, C2);
      EXPECT_TRUE(hd > 20);
    }
  }
}
