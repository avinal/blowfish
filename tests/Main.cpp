/**
 * /mnt/z/my_git/blowfish/src/Main.cpp
 * @file Main.cpp
 * @author Avinal Kumar
 * @since March 06, 2021
 *
 * Test Program
 */

#include <iostream>

#include <blowfish/blowfish.h>

std::string from_uint(uint32_t sh) {
  std::string re("");
  for (int i = 0; i < 4; i++) {
    re += (unsigned char)(sh >> i * 8);
  }
  return re;
}

int main(int argc, char const *argv[]) {
  std::string key("test@pass47");
  std::string message("My name is Avinal and I am cute");
  std::string cipher("");
  int len = message.length();
  int j = sizeof(uint32_t);
  int rem =
      ((len > j * 2) ? (((len / j * 2) + 1) * j * 2 - len) : (j * 2 - len));
  message.append(rem, '\0');
  len = message.length();
  Blowfish blowfish(key);
  std::cout << "My message is: " << message << std::endl;
  uint32_t lm, rm;
  for (size_t i = 0; i < len; i += 8) {
    lm = 0;
    rm = 0;
    lm = *reinterpret_cast<unsigned int *>(
        const_cast<char *>(message.substr(i, j).c_str()));
    rm = *reinterpret_cast<unsigned int *>(
        const_cast<char *>(message.substr(i + 4, j).c_str()));
    blowfish.encrypt(lm, rm);
    cipher += from_uint(lm) + from_uint(rm);
  }
  std::cout << cipher << std::endl;
  std::string decipher("");
  len = cipher.length();
  std::cout << "length: " << len << std::endl;
  for (size_t i = 0; i < len; i += 8) {
    lm = 0;
    rm = 0;
    lm = *reinterpret_cast<unsigned int *>(
        const_cast<char *>(cipher.substr(i, 4).c_str()));
    rm = *reinterpret_cast<unsigned int *>(
        const_cast<char *>(cipher.substr(i + 4, 4).c_str()));
    blowfish.decrypt(lm, rm);
    decipher += from_uint(lm) + from_uint(rm);
  }

  std::cout << decipher << std::endl;
  if (message == decipher) {
    return 0;
  } else {
    return 1;
  }
}
