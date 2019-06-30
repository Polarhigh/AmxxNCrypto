#include "sdk/amxxmodule.h"
#include "hash-library/hmac.h"
#include "hash-library/sha256.h"
#include "base64.h"
#include "uuid.h"
#include <string>

static cell AMX_NATIVE_CALL amx_hmacsha256_base64(AMX* amx, cell* params)
{
    int text_len;
    char* text = MF_GetAmxString(amx, params[1], 0, &text_len);

    int key_len;
    char* key = MF_GetAmxString(amx, params[2], 1, &key_len);

    unsigned char hashed[32];
    hmac<SHA256>(text, text_len, key, key_len, hashed);

    std::string base64_encoded = base64_encode(hashed, sizeof(hashed));

    //MF_SetAmxString(amx, params[3], base64_encoded.c_str(), base64_encoded.length());
    MF_SetAmxString(amx, params[3], base64_encoded.c_str(), params[4]);

    return 0;
}

static cell AMX_NATIVE_CALL amx_generate_uuid(AMX* amx, cell* params)
{
    std::string uuid = generate_uuid();

    MF_SetAmxString(amx, params[1], uuid.c_str(), uuid.length());

    return 0;
}

AMX_NATIVE_INFO g_natives[] =
{
    { "ncrypto_hmacsha256_base64",		amx_hmacsha256_base64 },
    { "ncrypto_generate_uuid",		    amx_generate_uuid },
    { NULL,						        NULL }
};
