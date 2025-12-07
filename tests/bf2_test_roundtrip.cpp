// SPDX-FileCopyrightText: 2025 Avinal Kumar avinal.xlvii@gmail.com
// SPDX-License-Identifier: MIT

#include "test_framework.h"
#include <blowfish/blowfish2.h>
#include <random>

// Ensure encrypt -> decrypt returns original plaintext
// for fixed and randomized test blocks.
TEST("Blowfish2 encrypt/decrypt roundtrip") {
  Blowfish2 bf("test-key-2");

  std::mt19937_64 rng(987654321ULL);

  for (int i = 0; i < 400; ++i) {
    uint64_t L = rng();
    uint64_t R = rng();

    uint64_t L2 = L, R2 = R;
    bf.encrypt(L2, R2);
    bf.decrypt(L2, R2);

    EXPECT_EQ(L, L2);
    EXPECT_EQ(R, R2);
  }
}
