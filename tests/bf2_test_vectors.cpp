// SPDX-FileCopyrightText: 2025 Avinal Kumar avinal.xlvii@gmail.com
// SPDX-License-Identifier: MIT

#include "test_framework.h"
#include <blowfish/blowfish2.h>

// Known Answer Tests (KAT): Validate Blowfish output against fixed reference
// vectors to ensure algorithmic correctness.
TEST("Blowfish2 Known Answer Vector")
{
    Blowfish2 bf("abcdefghijklmnopqrstuvwxyz");

    uint64_t L = 0x424C4F5742463231ULL; // "BLOWBF21" (just a stable block)
    uint64_t R = 0x4649534832463231ULL; // "FISH2F21"

    uint64_t Lc = L, Rc = R;
    bf.encrypt(Lc, Rc);

    EXPECT_EQ(Lc, 0xF69E30BC3A4E8B0AULL);
    EXPECT_EQ(Rc, 0x31E5F507F5412293ULL);

    bf.decrypt(Lc, Rc);
    EXPECT_EQ(Lc, L);
    EXPECT_EQ(Rc, R);
}
