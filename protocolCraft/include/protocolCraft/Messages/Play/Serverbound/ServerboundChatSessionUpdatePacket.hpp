#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/RemoteChatSessionData.hpp"

namespace ProtocolCraft
{
    class ServerboundChatSessionUpdatePacket : public BaseMessage<ServerboundChatSessionUpdatePacket>
    {
    public:

        static constexpr std::string_view packet_name = "Chat Session Update";

        DECLARE_FIELDS(
            (RemoteChatSessionData),
            (ChatSession)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(ChatSession);
    };
} //ProtocolCraft
#endif
