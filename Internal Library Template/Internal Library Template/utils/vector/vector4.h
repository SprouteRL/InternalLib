#pragma once
#include <cmath>

class Vector4 {
public:
    float x, y, z, w;

    Vector4() : x(0), y(0), z(0), w(0) {}
    Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    Vector4(const Vector3& v, float w) : x(v.x), y(v.y), z(v.z), w(w) {}

    Vector4 operator+(const Vector4& other) {
        return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    Vector4 operator-(const Vector4& other) {
        return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    Vector4 operator*(float scalar) {
        return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
    }

    Vector4 operator/(float scalar) {
        return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
    }

    float dot(const Vector4& other) {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    float length() {
        return sqrt(x * x + y * y + z * z + w * w);
    }

    Vector4 normalize() {
        float len = length();
        if (len > 0) {
            return *this / len;
        }
        return Vector4(0, 0, 0, 0);
    }
};