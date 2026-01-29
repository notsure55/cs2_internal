#include <entities/entities.h>

namespace Entities {
    char* CWeapon::get_name() {
        return { *reinterpret_cast<char**>(*reinterpret_cast<uintptr_t*>(cast_ptr(this) + 0x10) + 0x20) };
    }
    std::pair<Math::Vec3*, Math::Vec3*> CWeapon::get_pos() {
        return reinterpret_cast<CBaseEntity*>(this)->get_pos();
    }
}
