#include <iostream>
#include "base64.h"
using namespace std;
using namespace Encoding;

/*
 * 
 */
int main(int argc, char** argv) {

    string str = R"(René Nyffenegger
"http://www.renenyffenegger.ch
Passion for data)";
    cout << "Original: " << str << endl << endl;
    str = Base64::Encode(str);
    cout << "Encoded: " << str << endl << endl;
    str = Base64::Decode(str);
    cout << "Decoded: " << str << endl << endl;

    cout << "---Encode - No Linebreaks, Safe Url Base64 ---" << endl << Base64::Encode("HelloWorld!!!", false, true) << endl << endl;
    cout << "---Encode - No Linebreaks, Unsafe Url Base64 ---" << endl << Base64::Encode("HelloWorld!!!", false, false) << endl << endl;

    cout << "---Decode - No Linebreaks, Safe Url Base64 ---" << endl << Base64::Decode("SGVsbG9Xb3JsZCEhIQ,,") << endl << endl;
    cout << "---Decode - No Linebreaks, Unsafe Url Base64 ---" << endl << Base64::Decode("SGVsbG9Xb3JsZCEhIQ==") << endl << endl;

    string toEncode = "HelloWorld!!!HelloWorld!!!HelloWorld!!!HelloWorld!!!HelloWorld!!!HelloWorld!!!HelloWorld!!!HelloWorld!!!HelloWorld!!!HelloWorld!!!HelloWorld!!!HelloWorld!!!HelloWorld!!!HelloWorld!!!";
    cout << "---Encode - Linebreaks, Safe Url Base64 ---" << endl << Base64::Encode(toEncode, true, true)  << endl << endl;
    cout << "---Encode - Linebreaks, Unsafe Url Base64 ---" << endl << Base64::Encode(toEncode, true, false) << endl << endl;

    string toDecode1 = R"(SGVsbG9Xb3JsZCEhIUhlbGxvV29ybGQhISFIZWxsb1dvcmxkISEhSGVsbG9Xb3JsZCEhIUhlbGxv
V29ybGQhISFIZWxsb1dvcmxkISEhSGVsbG9Xb3JsZCEhIUhlbGxvV29ybGQhISFIZWxsb1dvcmxk
ISEhSGVsbG9Xb3JsZCEhIUhlbGxvV29ybGQhISFIZWxsb1dvcmxkISEhSGVsbG9Xb3JsZCEhIUhl
bGxvV29ybGQhISE,)";

    string toDecode2 = R"(SGVsbG9Xb3JsZCEhIUhlbGxvV29ybGQhISFIZWxsb1dvcmxkISEhSGVsbG9Xb3JsZCEhIUhlbGxv
V29ybGQhISFIZWxsb1dvcmxkISEhSGVsbG9Xb3JsZCEhIUhlbGxvV29ybGQhISFIZWxsb1dvcmxk
ISEhSGVsbG9Xb3JsZCEhIUhlbGxvV29ybGQhISFIZWxsb1dvcmxkISEhSGVsbG9Xb3JsZCEhIUhl
bGxvV29ybGQhISE=)";

    cout << "---Decode - Linebreaks, Safe Url Base64 ---" << endl << Base64::Decode(toDecode1) << endl << endl;
    cout << "---Decode - Linebreaks, Unsafe Url Base64 ---" << endl << Base64::Decode(toDecode2) << endl << endl;
    
    cout << "---Removing Linebreaks & Transform to Unsafe Url Base64---" << endl << Base64::ToUnsafeUrlBase64(Base64::RemoveLineBreaks(toDecode1)) << endl << endl;
    cout << "---Removing Linebreaks & Transform to Safe Url Base64---" << endl << Base64::ToSafeUrlBase64(Base64::RemoveLineBreaks(toDecode2)) << endl << endl;
    
        string toDecode3 = R"(SGVsbG9Xb3JsZCEhIUhlbGxvV29ybGQhISFIZWxsb1dvcmxkISEhSGVsbG9Xb3JsZCEhIUhlbGxvV29ybGQhISFIZWxsb1dvcmxkISEhSGVsbG9Xb3JsZCEhIUhlbGxvV29ybGQhISFIZWxsb1dvcmxkISEhSGVsbG9Xb3JsZCEhIUhlbGxvV29ybGQhISFIZWxsb1dvcmxkISEhSGVsbG9Xb3JsZCEhIUhlbGxvV29ybGQhISE,)";
    string toDecode4 = R"(SGVsbG9Xb3JsZCEhIUhlbGxvV29ybGQhISFIZWxsb1dvcmxkISEhSGVsbG9Xb3JsZCEhIUhlbGxvV29ybGQhISFIZWxsb1dvcmxkISEhSGVsbG9Xb3JsZCEhIUhlbGxvV29ybGQhISFIZWxsb1dvcmxkISEhSGVsbG9Xb3JsZCEhIUhlbGxvV29ybGQhISFIZWxsb1dvcmxkISEhSGVsbG9Xb3JsZCEhIUhlbGxvV29ybGQhISE=)";
    
    cout << "---Inserting Linebreaks Default 76 ---" << endl << Base64::InsertLineBreaks(toDecode3) << endl << endl;
    cout << "---Inserting Linebreaks PEM Format 64 ---" << endl << Base64::InsertLineBreaks(toDecode4, LINE_BREAK_APPEAR_PEM) << endl << endl;
    cout << "---Inserting Linebreaks Custom every 10 chars ---" << endl << Base64::InsertLineBreaks(toDecode4, 10) << endl << endl;
    return 0;
}