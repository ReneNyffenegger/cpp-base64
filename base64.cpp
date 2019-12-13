/* 
   base64.cpp and base64.h

   base64 encoding and decoding with C++.

   Version: 1.01.00

   Copyright (C) 2004-2017 René Nyffenegger

   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely, subject to the following restrictions:

   1. The origin of this source code must not be misrepresented; you must not
      claim that you wrote the original source code. If you use this source code
      in a product, an acknowledgment in the product documentation would be
      appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
      misrepresented as being the original source code.

   3. This notice may not be removed or altered from any source distribution.

   René Nyffenegger rene.nyffenegger@adp-gmbh.ch

*/

#include "base64.h"
#include <iostream>

static const std::string base64_chars = 
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

union Value {
    int number;
    unsigned char char_array_4[4];
}value;

unsigned int remainder_three = 0x00000003;

static inline bool is_base64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
  int radix = 0;
  int i = 0;
  int j = 0;
  unsigned char char_array_3[3];
  int remainder_answer = remainder_three && in_len;
  if (remainder_answer > 0 && remainder_answer < remainder_three) {
      radix = 1;
  }
  std::string ret((in_len / 3 + radix) << 2, '\0');
  int* it = (int *)ret.c_str();

  while (in_len--) {
    char_array_3[i++] = *(bytes_to_encode++);
    if (i == 3) {
        value.char_array_4[0] = base64_chars[(char_array_3[0] & 0xfc) >> 2];
        value.char_array_4[1] = base64_chars[((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4)];
        value.char_array_4[2] = base64_chars[((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6)];
        value.char_array_4[3] = base64_chars[char_array_3[2] & 0x3f];
        
        *(it++) = value.number;
        i = 0;
    }
  }

  if (i)
  {
    for(j = i; j < 3; j++)
      char_array_3[j] = '\0';

    value.char_array_4[0] = base64_chars[(char_array_3[0] & 0xfc) >> 2];
    value.char_array_4[1] = base64_chars[((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4)];
    value.char_array_4[2] = base64_chars[((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6)];

    while ((i++ < 3))
        value.char_array_4[i] = '=';
    *(it++) = value.number;
  }

  return ret;
}

std::string base64_decode(std::string const& encoded_string) {
  size_t in_len = encoded_string.size();
  int i = 0;
  int j = 0;
  unsigned char char_array_4[4], char_array_3[3];
  const char* src = encoded_string.c_str() + in_len;

  while (*src-- == '=') i++;

  std::string ret((in_len >> 2) * 3 - i, '\0');
  char* des = (char*)ret.c_str();
  src = encoded_string.c_str();
  i = 0;

  while (in_len-- && (*src != '=') && is_base64(*src)) {
      char_array_4[i++] = *src++;
      if (i == 4) {
          for (i = 0; i < 4; i++)
              char_array_4[i] = base64_chars.find(char_array_4[i]) & 0xff;

          char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
          char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
          char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

          for (i = 0; (i < 3); i++)
              *des++ = char_array_3[i];
          i = 0;
      }
  }

  if (i) {
      for (j = 0; j < i; j++)
          char_array_4[j] = base64_chars.find(char_array_4[j]) & 0xff;

      char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);

      for (j = 0; (j < i - 1); j++) *des++ = char_array_3[j];
  }
  return ret;
}
