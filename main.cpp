#include <iostream>
#include <iomanip>
#include <cmath>
#include <windows.h>

double Eiler(double x, double y) {
    return 2 * x * std::sqrt(y) - y;
}

int Rounding(double error) {
    int count = 0;
    while (true) {
        double tmp = error;
        if (static_cast<int>(tmp) % 10 != 0 || static_cast<int>(tmp) < 1) {
            error *= 10;
            count++;
        } else {
            count--;
            break;
        }
    }
    return count--;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    double a, s, b, error;
    std::cout << "Please enter a" << std::endl;
    std::cin >> a;
    std::cout << "Please enter s" << std::endl;
    std::cin >> s;

    while (s < 0) {
        std::cout << "Please enter new s (s>=0)" << std::endl;
        std::cin >> s;
    }

    std::cout << "Please b: " << std::endl;
    std::cin >> b;
    std::cout << "Please error: " << std::endl;
    std::cin >> error; // Погрешность

    while (error <= 0 || error >= 1) {
        std::cout << "Please enter new Error([0;1])" << std::endl;
        std::cin >> error;
    }

    double x_i, xi_2, y_i, dy_i, yi_1, yi_2, y1_2, h, yOld1, yOld2;
    bool firstFlag = true, secondFlag = true;
    int firstCount = 0, secondCount = 0;

    for (int step = 1; step <= 10000; step++) {
        firstCount = step;

        if (secondFlag) {
            secondCount = step;
        }

        h = (b - a) / static_cast<double>(step);
        x_i = a;
        xi_2 = a;
        y1_2 = s + h / 2 * Eiler(x_i, s);
        yi_2 = s;
        y_i = s + h * Eiler(x_i + h / 2, y1_2);
        x_i += h;
        yOld1 = y_i;
        yOld2 = yi_2;

        for (int i = 0; i < step - 1; i++) {
            if (firstFlag) {
                yi_1 = yi_2 + 2 * Eiler(xi_2, y_i) * h;
                yi_2 = y_i;
                y_i = yi_1;
            }
            xi_2 += h;
        }

        for (int i = 0; i < step; i++) {
            if (secondFlag) {
                dy_i = Eiler(x_i, yi_2) * h;
                yi_2 += dy_i;
            }
            x_i += h;
        }

        if (abs(y_i - yOld1) < error) {
            firstFlag = false;
        }

        if (abs(yi_2 - yOld2) < error) {
            secondFlag = false;
        }

        if (!firstFlag && !secondFlag) {
            break;
        }
    }


    if (firstCount == 10000) {
        std::cout << "It was not possible to achieve the specified accuracy (first method)" << std::endl;
    }

    std::cout << "Iterations (first method) " << firstCount << std::endl;
    std::cout
            << "Last value (first method) = "
            << std::fixed << std::setprecision(Rounding(error)) << y_i << std::endl;

    if (secondCount == 10000) {
        std::cout << "It was not possible to achieve the specified accuracy(second method)" << std::endl;
    }

    std::cout << "Iterations (second method) " << secondCount << std::endl;
    std::cout
            << "Last value (second method) = "
            << std::fixed << std::setprecision(Rounding(error)) << yi_2 << std::endl;

}

