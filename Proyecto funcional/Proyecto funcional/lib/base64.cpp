#include "base64.h"

namespace base64 {

const char encoding_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const char padding_char = '=';

String encode(const uint8_t* data, size_t length) {
    String encoded;
    int i = 0;

    while (i < length) {
        uint32_t octet_a = i < length ? data[i++] : 0;
        uint32_t octet_b = i < length ? data[i++] : 0;
        uint32_t octet_c = i < length ? data[i++] : 0;

        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        encoded += encoding_table[(triple >> 3 * 6) & 0x3F];
        encoded += encoding_table[(triple >> 2 * 6) & 0x3F];
        encoded += (i > length + 1) ? padding_char : encoding_table[(triple >> 1 * 6) & 0x3F];
        encoded += (i > length) ? padding_char : encoding_table[(triple >> 0 * 6) & 0x3F];
    }

    return encoded;
}

}
