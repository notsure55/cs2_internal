#include <entities/entities.h>

namespace Entities {
    std::pair<Math::Vec3*, Math::Vec3*> CBaseEntity::get_pos() {
        auto pos = reinterpret_cast<Math::Vec3*>(*reinterpret_cast<uintptr_t*>(cast_ptr(this) + Offsets::Client::C_BaseEntity::m_CBodyComponent) + 0x90);
        return { pos, pos };
    }
}
