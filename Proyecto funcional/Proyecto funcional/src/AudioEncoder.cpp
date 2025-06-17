#include "AudioEncoder.h"

static const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

String encodeToBase64(const int16_t* buffer, size_t len) {
    const uint8_t* bytes_to_encode = reinterpret_cast<const uint8_t*>(buffer);
    size_t input_length = len * sizeof(int16_t);

    String result;
    int i = 0;
    uint8_t array3[3];
    uint8_t array4[4];

    while (input_length--) {
        array3[i++] = *(bytes_to_encode++);
        if (i == 3) {
            array4[0] = (array3[0] & 0xfc) >> 2;
            array4[1] = ((array3[0] & 0x03) << 4) + ((array3[1] & 0xf0) >> 4);
            array4[2] = ((array3[1] & 0x0f) << 2) + ((array3[2] & 0xc0) >> 6);
            array4[3] = array3[2] & 0x3f;

            for (i = 0; i < 4; i++)
                result += base64_chars[array4[i]];
            i = 0;
        }
    }

    if (i > 0) {
        for (int j = i; j < 3; j++)
            array3[j] = '\0';

        array4[0] = (array3[0] & 0xfc) >> 2;
        array4[1] = ((array3[0] & 0x03) << 4) + ((array3[1] & 0xf0) >> 4);
        array4[2] = ((array3[1] & 0x0f) << 2) + ((array3[2] & 0xc0) >> 6);
        array4[3] = array3[2] & 0x3f;

        for (int j = 0; j < i + 1; j++)
            result += base64_chars[array4[j]];

        while ((i++ < 3))
            result += '=';
    }

    return result;
}


