/*
 * @file blowfish.hpp
 * @author Avinal Kumar
 * @since February 15, 2021
 *
 * Blowfish Algorithm Header File
 */

#include <algorithm>
#include <array>
#include <string>

#define MAXKEYBYTES 56 // 448 bits max
#define N 16

#define BYTE unsigned char
#define DWORD unsigned long
#define WORD unsigned int

#if !defined(BLOWFISH_BLOWFISH_H_)
#define BLOWFISH_BLOWFISH_H_

class Blowfish {
private:
  std::array<DWORD, N + 2> PArray;
  std::array<std::array<DWORD, 256>, 4> Sboxes;
  DWORD F(DWORD x);

public:
  Blowfish(std::string const &key);
  void encrypt(DWORD &xl, DWORD &xr);
  void decrypt(DWORD &xl, DWORD &xr);
};

#endif // BLOWFISH_BLOWFISH_H_
