#pragma once

#include <utility/utility.h>
#include <imgui/imgui.h>

namespace Math {

    class Matrix {
    public:
        float v[4][4];
    };

    class Vec3 {
    public:
        float x, y, z;

        Vec3 operator+(const Vec3& o) const {
            return { x + o.x, y + o.y, z + o.z };
        }

        Vec3 operator-(const Vec3& o) const {
            return { x - o.x, y - o.y, z - o.z };
        }

        Vec3& operator+=(const Vec3& o) {
            x += o.x; y += o.y; z += o.z;
            return *this;
        }

        Vec3& operator-=(const Vec3& o) {
            x -= o.x; y -= o.y; z -= o.z;
            return *this;
        }

        float magnitude() {
            return (this->x * this->x) + (this->y * this->y) + (this->z * this->z);
        }
    };

    bool wts(const Vec3* in, ImVec2& out);
}
