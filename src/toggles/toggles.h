#pragma once

#include <utility/utility.h>

namespace Toggles {
    namespace Esp {
        namespace Players {
            extern bool boxes;
            extern bool skeletons;
            extern bool health;
            extern bool names;
        }
        namespace Weapons {
            extern bool boxes;
            extern bool names;
        }
        extern bool players;
        extern bool weapons;
    }

    namespace Aimbot {
        extern bool in_fov;
        extern float fov;
    }
}
