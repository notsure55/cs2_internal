#include <math/math.h>
#include <menu/menu.h>
#include <globals/globals.h>

namespace Math {
    bool wts(const Vec3* in, ImVec2& out) {
        const auto screen_size = Menu::get_screen_size();
        const auto z = Globals::view_matrix->v[3][0] * in->x + Globals::view_matrix->v[3][1] * in->y
            + Globals::view_matrix->v[3][2] * in->z + Globals::view_matrix->v[3][3];

        if (z < 0.001) {
            return false;
        }

        out.x = screen_size.x * 0.5;
        out.y = screen_size.y * 0.5;

        out.x *= 1.0 + (Globals::view_matrix->v[0][0] * in->x + Globals::view_matrix->v[0][1] *
                        in->y + Globals::view_matrix->v[0][2] * in->z + Globals::view_matrix->v[0][3]) / z;
        out.y *= 1.0 - (Globals::view_matrix->v[1][0] * in->x + Globals::view_matrix->v[1][1] *
                        in->y + Globals::view_matrix->v[1][2] * in->z + Globals::view_matrix->v[1][3]) / z;
        return true;
    }
}
