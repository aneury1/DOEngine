#pragma once

#ifdef __linux__
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#endif
#include <string>
#ifdef __WIN32__
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>

struct InitSocketEngine{
    InitSocketEngine(){
       WSAData data;
       WSAStartup(MAKEWORD(2,2), &data);
    }
    
};
static InitSocketEngine object;
#else
typedef int SOCKET;
#endif


class UDPServer
{

    
   public:

    SOCKET server_socket;
    bool is_running;
    UDPServer(sockaddr_in* addr);
    bool isRunning();
    std::string recv();
};