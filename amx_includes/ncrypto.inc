#if defined _ncrypto_included
    #endinput
#endif
#define _ncrypto_included

#if AMXX_VERSION_NUM >= 175
 #pragma reqlib ncrypto
 #if !defined AMXMODX_NOAUTOLOAD
  #pragma loadlib ncrypto
 #endif
#else
 #pragma library ncrypto
#endif

native ncrypto_hmacsha256_base64(const text[], const key[], out_text[], const length);
native ncrypto_generate_uuid(out_uid[37]);