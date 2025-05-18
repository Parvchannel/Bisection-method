#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cmath>
using namespace std;

// Replace 'x' with a number in the input string
string substituteX(string expr, double x) {
    string result;
    for (size_t i = 0; i < expr.length(); ++i) {
        if (expr[i] == 'x') {
            result += "(" + to_string(x) + ")";
        } else {
            result += expr[i];
        }
    }
    return result;
}

// Check operator precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

// Apply a basic math operation
double applyOp(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
        default: return 0;
    }
}

// Evaluate a fully numerical expression string
double evaluate(string tokens) {
    stack<double> values;
    stack<char> ops;

    for (size_t i = 0; i < tokens.length(); ++i) {
        if (tokens[i] == ' ') continue;

        if (isdigit(tokens[i]) || tokens[i] == '.') {
            string val;
            while (i < tokens.length() && (isdigit(tokens[i]) || tokens[i] == '.'))
                val += tokens[i++];
            values.push(stod(val));
            i--;
        } else if (tokens[i] == '(') {
            ops.push(tokens[i]);
        } else if (tokens[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(a, b, op));
            }
            if (!ops.empty()) ops.pop(); // pop '('
        } else {
            while (!ops.empty() && precedence(ops.top()) >= precedence(tokens[i])) {
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(a, b, op));
            }
            ops.push(tokens[i]);
        }
    }

    while (!ops.empty()) {
        double b = values.top(); values.pop();
        double a = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOp(a, b, op));
    }

    return values.top();
}

// Evaluate expression string at value of x
double f(string expr, double x) {
    string replaced = substituteX(expr, x);
    return evaluate(replaced);
}

// Bisection method using expression
void bisection(string expr, double a, double b, double tol, int max_iter) {
    if (f(expr, a) * f(expr, b) >= 0) {
        cout << "Function has same signs at a and b. Try different interval.\n";
        return;
    }

    double c;
    int iter = 0;
    while ((b - a) >= tol && iter < max_iter) {
        c = (a + b) / 2.0;
        double fc = f(expr, c);

        if (fc == 0.0)
            break;
        else if (fc * f(expr, a) < 0)
            b = c;
        else
            a = c;

        iter++;
    }

    cout << "Root found at x = " << c << " after " << iter << " iterations\n";
}

int main() {
    string expression;
    double a, b, tol;
    int max_iter;

    cout << "Enter function of x (e.g., x^2 - 4): ";
    getline(cin, expression);
    cout << "Enter lower bound (a): ";
    cin >> a;
    cout << "Enter upper bound (b): ";
    cin >> b;
    cout << "Enter tolerance (e.g., 0.001): ";
    cin >> tol;
    cout << "Enter maximum iterations: ";
    cin >> max_iter;

    bisection(expression, a, b, tol, max_iter);

    return 0;
}
