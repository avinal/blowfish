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

// Eric Young test vectors — official Blowfish KAT from Schneier's reference.
// Each entry: { key (hex bytes), plaintext_L, plaintext_R, cipher_L, cipher_R }
TEST("Blowfish Eric Young Test Vectors") {
  struct TestVector {
    const uint8_t key[8];
    size_t keylen;
    uint32_t plain_l, plain_r;
    uint32_t cipher_l, cipher_r;
  };

  // Subset of the published Eric Young / SSLeay test vectors
  static const TestVector vectors[] = {
      {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
       8, 0x00000000, 0x00000000, 0x4EF99745, 0x6198DD78},
      {{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
       8, 0xFFFFFFFF, 0xFFFFFFFF, 0x51866FD5, 0xB85ECB8A},
      {{0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
       8, 0x10000000, 0x00000001, 0x7D856F9A, 0x613063F2},
      {{0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF},
       8, 0x11111111, 0x11111111, 0x61F9C380, 0x2281B096},
      {{0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10},
       8, 0x01234567, 0x89ABCDEF, 0x0ACEAB0F, 0xC6A0A28D},
  };

  for (const auto &v : vectors) {
    Blowfish bf;
    bf.initialize(v.key, v.keylen);

    uint32_t L = v.plain_l, R = v.plain_r;
    bf.encrypt(L, R);
    EXPECT_EQ(L, v.cipher_l);
    EXPECT_EQ(R, v.cipher_r);

    bf.decrypt(L, R);
    EXPECT_EQ(L, v.plain_l);
    EXPECT_EQ(R, v.plain_r);
  }
}
