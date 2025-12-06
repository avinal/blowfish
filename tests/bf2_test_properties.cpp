// SPDX-FileCopyrightText: 2025 Avinal Kumar avinal.xlvii@gmail.com
// SPDX-License-Identifier: MIT

#include "test_framework.h"
#include <blowfish/blowfish2.h>

TEST("Blowfish2 no fixed points") {
  Blowfish2 bf("fixed-point-check");

  for (uint64_t i = 1; i < 50; ++i) {
    uint64_t L = i * 0x123456789ABCDEFULL;
    uint64_t R = i * 0xFEDCBA987654321ULL;

    uint64_t L2 = L, R2 = R;
    bf.encrypt(L2, R2);

    EXPECT_TRUE(!(L == L2 && R == R2));
  }
}

TEST("Blowfish2 no short cycles") {
  Blowfish2 bf("cycle-check");

  for (uint64_t seed = 1; seed <= 5; ++seed) {
    uint64_t L0 = seed;
    uint64_t R0 = seed * 12345;

    uint64_t L = L0, R = R0;

    for (int iter = 0; iter < 12; ++iter) {
      bf.encrypt(L, R);
      EXPECT_TRUE(!(L == L0 && R == R0));
    }
  }
}
