// SPDX-FileCopyrightText: 2025 Avinal Kumar avinal.xlvii@gmail.com
// SPDX-License-Identifier: MIT

#include "test_framework.h"
#include <blowfish/blowfish.h>

// Known Answer Tests (KAT): Validate Blowfish output against fixed reference
// vectors to ensure algorithmic correctness.
TEST("Blowfish Known Test Vectors") {
  Blowfish bf("abcdefghijklmnopqrstuvwxyz");

  uint32_t L = 0x424C4F57; // "BLOW"
  uint32_t R = 0x46495348; // "FISH"

  bf.encrypt(L, R);
  EXPECT_EQ(L, 0x324ED0FE);
  EXPECT_EQ(R, 0xF413A203);

  bf.decrypt(L, R);
  EXPECT_EQ(L, 0x424C4F57);
  EXPECT_EQ(R, 0x46495348);
}
