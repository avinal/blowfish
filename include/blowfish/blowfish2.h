// SPDX-FileCopyrightText: 2024 Avinal Kumar avinal.xlvii@gmail.com
// SPDX-License-Identifier: MIT

// Original Blowfish 2 Algorithm copyright:
// SPDX-FileCopyrightText: 2005 Alexander Pukall

#include <algorithm>
#include <array>
#include <cstdint>
#include <string>

#define MAXKEYBYTES 56 // 4224 bits max
#define N 64

#if !defined(BLOWFISH_BLOWFISH2_H_)
#define BLOWFISH_BLOWFISH2_H_

class Blowfish2 {
private:
  std::array<uint64_t, N + 2> PArray;
  std::array<std::array<uint64_t, 256>, 8> Sboxes;
  uint64_t F(uint64_t x);

public:
  Blowfish2() {}
  Blowfish2(std::string const &key);
  Blowfish2(Blowfish2 const &) = delete;

  void initialize(std::string const &key);

  void encrypt(uint64_t &xl, uint64_t &xr);
  void decrypt(uint64_t &xl, uint64_t &xr);
};

#endif // BLOWFISH_BLOWFISH2_H_
