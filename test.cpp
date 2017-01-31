#include "base64.h"
#include <iostream>

int main() {
  const std::string s = 
    "René Nyffenegger\n"
    "http://www.renenyffenegger.ch\n"
    "passion for data\n";

  std::string encoded = base64_encode(reinterpret_cast<const unsigned char*>(s.c_str()), s.length());
  std::string decoded = base64_decode(encoded);

  std::cout << "encoded: " << std::endl << encoded << std::endl << std::endl;
  std::cout << "decoded: " << std::endl << decoded << std::endl;

  return 0;
}
