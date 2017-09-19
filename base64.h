//
//  base64 encoding and decoding with C++.
//  Version: 1.01.00
//
#pragma once
#ifndef BASE64_H_C0CE2A47_D10E_42C9_A27C_C883944E704A
#define BASE64_H_C0CE2A47_D10E_42C9_A27C_C883944E704A

#define LINE_BREAKS_APPEAR_MIME 76
#define LINE_BREAKS_APPEAR_PEM 64
#define NO_LINE_BREAKS 0
#define LINE_BREAKS_CHAR "\n"

#include <string>

namespace Encoding {

    class Base64 {
    public:
        static std::string Encode(std::string data, bool toUrlSafe = false, size_t lineBreaks = NO_LINE_BREAKS);
        static std::string Decode(std::string encoded_string);
        static std::string InsertLineBreaks(std::string base64, size_t lineBreakAppear = LINE_BREAKS_APPEAR_MIME);
        static std::string RemoveLineBreaks(std::string base64);
        static std::string ToSafeUrlBase64(std::string base64);
        static std::string ToUnsafeUrlBase64(std::string base64);
    private:
    };
}
#endif /* BASE64_H_C0CE2A47_D10E_42C9_A27C_C883944E704A */
