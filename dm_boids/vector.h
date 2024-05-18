#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>

constexpr int windowWidth = 800;
constexpr int windowHeight = 600;


struct Vector {
    float x, y;

    Vector(float x = 0, float y = 0) : x(x), y(y) {}

    Vector operator+(const Vector& other) const {
        return Vector(x + other.x, y + other.y);
    }

    Vector operator-(const Vector& other) const {
        return Vector(x - other.x, y - other.y);

    }

    Vector operator*(float scalar) const {
        return Vector(x * scalar, y *  scalar);

    }

    Vector operator/(float scalar) const {
        return Vector(x / scalar, y / scalar);
    }

    Vector& operator+=(const Vector& other) {
        x = x + other.x;
        y = y + other.y;
        return *this;
    }

    float norm() const {
        return std::sqrt(x * x + y * y);
    }

    Vector normalize() const {
        if (norm() != 0) {
            return Vector(x / norm(), y / norm());
        } else {
            return *this; // Retourne le vecteur lui-même si sa norme est nulle
        }
    }
};

#endif // VECTOR_H
