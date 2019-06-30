#ifdef WIN32
#include <Rpc.h>
#else
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <uuid/uuid.h>
#endif
#include <string>

std::string generate_uuid()
{
#ifdef WIN32
    UUID uuid;
    UuidCreate(&uuid);

    unsigned char* uuid_str;
    UuidToStringA(&uuid, &uuid_str);

    std::string s((char*)uuid_str);

    RpcStringFreeA(&uuid_str);
#else
    uuid_t uuid;
    uuid_generate_time_safe(uuid);
    
    char uuid_str[37];
    uuid_unparse_lower(uuid, uuid_str);

    std::string s(uuid_str);
    
    uuid_clear(uuid);
#endif
    return s;
}
