#if PROTOCOL_VERSION > 759 /* > 1.19 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#include "protocolCraft/Types/Holder.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundDeleteChatPacket : public BaseMessage<ClientboundDeleteChatPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Delete Chat";

#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        DECLARE_FIELDS(
            (std::vector<unsigned char>),
            (MessageSignature)
        );
#else
        DECLARE_FIELDS(
            (Holder<std::array<unsigned char, 256>>),
            (MessageSignature)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(MessageSignature);
    };
} //ProtocolCraft
#endif
