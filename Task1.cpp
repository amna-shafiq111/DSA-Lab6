#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <cctype>

using namespace std;

const int MAX_SIZE = 500;

template <typename T>
class Stack {
private:
    T data[MAX_SIZE];
    int topIndex;

public:
    Stack() {
        topIndex = -1;
    }

    bool isEmpty() {
        return topIndex == -1;
    }

    bool isFull() {
        return topIndex == MAX_SIZE - 1;
    }

    void push(T value) {
        if (isFull()) {
            cout << "Stack overflow!" << endl;
            exit(1);
        }

        data[++topIndex] = value;
    }

    T pop() {
        if (isEmpty()) {
            cout << "Stack underflow!" << endl;
            exit(1);
        }

        return data[topIndex--];
    }

    T top() {
        if (isEmpty()) {
            cout << "Stack is empty!" << endl;
            exit(1);
        }

        return data[topIndex];
    }
};

int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;

    return 0;
}

bool isOperator(char c) {
    return c == '+' || c == '-' ||
           c == '*' || c == '/' || c == '^';
}

string infix_to_postfix(string expr) {
    Stack<char> operators;
    string output = "";

    for (int i = 0; i < (int)expr.length(); i++) {
        char c = expr[i];

        if (isspace((unsigned char)c))
            continue;

        if (isalnum((unsigned char)c) || c == '.') {
            while (i < (int)expr.length() &&
                   (isalnum((unsigned char)expr[i]) ||
                    expr[i] == '.')) {
                output += expr[i];
                i++;
            }

            output += ' ';
            i--;
        }
        else if (c == '(') {
            operators.push(c);
        }
        else if (c == ')') {
            while (!operators.isEmpty() &&
                   operators.top() != '(') {
                output += operators.pop();
                output += ' ';
            }

            if (!operators.isEmpty())
                operators.pop();
        }
        else if (isOperator(c)) {
            while (!operators.isEmpty() &&
                   operators.top() != '(' &&
                   (precedence(operators.top()) > precedence(c) ||
                    (precedence(operators.top()) == precedence(c)
                     && c != '^'))) {
                output += operators.pop();
                output += ' ';
            }

            operators.push(c);
        }
    }

    while (!operators.isEmpty()) {
        output += operators.pop();
        output += ' ';
    }

    return output;
}

string infix_to_prefix(string expr) {
    string reversed = "";

    for (int i = (int)expr.length() - 1; i >= 0; i--) {
        if (expr[i] == '(')
            reversed += ')';
        else if (expr[i] == ')')
            reversed += '(';
        else
            reversed += expr[i];
    }

    string postfix = infix_to_postfix(reversed);
    string prefix = "";

    for (int i = (int)postfix.length() - 1; i >= 0; i--)
        prefix += postfix[i];

    while (!prefix.empty() && prefix[0] == ' ')
        prefix.erase(0, 1);

    while (!prefix.empty() && prefix.back() == ' ')
        prefix.pop_back();

    return prefix;
}

string postfix_to_infix(string expr) {
    Stack<string> values;
    string token = "";

    for (int i = 0; i <= (int)expr.length(); i++) {
        char c = (i == (int)expr.length()) ? ' ' : expr[i];

        if (!isspace((unsigned char)c)) {
            token += c;
        }
        else if (!token.empty()) {
            if (token.length() == 1 && isOperator(token[0])) {
                if (values.isEmpty())
                    return "Invalid postfix expression";

                string right = values.pop();

                if (values.isEmpty())
                    return "Invalid postfix expression";

                string left = values.pop();

                values.push("(" + left + " " + token +
                            " " + right + ")");
            }
            else {
                values.push(token);
            }

            token = "";
        }
    }

    if (values.isEmpty())
        return "Invalid postfix expression";

    string answer = values.pop();

    if (!values.isEmpty())
        return "Invalid postfix expression";

    return answer;
}

double evaluate_postfix(string expr) {
    Stack<double> values;
    string token = "";

    for (int i = 0; i <= (int)expr.length(); i++) {
        char c = (i == (int)expr.length()) ? ' ' : expr[i];

        if (!isspace((unsigned char)c)) {
            token += c;
        }
        else if (!token.empty()) {
            if (token.length() == 1 && isOperator(token[0])) {
                if (values.isEmpty()) return NAN;

                double b = values.pop();

                if (values.isEmpty()) return NAN;

                double a = values.pop();
                double result = 0;

                switch (token[0]) {
                    case '+': result = a + b; break;
                    case '-': result = a - b; break;
                    case '*': result = a * b; break;

                    case '/':
                        if (b == 0) return NAN;
                        result = a / b;
                        break;

                    case '^':
                        result = pow(a, b);
                        break;
                }

                values.push(result);
            }
            else {
                values.push(atof(token.c_str()));
            }

            token = "";
        }
    }

    if (values.isEmpty()) return NAN;

    double answer = values.pop();

    if (!values.isEmpty()) return NAN;

    return answer;
}

double evaluate_prefix(string expr) {
    Stack<double> values;
    string tokens[MAX_SIZE];
    int count = 0;
    string token = "";

    for (int i = 0; i <= (int)expr.length(); i++) {
        char c = (i == (int)expr.length()) ? ' ' : expr[i];

        if (!isspace((unsigned char)c)) {
            token += c;
        }
        else if (!token.empty()) {
            if (count >= MAX_SIZE)
                return NAN;

            tokens[count++] = token;
            token = "";
        }
    }

    for (int i = count - 1; i >= 0; i--) {
        token = tokens[i];

        if (token.length() == 1 && isOperator(token[0])) {
            if (values.isEmpty()) return NAN;

            double a = values.pop();

            if (values.isEmpty()) return NAN;

            double b = values.pop();
            double result = 0;

            switch (token[0]) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;

                case '/':
                    if (b == 0) return NAN;
                    result = a / b;
                    break;

                case '^':
                    result = pow(a, b);
                    break;
            }

            values.push(result);
        }
        else {
            values.push(atof(token.c_str()));
        }
    }

    if (values.isEmpty()) return NAN;

    double answer = values.pop();

    if (!values.isEmpty()) return NAN;

    return answer;
}

int main() {
    int choice;
    string expr;

    do {
        cout << "\n===== EXPRESSION CONVERTER =====\n";
        cout << "1. Infix to Postfix\n";
        cout << "2. Infix to Prefix\n";
        cout << "3. Postfix to Infix\n";
        cout << "4. Evaluate Postfix\n";
        cout << "5. Evaluate Prefix\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";

        cin >> choice;
        cin.ignore(10000, '\n');

        if (choice >= 1 && choice <= 5) {
            cout << "Enter expression: ";
            getline(cin, expr);
        }

        switch (choice) {
            case 1:
                cout << "Postfix: "
                     << infix_to_postfix(expr) << endl;
                break;

            case 2:
                cout << "Prefix: "
                     << infix_to_prefix(expr) << endl;
                break;

            case 3:
                cout << "Infix: "
                     << postfix_to_infix(expr) << endl;
                break;

            case 4:
                cout << "Result: "
                     << evaluate_postfix(expr) << endl;
                break;

            case 5:
                cout << "Result: "
                     << evaluate_prefix(expr) << endl;
                break;

            case 0:
                cout << "Program ended." << endl;
                break;

            default:
                cout << "Invalid choice." << endl;
        }

    } while (choice != 0);

    return 0;
}
