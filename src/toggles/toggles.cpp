#include <toggles/toggles.h>

namespace Toggles {
    namespace Esp {
        namespace Players {
            bool boxes { false };
            bool skeletons { true };
            bool health { true };
            bool names { false };
        }
        namespace Weapons {
            bool boxes { true };
            bool names { true };
        }
        bool players { true };
        bool weapons { true };
        bool combo_players { true };
        bool combo_weapons { false };
    }

    namespace Aimbot {
        bool in_fov { true };
        float fov { 30.0f };
    }
}
