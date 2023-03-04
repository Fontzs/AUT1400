#ifndef Q1_H
#define Q1_H
#include <cmath>
#include <functional>
namespace q1 {

double gradient_descent(double init, double step, std::function<double(double)> func);

template <typename T, typename F>
T gradient_descent(double init, double step) {
    return gradient_descent(init, step, F());
}

double gradient_descent(double init, double step, std::function<double(double)> f) {
    double x{init};
    double df{(f(x + 0.00001) - f(x)) / 0.00001};
    while (abs(df) > 0.00001) {
        x -= step * df;
        df = (f(x + 0.00001) - f(x)) / 0.00001;
    }
    return x;

    // double res{init};
    // double gradient{};
    // const double deltaX = 1e-4;
    // double deltaY{};
    // deltaY = (func(res + deltaX) - func(res));
    // gradient = deltaY / deltaX;
    // while (fabs(gradient) > 1e-6) {
    //     res -= gradient * step;
    //     deltaY = (func(res + deltaX) - func(res));
    //     gradient = deltaY / deltaX;
    // return res;
}

}  // namespace q1
#endif  // Q1_H
