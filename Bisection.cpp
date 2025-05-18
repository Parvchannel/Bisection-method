#include <iostream>
#include <cmath>
using namespace std;

// Predefined equation: change this as needed
double f(double x) {
    return(x * x)  + x - 12;  // Example: f(x) = x^3 - x - 2
}

// Bisection Method
void bisection(double a, double b, double tol, int max_iter) {
    if (f(a) * f(b) >= 0) {
        cout << "f(a) and f(b) must have opposite signs.\n";
        return;
    }

    double c;
    int iter = 0;

    while ((b - a) >= tol && iter < max_iter) {
        c = (a + b) / 2.0;

        if (f(c) == 0.0) {
            break;
        } else if (f(c) * f(a) < 0) {
            b = c;
        } else {
            a = c;
        }

        iter++;
    }

    cout << "Root found at x = " << c << " after " << iter << " iterations.\n";
}

int main() {
    double a, b, tol;
    int max_iter;

    // Take user input for range and parameters
    cout << "Enter lower bound (a): ";
    cin >> a;
    cout << "Enter upper bound (b): ";
    cin >> b;
    cout << "Enter tolerance (e.g., 0.001): ";
    cin >> tol;
    cout << "Enter maximum iterations: ";
    cin >> max_iter;

    // Perform bisection on the hardcoded function
    bisection(a, b, tol, max_iter);

    return 0;
}
