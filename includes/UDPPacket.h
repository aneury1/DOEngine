#pragma once
#include <cstddef>
#include <string>

#define NETWORK

class UDPPacket
{
  public:
    typedef unsigned char packet;

    virtual int ReceivedPacket(const std::string& url, short port);

    virtual int SendPacket(const unsigned char* buffer, size_t max_len,
                           const std::string& url, short port);

  protected:
    packet* packet_buffer;
    int length;
    int socket_option;
};
