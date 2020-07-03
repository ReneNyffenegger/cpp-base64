#include "base64.h"
#include <iostream>

int main() {

  bool all_tests_passed = true;

  const std::string orig =
    "René Nyffenegger\n"
    "http://www.renenyffenegger.ch\n"
    "passion for data\n";

    std::string encoded = base64_encode(reinterpret_cast<const unsigned char*>(orig.c_str()), orig.length());
    std::string decoded = base64_decode(encoded);

    if (encoded != "UmVuw6kgTnlmZmVuZWdnZXIKaHR0cDovL3d3dy5yZW5lbnlmZmVuZWdnZXIuY2gKcGFzc2lvbiBmb3IgZGF0YQo=") {
      std::cout << "Encoding is wrong" << std::endl;
      all_tests_passed = false;
    }

    if (decoded != orig) {
      std::cout << "decoded != orig" << std::endl;
      all_tests_passed = false;
    }

 // Test all possibilites of fill bytes (none, one =, two ==)
 // References calculated with: https://www.base64encode.org/

    std::string rest0_original = "abc";
    std::string rest0_reference = "YWJj";

    std::string rest0_encoded = base64_encode(reinterpret_cast<const unsigned char*>(rest0_original.c_str()),
      rest0_original.length());
    std::string rest0_decoded = base64_decode(rest0_encoded);

    if (rest0_decoded != rest0_original) {
      std::cout << "rest0_decoded != rest0_original" << std::endl;
      all_tests_passed = false;
    }
    if (rest0_reference != rest0_encoded) {
      std::cout << "rest0_reference != rest0_encoded" << std::endl;
      all_tests_passed = false;
    }

 // std::cout << "encoded:   " << rest0_encoded << std::endl;
 // std::cout << "reference: " << rest0_reference << std::endl;
 // std::cout << "decoded:   " << rest0_decoded << std::endl << std::endl;

    std::string rest1_original = "abcd";
    std::string rest1_reference = "YWJjZA==";

    std::string rest1_encoded = base64_encode(reinterpret_cast<const unsigned char*>(rest1_original.c_str()),
      rest1_original.length());
    std::string rest1_decoded = base64_decode(rest1_encoded);

    if (rest1_decoded != rest1_original) {
      std::cout << "rest1_decoded != rest1_original" << std::endl;
      all_tests_passed = false;
    }
    if (rest1_reference != rest1_encoded) {
      std::cout << "rest1_reference != rest1_encoded" << std::endl;
      all_tests_passed = false;
    }

 // std::cout << "encoded:   " << rest1_encoded << std::endl;
 // std::cout << "reference: " << rest1_reference << std::endl;
 // std::cout << "decoded:   " << rest1_decoded << std::endl << std::endl;

    std::string rest2_original = "abcde";
    std::string rest2_reference = "YWJjZGU=";

    std::string rest2_encoded = base64_encode(reinterpret_cast<const unsigned char*>(rest2_original.c_str()),
      rest2_original.length());
    std::string rest2_decoded = base64_decode(rest2_encoded);

    if (rest2_decoded != rest2_original) {
      std::cout << "rest2_decoded != rest2_original" << std::endl;
      all_tests_passed = false;
    }
    if (rest2_reference != rest2_encoded) {
      std::cout << "rest2_reference != rest2_encoded" << std::endl;
      all_tests_passed = false;
    }

 // std::cout << "encoded:   " << rest2_encoded << std::endl;
 // std::cout << "reference: " << rest2_reference << std::endl;
 // std::cout << "decoded:   " << rest2_decoded << std::endl << std::endl;
 //

 // --------------------------------------------------------------
 //
 // Data that is 17 bytes long requires one padding byte when
 // base-64 encoded. Such an encoded string could not correctly
 // be decoded when encoded with «url semantics». This bug
 // was discovered by https://github.com/kosniaz. The following
 // test checks if this bug was fixed:
 //
    std::string a17_orig    = "aaaaaaaaaaaaaaaaa";
    std::string a17_encoded     = base64_encode(a17_orig, false);
    std::string a17_encoded_url = base64_encode(a17_orig, true );

    if (a17_encoded != "YWFhYWFhYWFhYWFhYWFhYWE=") {
        std::cout << "Failed to encode a17" << std::endl;
        all_tests_passed = false;
    }

    if (a17_encoded_url != "YWFhYWFhYWFhYWFhYWFhYWE.") {
        std::cout << "Failed to encode a17 (url)" << std::endl;
        all_tests_passed = false;
    }

    if (base64_decode(a17_encoded_url) != a17_orig) {
        std::cout << "Failed to decode a17 (url)" << std::endl;
        all_tests_passed = false;
    }

    if (base64_decode(a17_encoded    ) != a17_orig) {
        std::cout << "Failed to decode a17 (no url)" << std::endl;
        all_tests_passed = false;
    }

 // --------------------------------------------------------------

 // characters 63 and 64 / URL encoding

    std::string s_6364 = "\x03" "\xef" "\xff" "\xf9";

    std::string s_6364_encoded     = base64_encode(s_6364, false);
    std::string s_6364_encoded_url = base64_encode(s_6364, true );

    if (s_6364_encoded    != "A+//+Q==") {
        std::cout << "Failed to encode_6364 (no url)" << std::endl;
        all_tests_passed = false;
    }

    if (s_6364_encoded_url!= "A-__-Q..") {
        std::cout << "Failed to encode_6364 (url)" << std::endl;
        all_tests_passed = false;
    }

    if (base64_decode(s_6364_encoded    ) != s_6364) {
        std::cout << "Failed to decode s_6364_encoded" << std::endl;
        all_tests_passed = false;
    }

    if (base64_decode(s_6364_encoded_url) != s_6364) {
        std::cout << "Failed to decode s_6364_encoded_url" << std::endl;
        all_tests_passed = false;
    }


 // --------------------------------------------------------------

#if __cplusplus >= 201703L
 //
 // Test the string_view interface (which required C++17)
 //
    std::string_view sv_orig    = "foobarbaz";
    std::string_view sv_encoded = base64_encode(sv_orig);

    if (sv_encoded != "Zm9vYmFyYmF6") {
       std::cout << "Failed to encode with string_view" << std::endl;
       all_tests_passed = false;
    }

    std::string_view sv_decoded = base64_decode(sv_encoded);

    if (sv_decoded != sv_orig) {
       std::cout << "Failed to decode with string_view" << std::endl;
       all_tests_passed = false;
    }

#endif

    if (all_tests_passed) return 0;
    return 1;
}
