#include <cstdint>
#include <iostream>

#include <blowfish/blowfish2.h>
#include <ostream>

std::string from_uint(uint64_t sh) {
  std::string re("");
  for (int i = 0; i < 8; i++) {
    re += (unsigned char)(sh >> i * 8);
  }
  return re;
}

uint64_t to_uint(std::string &s, size_t index, size_t size) {
  return *reinterpret_cast<uint64_t *>(
      const_cast<char *>(s.substr(index, size).c_str()));
}

int main(int argc, char const *argv[]) {
  std::string key("test@pass47");
  std::string message("My name is Avinal and I am cute and smart");
  std::string cipher("");
  int len = message.length();
  int J = sizeof(uint64_t);
  int rem =
      ((len > J * 2) ? (((len / J * 2) + 1) * J * 2 - len) : (J * 2 - len));
  message.append(rem, '\0');
  len = message.length();

  Blowfish2 blowfish(key);

  std::cout << "My message is: " << message << J << std::endl;
  uint64_t L = 0, R = 0;
  for (size_t i = 0; i < len; i += 16) {
    L = to_uint(message, i, J);
    R = to_uint(message, i + J, J);
    blowfish.encrypt(L, R);
    cipher += from_uint(L) + from_uint(R);
  }
  std::cout << "Cipher: " << cipher << std::endl;

  std::string decipher("");
  len = cipher.length();
  std::cout << "length: " << len << std::endl;
  for (size_t i = 0; i < len; i += 16) {
    L = to_uint(cipher, i, J);
    R = to_uint(cipher, i + J, J);
    blowfish.decrypt(L, R);
    decipher += from_uint(L) + from_uint(R);
  }
  if (message == decipher) {
    std::cout << "Test OK." << std::endl;
  } else {
    std::cout << "Test failed." << std::endl;
  }
  // C Blowfish 2 tests

  L = 0x0000000000000001, R = 0x0000000000000002;

  blowfish.initialize("TESTKEY");
  blowfish.encrypt(L, R);
  if (L == 0x7B2B9DE71D1B1C62 && R == 0x91C230351177BEE8)
    std::cout << "Test encryption OK." << std::endl;
  else
    std::cout << "Test encryption failed." << std::endl;

  blowfish.decrypt(L, R);
  if (L == 1 && R == 2)
    std::cout << "Test decryption OK." << std::endl;
  else
    std::cout << "Test decryption failed." << std::endl;

  L = 0x0102030405060708;
  R = 0x0910111213141516;

  blowfish.initialize("A");
  blowfish.encrypt(L, R);
  if (L == 0xCA38165603F9915C && R == 0x61F0776A0F55E807)
    std::cout << "Test encryption OK." << std::endl;
  else
    std::cout << "Test encryption failed." << std::endl;

  blowfish.decrypt(L, R);
  if (L == 0x0102030405060708 && R == 0x0910111213141516)
    std::cout << "Test decryption OK." << std::endl;
  else
    std::cout << "Test decryption failed." << std::endl;

  L = 0x0102030405060708;
  R = 0x0910111213141516;

  blowfish.initialize("B");
  blowfish.encrypt(L, R);
  if (L == 0xD07690A78B109983 && R == 0x8DDF85826F2366C2)
    std::cout << "Test encryption OK." << std::endl;
  else
    std::cout << "Test encryption failed." << std::endl;

  blowfish.decrypt(L, R);
  if (L == 0x0102030405060708 && R == 0x0910111213141516)
    std::cout << "Test decryption OK." << std::endl;
  else
    std::cout << "Test decryption failed." << std::endl;
}
