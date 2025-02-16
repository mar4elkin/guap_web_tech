#pragma once

#include <string.h>
#include <openssl/evp.h>

#define DIGEST_LENGTH 16

char* str_to_md5(const char* text) {
    unsigned char bytes[DIGEST_LENGTH];

    EVP_MD_CTX* context = EVP_MD_CTX_new();
    EVP_DigestInit_ex(context, EVP_md5(), NULL);

    EVP_DigestUpdate(context, text, strlen(text));
    unsigned int digestLength = DIGEST_LENGTH;

    EVP_DigestFinal_ex(context, bytes, &digestLength);
    EVP_MD_CTX_free(context);

    char* digest = (char*)malloc(DIGEST_LENGTH * 2 + 1);

    if (digest == NULL) {
        return NULL;
    }

    for (int i = 0; i < DIGEST_LENGTH; i++) {
        sprintf(&digest[i * 2], "%02x", bytes[i]);
    }

    return digest;
}