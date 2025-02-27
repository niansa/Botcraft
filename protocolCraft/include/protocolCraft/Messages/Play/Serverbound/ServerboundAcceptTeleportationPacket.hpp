#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundAcceptTeleportationPacket : public BaseMessage<ServerboundAcceptTeleportationPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Accept Teleportation";

        DECLARE_FIELDS(
            (VarInt),
            (Id_)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Id_);
    };
} //ProtocolCraft
