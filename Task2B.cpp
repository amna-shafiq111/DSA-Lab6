#include <iostream>
#include <cstring>
using namespace std;

class TagStack {
private:
char tags[100][50];
int top;

public:
TagStack() {
top = -1;
}


bool isEmpty() {
    return top == -1;
}

bool push(const char tag[]) {
    if (top >= 99) {
        return false;
    }

    top++;

    int i = 0;
    while (tag[i] != '\0' && i < 49) {
        tags[top][i] = tag[i];
        i++;
    }
    tags[top][i] = '\0';

    return true;
}

bool pop(char result[]) {
    if (isEmpty()) {
        return false;
    }

    int i = 0;
    while (tags[top][i] != '\0') {
        result[i] = tags[top][i];
        i++;
    }
    result[i] = '\0';

    top--;
    return true;
}


};

bool isNameCharacter(char ch) {
return (ch >= 'a' && ch <= 'z') ||
(ch >= 'A' && ch <= 'Z') ||
(ch >= '0' && ch <= '9') ||
ch == '-' || ch == '_';
}

bool validateMarkup(const char text[]) {
TagStack stack;
int i = 0;


while (text[i] != '\0') {
    if (text[i] != '<') {
        i++;
        continue;
    }

    i++;

    if (text[i] == '\0') {
        return false;
    }

    bool closing = false;

    if (text[i] == '/') {
        closing = true;
        i++;
    }

    char tag[50];
    int length = 0;

    while (isNameCharacter(text[i])) {
        if (length >= 49) {
            return false;
        }

        tag[length++] = text[i++];
    }

    tag[length] = '\0';

    if (length == 0) {
        return false;
    }

    while (text[i] != '\0' && text[i] != '>') {
        i++;
    }

    if (text[i] != '>') {
        return false;
    }

    i++;

    if (closing) {
        char openingTag[50];

        if (!stack.pop(openingTag)) {
            return false;
        }

        if (strcmp(openingTag, tag) != 0) {
            return false;
        }
    } else {
        if (!stack.push(tag)) {
            return false;
        }
    }
}

return stack.isEmpty();


}

int main() {
char text[1000];


cout << "MARKUP VALIDATOR" << endl;
cout << "Enter markup text: ";
cin.getline(text, 1000);

if (validateMarkup(text)) {
    cout << "Result: Markup is valid" << endl;
} else {
    cout << "Result: Markup is invalid" << endl;
}

return 0;

}
