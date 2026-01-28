#include <math/math.h>
#include <menu/menu.h>
#include <globals/globals.h>

namespace Math {
    constexpr float PI { 3.14 };

    float radians_to_degrees(const float& angle) {
        return angle * 180.0 / PI;
    }

    const ImVec2 calculate_angle(const Vec3* origin, const Vec3* target) {
        ImVec2 angles;
        const float yaw_angle = std::atan2f(target->y - origin->y, target->x - origin->x);
        angles.y = radians_to_degrees(yaw_angle);

        const float distance = (target->z - origin->z) / (*origin - *target).magnitude();
        const float pitch_angle = -(std::asinf(distance));
        angles.x = radians_to_degrees(pitch_angle);

        return angles;
    }

    bool wts(const Vec3* in, ImVec2& out, float* outz) {
        const auto screen_size = Menu::get_screen_size();
        const auto z = Globals::view_matrix->v[3][0] * in->x + Globals::view_matrix->v[3][1] * in->y
            + Globals::view_matrix->v[3][2] * in->z + Globals::view_matrix->v[3][3];

        if (z < 0.001) {
            return false;
        }

        if (outz) {
            *outz = (float)z;
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
