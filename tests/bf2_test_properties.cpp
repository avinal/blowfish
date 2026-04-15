// SPDX-FileCopyrightText: 2025 Avinal Kumar avinal.xlvii@gmail.com
// SPDX-License-Identifier: MIT

#include "test_framework.h"
#include <blowfish/blowfish2.h>
#include <stdexcept>

TEST("Blowfish2 varying key lengths") {
  uint64_t L = 0xDEADBEEFCAFEBABEULL, R = 0x0123456789ABCDEFULL;

  // 1-byte key (minimum)
  {
    Blowfish2 bf;
    bf.initialize(reinterpret_cast<const uint8_t *>("A"), 1);
    uint64_t l = L, r = R;
    bf.encrypt(l, r);
    EXPECT_TRUE(l != L || r != R);
    bf.decrypt(l, r);
    EXPECT_EQ(l, L);
    EXPECT_EQ(r, R);
  }

  // 56-byte key (maximum)
  {
    const uint8_t maxkey[56] = {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
        0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14,
        0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E,
        0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
        0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32,
        0x33, 0x34, 0x35, 0x36, 0x37, 0x38};
    Blowfish2 bf;
    bf.initialize(maxkey, 56);
    uint64_t l = L, r = R;
    bf.encrypt(l, r);
    EXPECT_TRUE(l != L || r != R);
    bf.decrypt(l, r);
    EXPECT_EQ(l, L);
    EXPECT_EQ(r, R);
  }

  // Different key lengths produce different ciphertext
  {
    Blowfish2 bf4, bf8;
    bf4.initialize(reinterpret_cast<const uint8_t *>("ABCD"), 4);
    bf8.initialize(reinterpret_cast<const uint8_t *>("ABCDEFGH"), 8);
    uint64_t l4 = L, r4 = R, l8 = L, r8 = R;
    bf4.encrypt(l4, r4);
    bf8.encrypt(l8, r8);
    EXPECT_TRUE(l4 != l8 || r4 != r8);
  }
}

TEST("Blowfish2 rejects invalid keys") {
  bool caught = false;

  // Empty key
  try {
    Blowfish2 bf("");
    (void)bf;
  } catch (const std::invalid_argument &) {
    caught = true;
  }
  EXPECT_TRUE(caught);

  // Over-length key (57 bytes)
  caught = false;
  try {
    Blowfish2 bf;
    uint8_t bigkey[57] = {};
    bf.initialize(bigkey, 57);
  } catch (const std::invalid_argument &) {
    caught = true;
  }
  EXPECT_TRUE(caught);

  // Null pointer
  caught = false;
  try {
    Blowfish2 bf;
    bf.initialize(nullptr, 8);
  } catch (const std::invalid_argument &) {
    caught = true;
  }
  EXPECT_TRUE(caught);
}

TEST("Blowfish2 edge-case blocks") {
  Blowfish2 bf("edge-test-2");

  // All-zero block
  {
    uint64_t L = 0, R = 0;
    uint64_t L2 = L, R2 = R;
    bf.encrypt(L2, R2);
    EXPECT_TRUE(L2 != 0 || R2 != 0);
    bf.decrypt(L2, R2);
    EXPECT_EQ(L2, L);
    EXPECT_EQ(R2, R);
  }

  // All-ones block
  {
    uint64_t L = 0xFFFFFFFFFFFFFFFFULL, R = 0xFFFFFFFFFFFFFFFFULL;
    uint64_t L2 = L, R2 = R;
    bf.encrypt(L2, R2);
    EXPECT_TRUE(L2 != L || R2 != R);
    bf.decrypt(L2, R2);
    EXPECT_EQ(L2, L);
    EXPECT_EQ(R2, R);
  }
}

TEST("Blowfish2 cross-instance consistency") {
  Blowfish2 bf1("same-key-2");
  Blowfish2 bf2("same-key-2");

  uint64_t L = 0xAAAAAAAAAAAAAAAAULL, R = 0x5555555555555555ULL;
  uint64_t L1 = L, R1 = R, L2 = L, R2 = R;
  bf1.encrypt(L1, R1);
  bf2.encrypt(L2, R2);
  EXPECT_EQ(L1, L2);
  EXPECT_EQ(R1, R2);
}

TEST("Blowfish2 re-initialization") {
  Blowfish2 bf("key-one");

  uint64_t L = 0x1111111111111111ULL, R = 0x2222222222222222ULL;
  uint64_t L1 = L, R1 = R;
  bf.encrypt(L1, R1);

  bf.initialize("key-two");
  uint64_t L2 = L, R2 = R;
  bf.encrypt(L2, R2);

  EXPECT_TRUE(L1 != L2 || R1 != R2);

  bf.decrypt(L2, R2);
  EXPECT_EQ(L2, L);
  EXPECT_EQ(R2, R);
}

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
