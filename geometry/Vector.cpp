#include <bits/stdc++.h>
using namespace std;
/**
 * 2D vectors
 */
template <typename T>
struct Vector {
    T x, y;

    Vector(T a, T b) : x(a), y(b) {
    }
    Vector() : x(0), y(0) {
    }

    // secodn const denotes that this is a pure function
    // (does not modify this->)
    Vector operator+(const Vector &v) const {
        return Vectr(x + v.x, y + v.y);
    }

    Vector operator-() const {
        return Vector(-x, -y);
    }
    Vector operator-(const Vector &v) const {
        return Vector(x - v.x, y - v.y);
    }
    Vector operator*(const T scalar) const {
        return Vector(x * scalar, y * scalar);
    }
    int dot(const Vector &v) const {
        return x * v.x + y * v.y;
    }
    // magnitude of vector in out-of-plane direction
    int cross(const Vector &v) const {
        return x * v.y - y * v.x;
    }

    friend ostream &operator<<(ostream &out, const Vector &a) {
        out << a.x << " " << a.y;
        return out;
    }
};

int main() {
    Vector<int> x(1, 1);
    Vector<int> y(-1, 1);
    cout << x.dot(y) << endl;
    return 0;
}