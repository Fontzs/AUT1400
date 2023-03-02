#ifndef Q1_H
#define Q1_H
#include <cmath>

namespace q1 {

// To calculate [f(x+h)-f(x)]/h
double derivative(double (*f)(double), double x, double h = 0.00001) {
    return (f(x + h) - f(x)) / h;
}

double gradient_descent(double initial_value, double step_size, double (*f)(double)) {
    double x_position{initial_value};
    double df = derivative(f, x_position);
    while (std::abs(df) > 0.00001) {
        x_position -= step_size * derivative(f, x_position);
        df = derivative(f, x_position);
    }
    return x_position;
}

template <typename Func>
double gradient_descent(double initial_guess, double learning_rate, Func f) {
    double current_value = initial_guess;
    double gradient;

    // 迭代更新
    for (int i = 0; i < 10000000; i++) {
        gradient = (f(current_value + FLT_EPSILON) - f(current_value)) / FLT_EPSILON;
        current_value -= learning_rate * gradient;
    }
    return current_value;
}

}  // namespace q1
#endif  // Q1_H