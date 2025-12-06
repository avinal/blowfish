// SPDX-FileCopyrightText: 2025 Avinal Kumar avinal.xlvii@gmail.com
// SPDX-License-Identifier: MIT

#include "test_framework.h"
#include <blowfish/blowfish.h>

// Test edge-case blocks, key lengths, symmetry,
// and consistency across instances.

TEST("Blowfish no fixed points") {
  Blowfish bf("key1");

  for (uint64_t x = 1; x < 20; ++x) {
    uint32_t L = x >> 32;
    uint32_t R = x & 0xFFFFFFFFu;

    uint32_t L2 = L, R2 = R;
    bf.encrypt(L2, R2);

    EXPECT_TRUE(!(L2 == L && R2 == R));
  }
}

TEST("Blowfish no short encryption cycles") {
  Blowfish bf("another-key");

  for (uint64_t seed = 1; seed < 10; ++seed) {
    uint32_t L = seed >> 32;
    uint32_t R = seed & 0xFFFFFFFFu;

    uint32_t a = L, b = R;

    for (int i = 0; i < 10; ++i) {
      bf.encrypt(a, b);
      EXPECT_TRUE(!(a == L && b == R));
    }
  }
}
