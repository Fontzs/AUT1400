#ifndef Q4_H
#define Q4_H
#include <cmath>
#include <vector>
namespace q4 {
using namespace std;

struct Vector2D {
    double x{};
    double y{};
};

struct Sensor {
    Vector2D pos;
    double accuracy;
};

double get_base(std::vector<Sensor> sensors) {
    double res{};
    for (auto x : sensors) {
        res += x.accuracy;
    }
    return res;
}

double get_x(std::vector<Sensor> sensors) {
    double x{};
    for (auto s : sensors) {
        x += s.pos.x * s.accuracy / get_base(sensors);
    }
    return x;
}

double get_y(std::vector<Sensor> sensors) {
    double y{};
    for (auto s : sensors) {
        y += s.pos.y * s.accuracy / get_base(sensors);
    }
    return y;
}

Vector2D kalman_filter(std::vector<Sensor> sensors) {
    return Vector2D{get_x(sensors), get_y(sensors)};
}

}  // namespace q4

#endif  // Q4_H