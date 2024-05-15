#include "UDPPacket.h"


#ifdef __WIN32__
#include <windows.h>
#include <winsock2.h>
struct winsocket_initializer
{
    winsocket_initializer()
    {
        WSAData data;
        WSAStartup(MAKEWORD(2, 2), &data);
        //// MessageBox(NULL,"INIT CORRE", "FIIFFI", MB_OK);
    }
};
static winsocket_initializer init__in;
#endif

int UDPPacket::ReceivedPacket(const std::string& url, short port)
{
    return 0;
}

int UDPPacket::SendPacket(const unsigned char* buffer, size_t max_len,
                          const std::string& url, short port)
{
    return 0;
}
