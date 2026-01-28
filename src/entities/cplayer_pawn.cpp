#include <entities/entities.h>

namespace Entities {
    std::pair<Math::Vec3*, Math::Vec3*> CPlayerPawn::get_pos() const {
        return { reinterpret_cast<Math::Vec3*>(cast_ptr(this) + Offsets::Client::C_CSPlayerPawn::m_vecLastClipCameraPos), reinterpret_cast<Math::Vec3*>(cast_ptr(this) + Offsets::Client::C_BasePlayerPawn::m_vOldOrigin) };
    }

    int CPlayerPawn::get_health() const {
        return *reinterpret_cast<int*>(cast_ptr(this) + Offsets::Client::C_BaseEntity::m_iHealth);
    }

    const uintptr_t CPlayerPawn::get_skeleton() const {
        const auto game_scene { *reinterpret_cast<uintptr_t*>(cast_ptr(this) + 0x38) };
        const auto skeletons { *reinterpret_cast<uintptr_t*>(game_scene + 0x290) };
        return skeletons;
    }

    Math::Vec3* CPlayerPawn::get_bone(Skeletons::CT::BONES bone) const {
        return reinterpret_cast<Math::Vec3*>(this->get_skeleton() + bone * 0x20);
    }
}
