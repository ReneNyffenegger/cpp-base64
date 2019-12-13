#include "base64.h"
#include <iostream>
#include <chrono>
int main() {
  const std::string s = 
    "René Nyffenegger\n"
    "http://www.renenyffenegger.ch\n"
    "passion for data\n";

  const std::string s = "An event loop, or sometimes called a message loop";
  auto begin = std::chrono::system_clock::now();
  std::string encoded = base64_encode(reinterpret_cast<const unsigned char*>(s.c_str()), s.length());
  auto start = std::chrono::system_clock::now();
  std::string decoded = base64_decode(encoded);

  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> encoded_time = start - begin;
  std::chrono::duration<double> decoded_time = end - start;
  std::cout << "encoded time: " << encoded_time.count() << "decoded time" << decoded_time.count() << std::endl;
  
  std::cout << "encoded: " << std::endl << encoded << std::endl << std::endl;
  std::cout << "decoded: " << std::endl << decoded << std::endl;
}
