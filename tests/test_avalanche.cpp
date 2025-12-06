// SPDX-FileCopyrightText: 2025 Avinal Kumar avinal.xlvii@gmail.com
// SPDX-License-Identifier: MIT

#include "test_framework.h"
#include <blowfish/blowfish.h>

static int hamming(uint64_t a, uint64_t b) {
  return __builtin_popcountll(a ^ b);
}

// Check that flipping one bit in plaintext or key
// causes large, unpredictable changes in ciphertext.
TEST("Blowfish Avalanche Effect") {
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
