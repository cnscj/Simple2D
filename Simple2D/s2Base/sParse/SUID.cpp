#include "SUID.h"
#include <objbase.h>
std::string SUID::CreateUUID()
{

#ifdef WIN32
    return SUID::CreateGUID();
#else
    static const size_t BUFF_SIZE = 64;
    char szGUID[BUFF_SIZE];
    TmUUID_t    uuid;
    TmMsg_CreateUUID(&uuid);
    sprintf(szGUID, "%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X",
    uuid.Data1, uuid.Data2, uuid.Data3, uuid.Data4[0], uuid.Data4[1], uuid.Data4[2],
    uuid.Data4[3], uuid.Data4[4], uuid.Data4[5], uuid.Data4[6], uuid.Data4[7]);
    return std::string(szGUID);
#endif
}

std::string SUID::CreateGUID()
{

#ifdef WIN32
    static const size_t BUFF_SIZE = 64;
    char szGUID[BUFF_SIZE];
    GUID uuid;
    CoCreateGuid(&uuid);
    sprintf_s(szGUID, sizeof(szGUID), "%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X",
    uuid.Data1, uuid.Data2, uuid.Data3, uuid.Data4[0], uuid.Data4[1], uuid.Data4[2],
    uuid.Data4[3], uuid.Data4[4], uuid.Data4[5], uuid.Data4[6], uuid.Data4[7]);
    return std::string(szGUID);
#else
    return SUID::CreateUUID();
#endif

}