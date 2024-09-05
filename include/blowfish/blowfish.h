// SPDX-FileCopyrightText: 2024 Avinal Kumar avinal.xlvii@gmail.com
// SPDX-License-Identifier: MIT

// Original Blowfish Algorithm copyright:
// SPDX-FileCopyrightText: 1997 Paul Kocher

#include <algorithm>
#include <array>
#include <cstdint>
#include <string>

#define MAXKEYBYTES 56 // 448 bits max
#define N 16

#if !defined(BLOWFISH_BLOWFISH_H_)
#define BLOWFISH_BLOWFISH_H_

class Blowfish {
private:
  std::array<uint32_t, N + 2> PArray;
  std::array<std::array<uint32_t, 256>, 4> Sboxes;
  uint32_t F(uint32_t x);

public:
  Blowfish() {}
  Blowfish(std::string const &key);
  Blowfish(Blowfish const &) = delete;

  void initialize(std::string const &key);

  void encrypt(uint32_t &xl, uint32_t &xr);
  void decrypt(uint32_t &xl, uint32_t &xr);
};

#endif // BLOWFISH_BLOWFISH_H_
