// SPDX-FileCopyrightText: 2024 Avinal Kumar avinal.xlvii@gmail.com
// SPDX-License-Identifier: MIT

// Original Blowfish 2 Algorithm copyright:
// SPDX-FileCopyrightText: 2005 Alexander Pukall

#pragma once
#include <array>
#include <cstdint>
#include <string>

static constexpr uint64_t BF2_NUM_ROUNDS = 64;
static constexpr uint64_t BF2_MAX_KEYBYTES = 56;

#if !defined(BLOWFISH_BLOWFISH2_H_)
#define BLOWFISH_BLOWFISH2_H_

class Blowfish2 {
private:
  std::array<uint64_t, BF2_NUM_ROUNDS + 2> PArray{};
  std::array<std::array<uint64_t, 256>, 8> Sboxes{};
  uint64_t F(uint64_t x) const noexcept;

public:
  Blowfish2() = default;
  explicit Blowfish2(const std::string &key) { initialize(key); }

  Blowfish2(const Blowfish2 &) = delete;
  Blowfish2 &operator=(const Blowfish2 &) = delete;

  void initialize(std::string const &key);
  void initialize(const uint8_t *key, size_t keylen);

  void encrypt(uint64_t &xl, uint64_t &xr) noexcept;
  void decrypt(uint64_t &xl, uint64_t &xr) noexcept;
};

#endif // BLOWFISH_BLOWFISH2_H_
