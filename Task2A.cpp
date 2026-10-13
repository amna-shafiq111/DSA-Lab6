
#include <iostream>
using namespace std;

class Stack {
private:
    char arr[1000];
    int top;

public:
    Stack() {
        top = -1;
    }

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == 999;
    }

    void push(char value) {
        if (isFull()) {
            cout << "Stack overflow!" << endl;
            return;
        }
        arr[++top] = value;
    }

    char pop() {
        if (isEmpty()) {
            return '\0';
        }
        return arr[top--];
    }

    char peek() {
        if (isEmpty()) {
            return '\0';
        }
        return arr[top];
    }
};

bool isMatchingPair(char opening, char closing) {
    return (opening == '(' && closing == ')') ||
           (opening == '[' && closing == ']') ||
           (opening == '{' && closing == '}');
}

bool validateBrackets(const char expression[]) {
    Stack s;

    for (int i = 0; expression[i] != '\0'; i++) {
        char ch = expression[i];

        if (ch == '(' || ch == '[' || ch == '{') {
            s.push(ch);
        }
        else if (ch == ')' || ch == ']' || ch == '}') {
            if (s.isEmpty()) {
                return false;
            }

            char opening = s.pop();

            if (!isMatchingPair(opening, ch)) {
                return false;
            }
        }
    }

    return s.isEmpty();
}

int main() {
    char expression[1000];

    cout << "BRACKET VALIDATOR" << endl;
    cout << "Enter an expression: ";
    cin.getline(expression, 1000);

    if (validateBrackets(expression)) {
        cout << "Result: Balanced brackets" << endl;
    }
    else {
        cout << "Result: Unbalanced brackets" << endl;
    }

    return 0;
}
