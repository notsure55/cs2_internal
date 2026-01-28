#include <entities/entities.h>
#include <globals/globals.h>

namespace Entities {
    Entity::Entity(CBaseEntity* e, const EntityType t) : entity(e), type(t) {}
    const EntityType& Entity::get_type() const {
        return type;
    }
    std::pair<Math::Vec3*, Math::Vec3*> Entity::get_pos() const {
        switch (this->get_type()) {
        case EntityType::PLAYER:
            return Globals::entity_system->get_pawn(this->get_entity<CPlayerController>())->get_pos();
        case EntityType::WEAPON:
            return this->get_entity<CBaseEntity>()->get_pos();
        }
    }

    char* Entity::get_name() const {
        switch (this->get_type()) {
        case EntityType::PLAYER:
            return this->get_entity<CPlayerController>()->get_name();
        case EntityType::WEAPON:
            return this->get_entity<CWeapon>()->get_name();
        }
    }
}
