// SPDX-FileCopyrightText: 2025 Avinal Kumar avinal.xlvii@gmail.com
// SPDX-License-Identifier: MIT

#include "test_framework.h"
#include <blowfish/blowfish.h>
#include <stdexcept>

// Test edge-case blocks, key lengths, symmetry,
// and consistency across instances.

TEST("Blowfish varying key lengths") {
  uint32_t L = 0xDEADBEEF, R = 0xCAFEBABE;

  // 1-byte key (minimum)
  {
    Blowfish bf;
    bf.initialize(reinterpret_cast<const uint8_t *>("A"), 1);
    uint32_t l = L, r = R;
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
    Blowfish bf;
    bf.initialize(maxkey, 56);
    uint32_t l = L, r = R;
    bf.encrypt(l, r);
    EXPECT_TRUE(l != L || r != R);
    bf.decrypt(l, r);
    EXPECT_EQ(l, L);
    EXPECT_EQ(r, R);
  }

  // Different key lengths produce different ciphertext
  {
    Blowfish bf4, bf8;
    bf4.initialize(reinterpret_cast<const uint8_t *>("ABCD"), 4);
    bf8.initialize(reinterpret_cast<const uint8_t *>("ABCDEFGH"), 8);
    uint32_t l4 = L, r4 = R, l8 = L, r8 = R;
    bf4.encrypt(l4, r4);
    bf8.encrypt(l8, r8);
    EXPECT_TRUE(l4 != l8 || r4 != r8);
  }
}

TEST("Blowfish rejects invalid keys") {
  bool caught = false;

  // Empty key
  try {
    Blowfish bf("");
    (void)bf;
  } catch (const std::invalid_argument &) {
    caught = true;
  }
  EXPECT_TRUE(caught);

  // Over-length key (57 bytes)
  caught = false;
  try {
    Blowfish bf;
    uint8_t bigkey[57] = {};
    bf.initialize(bigkey, 57);
  } catch (const std::invalid_argument &) {
    caught = true;
  }
  EXPECT_TRUE(caught);

  // Null pointer
  caught = false;
  try {
    Blowfish bf;
    bf.initialize(nullptr, 8);
  } catch (const std::invalid_argument &) {
    caught = true;
  }
  EXPECT_TRUE(caught);
}

TEST("Blowfish edge-case blocks") {
  Blowfish bf("edge-test");

  // All-zero block
  {
    uint32_t L = 0, R = 0;
    uint32_t L2 = L, R2 = R;
    bf.encrypt(L2, R2);
    EXPECT_TRUE(L2 != 0 || R2 != 0);
    bf.decrypt(L2, R2);
    EXPECT_EQ(L2, L);
    EXPECT_EQ(R2, R);
  }

  // All-ones block
  {
    uint32_t L = 0xFFFFFFFF, R = 0xFFFFFFFF;
    uint32_t L2 = L, R2 = R;
    bf.encrypt(L2, R2);
    EXPECT_TRUE(L2 != L || R2 != R);
    bf.decrypt(L2, R2);
    EXPECT_EQ(L2, L);
    EXPECT_EQ(R2, R);
  }

  // L == R
  {
    uint32_t L = 0x12345678, R = 0x12345678;
    uint32_t L2 = L, R2 = R;
    bf.encrypt(L2, R2);
    bf.decrypt(L2, R2);
    EXPECT_EQ(L2, L);
    EXPECT_EQ(R2, R);
  }
}

TEST("Blowfish cross-instance consistency") {
  Blowfish bf1("same-key");
  Blowfish bf2("same-key");

  uint32_t L = 0xAAAAAAAA, R = 0x55555555;
  uint32_t L1 = L, R1 = R, L2 = L, R2 = R;
  bf1.encrypt(L1, R1);
  bf2.encrypt(L2, R2);
  EXPECT_EQ(L1, L2);
  EXPECT_EQ(R1, R2);
}

TEST("Blowfish re-initialization") {
  Blowfish bf("key-one");

  uint32_t L = 0x11111111, R = 0x22222222;
  uint32_t L1 = L, R1 = R;
  bf.encrypt(L1, R1);

  bf.initialize("key-two");
  uint32_t L2 = L, R2 = R;
  bf.encrypt(L2, R2);

  // Different keys must produce different ciphertext
  EXPECT_TRUE(L1 != L2 || R1 != R2);

  // Roundtrip still works after re-init
  bf.decrypt(L2, R2);
  EXPECT_EQ(L2, L);
  EXPECT_EQ(R2, R);
}

TEST("Blowfish no fixed points") {
  Blowfish bf("key1");

  for (uint32_t i = 1; i < 20; ++i) {
    uint32_t L = i * 0x12345678u;
    uint32_t R = i * 0x9ABCDEF0u;

    uint32_t L2 = L, R2 = R;
    bf.encrypt(L2, R2);

    EXPECT_TRUE(!(L2 == L && R2 == R));
  }
}

TEST("Blowfish no short encryption cycles") {
  Blowfish bf("another-key");

  for (uint32_t seed = 1; seed < 10; ++seed) {
    uint32_t L = seed * 0x11111111u;
    uint32_t R = seed * 0xAAAAAAAAu;

    uint32_t a = L, b = R;

    for (int i = 0; i < 10; ++i) {
      bf.encrypt(a, b);
      EXPECT_TRUE(!(a == L && b == R));
    }
  }
}
