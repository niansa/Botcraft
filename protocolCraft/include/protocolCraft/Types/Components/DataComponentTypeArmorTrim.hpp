#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeArmorTrim : public DataComponentType
        {
            DECLARE_FIELDS(
                (VarInt,   VarInt,  bool),
                (Material, Pattern, ShowInTooltip)
            );
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(Material);
            GETTER_SETTER(Pattern);
            GETTER_SETTER(ShowInTooltip);
        };
    }
}
#endif
