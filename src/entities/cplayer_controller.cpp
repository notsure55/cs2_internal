#include <entities/entities.h>

namespace Entities {
    char* CPlayerController::get_name() const {
        return reinterpret_cast<char*>(cast_ptr(this) + Offsets::Client::CBasePlayerController::m_iszPlayerName);
    }
}
