// SPDX-FileCopyrightText: 2024 Avinal Kumar avinal.xlvii@gmail.com
// SPDX-License-Identifier: MIT

// Original Blowfish Algorithm copyright:
// SPDX-FileCopyrightText: 1997 Paul Kocher

#pragma once
#include <array>
#include <cstdint>
#include <string>

static constexpr uint32_t BF_NUM_ROUNDS = 16;
static constexpr uint32_t BF_MAX_KEYBYTES = 56;

#if !defined(BLOWFISH_BLOWFISH_H_)
#define BLOWFISH_BLOWFISH_H_

class Blowfish {
private:
  std::array<uint32_t, BF_NUM_ROUNDS + 2> PArray{};
  std::array<std::array<uint32_t, 256>, 4> Sboxes{};
  uint32_t F(uint32_t x) const noexcept;

public:
  Blowfish() = default;
  explicit Blowfish(std::string const &key);
  Blowfish(Blowfish const &) = delete;

  void initialize(const uint8_t *key, size_t keylen);
  void initialize(const std::string &key);

  void encrypt(uint32_t &xl, uint32_t &xr) noexcept;
  void decrypt(uint32_t &xl, uint32_t &xr) noexcept;
  ~Blowfish();
};

#endif // BLOWFISH_BLOWFISH_H_
