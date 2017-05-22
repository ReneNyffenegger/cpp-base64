#ifndef __BASE64_H_C0CE2A47_D10E_42C9_A27C_C883944E704A__
#define __BASE64_H_C0CE2A47_D10E_42C9_A27C_C883944E704A__

#include <string>

std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_decode(std::string const& s);

#endif /* __BASE64_H_C0CE2A47_D10E_42C9_A27C_C883944E704A__ */
