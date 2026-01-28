#include <entities/entities.h>

namespace Entities {
    char* CWeapon::get_name() {
        return { *reinterpret_cast<char**>(*reinterpret_cast<uintptr_t*>(cast_ptr(this) + 0x10) + 0x20) };
    }
}
