/**
 * @file blowfish.hpp
 * @author Avinal Kumar
 * @since February 15, 2021
 *
 * Blowfish Algorithm Header File
 */

#define MAXKEYBYTES 56 // 448 bits max

#define DWORD unsigned long
#define WORD unsigned int
#define BYTE unsigned char

#if !defined(BLOWFISH_HPP)
#define BLOWFISH_HPP

#include <algorithm>
#include <array>

class blowfish {
private:
  std::array<DWORD, 16 + 2> PArray;
  std::array<std::array<DWORD, 256>, 4> Sboxes;
  DWORD F(DWORD x);

public:
  blowfish(BYTE *key, WORD keylength);
  void encrypt(DWORD *xl, DWORD *xr);
  void decrypt(DWORD *xl, DWORD *xr);
};

#endif // BLOWFISH_HPP
