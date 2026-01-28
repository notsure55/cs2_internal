#include <toggles/toggles.h>

namespace Toggles {
    namespace Esp {
        bool boxes { true };
        bool skeletons { true };
        bool health { true };
        bool names { true };
        bool players { true };
        bool weapons { true };
    }

    namespace Aimbot {
        bool in_fov { true };
        float fov { 30.0f };
    }
}
