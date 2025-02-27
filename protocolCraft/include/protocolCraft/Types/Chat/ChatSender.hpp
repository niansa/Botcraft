#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ChatSender : public NetworkType
    {
        DECLARE_FIELDS(
            (UUID, Chat, std::optional<Chat>),
            (Uuid, Name, TeamName)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Uuid);
        GETTER_SETTER(Name);
        GETTER_SETTER(TeamName);
    };
}
#endif
