#pragma once

#include "UDPPacket.h"
#include "gmock/gmock.h"
#include <cstddef>

class UDPPacketMock : public UDPPacket
{
    MOCK_METHOD(int, ReceivedPacket, (const std::string&, short), (override));
    MOCK_METHOD(int, SendPacket,
                (const unsigned char*, size_t, const std::string&, short),
                (override));
};