// SPDX-FileCopyrightText: 2025 Avinal Kumar avinal.xlvii@gmail.com
// SPDX-License-Identifier: MIT

#include "test_framework.h"
#include <blowfish/blowfish.h>
#include <random>

// Ensure encrypt -> decrypt returns original plaintext
// for fixed and randomized test blocks.
TEST("Blowfish encrypt/decrypt roundtrip") {
  Blowfish bf("test-key");

  std::mt19937_64 rng(12345);

  for (int i = 0; i < 500; ++i) {
    uint64_t block = rng();
    uint32_t L = block >> 32;
    uint32_t R = block & 0xFFFFFFFFu;

    uint32_t L2 = L, R2 = R;
    bf.encrypt(L2, R2);
    bf.decrypt(L2, R2);

    EXPECT_EQ(L, L2);
    EXPECT_EQ(R, R2);
  }
}
