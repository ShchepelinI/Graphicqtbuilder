#ifndef POLAND_H
#define POLAND_H

#endif // POLAND_H

#include <cmath>

using namespace std;

struct Stack {
    long double num;
    char sign;
    Stack *next;
};

void push(Stack *&top, long double num, char sign) {
    Stack *p = (Stack *) malloc(sizeof(Stack));
    p->num = num;
    p->sign = sign;
    p->next = top;
    top = p;
}

Stack pop(Stack *&top) {
    Stack temp = *top;
    top = top->next;
    return temp;
}

int prior(char a) {
    if (a == '(') return 0;
    if (a == '+' || a == '-') return 1;
    if (a == '*' || a == '/') return 2;
    if (a == '^') return 3;
    if (a == 'S' || a == 'C' || a == 'T' || a == 'Q' || a == 'L' || a == 'A') return 4;
    return -1;
}

bool apply(Stack *&top1, char sign) {
    long double b;
    long double a;
    if (top1 != nullptr) b = pop(top1).num;
    else
        return true;

    if (prior(sign) != 4) {
        if (top1 != nullptr)
            a = pop(top1).num;
        else
            return true;
    }

    if (sign == '+') push(top1, a + b, '@');
    else if (sign == '-') push(top1, a - b, '@');
    else if (sign == '*') push(top1, a * b, '@');
    else if (sign == '/' && b != 0) push(top1, a / b, '@');
    else if (sign == '^') push(top1, pow(a, b), '@');
    else if (sign == 'S') push(top1, sin(b), '@');
    else if (sign == 'C') push(top1, cos(b), '@');
    else if (sign == 'T') push(top1, tan(b), '@');
    else if (sign == 'L' && b > 0) push(top1, log(b), '@');
    else if (sign == 'Q' && b >= 0) push(top1, sqrt(b), '@');
    else if (sign == 'A') push(top1, fabs(b), '@');
    else
        return true;
    return false;
}
Stack *top1 = nullptr;
Stack *top2 = nullptr;

bool calculate (string s, double & rez) {

    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '-' && !('0' <= s[i - 1] && s[i - 1] <= '9' || s[i - 1] == ')'))
            s.insert(i, "0");
    }

    Stack *top3 = nullptr;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') {
            push(top3, 0.0, s[i]);
        } else if (s[i] == ')' && s[i - 1] != '(' && top3 != nullptr) {
            pop(top3);
        } else if (s[i] == ')') {
            return false;
        }
    }
    if (top3 != nullptr) {
        return false;
    }

    string f = "";
    for (int i = 0; i < s.size(); i++) {
        while ('a' <= s[i] && s[i] <= 'z') {
            f += s[i];
            s[i] = ' ';
            i++;
        }
        if (f == "sin") {
            s[i - 1] = 'S';
        } else if (f == "cos") {
            s[i - 1] = 'C';
        } else if (f == "tg") {
            s[i - 1] = 'T';
        } else if (f == "sqrt") {
            s[i - 1] = 'Q';
        } else if (f == "ln") {
            s[i - 1] = 'L';
        } else if (f == "abs") {
            s[i - 1] = 'A';
        } else if (f != "") {
            return false;
        }
        f = "";
    }

    for (int i = 0; i < s.size() - 1; i++) {
        if (prior(s[i]) > 0 && prior(s[i + 1]) > 0) {
            return false;
        }
    }
    if ((prior(s[0]) > 0) && prior(s[0]) != 4) {
        return false;
    }

    for (int i = 0; i < s.size(); i++) {
        if ('0' <= s[i] && s[i] <= '9' || s[i] == '.') {
            string ss = "";
            while ('0' <= s[i] && s[i] <= '9' || s[i] == '.') {
                ss += s[i];
                i++;
            }
            double r = stod(ss);
            push(top1, r, '@');
        }
        if (s[i] == '(') {
            push(top2, 0.0, s[i]);
        } else if (s[i] == ')') {
            while (top2->sign != '(') {
                if (apply(top1, pop(top2).sign)) {
                    return false;
                }
            }
            pop(top2);
        } else if (0 <= prior(s[i])) {
            while (top2 != nullptr && prior(top2->sign) >= prior(s[i])) {
                if (apply(top1, pop(top2).sign)) {
                    return false;
                }
            }
            push(top2, 0.0, s[i]);
        }
    }


    while (top2 != nullptr) {
        if (apply(top1, pop(top2).sign)) {
            return false;
        }
    }

    rez = pop(top1).num;
    //cout << fixed << setprecision(6) << pop(top1).num << '\n';
    return true;
}
