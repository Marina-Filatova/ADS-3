// Copyright 2021 NNTU-CS
#include <string>
#include "tstack.h"

int priority(char ch) {
switch (ch) {
case '(':return 0;
case ')':return 1;
case '+':return 2;
case '-':return 2;
case '*':return 3;
case '/':return 3;
default: return -1;
}
}

int vichisl(char operate, int num1, int num2) {
switch (operate) {
case '+': return num1 + num2;
break;
case '-': return num1 - num2;
break;
case '*': return num1 * num2;
break;
case '/': return num1 / num2;
break;
}
}

std::string infx2pstfx(std::string inf) {
std::string pst;
int i = 0;
char ch = inf[i];
char top = 0;
TStack <char> Stack;
while (ch) {
int prioritet;
prioritet = priority(ch);
if (prioritet > -1) {
if ((prioritet == 0) || (prioritet > priority(top) ||
Stack.isEmpty()) && ch != ')') {
if (Stack.isEmpty()) {
top = ch;
}
Stack.push(ch);
} else if (ch == ')') {
while (Stack.get() != '(') {
pst.push_back(Stack.get());
pst.push_back(' ');
Stack.pop();
}
Stack.pop();
if (Stack.isEmpty()) {
top = 0;
}
} else {
while (!Stack.isEmpty() && priority(Stack.get()) >= prioritet) {
pst.push_back(Stack.get());
pst.push_back(' ');
Stack.pop();
}
if (Stack.isEmpty()) {
top = ch;
}
Stack.push(ch);
}
} else {
pst.push_back(ch);
pst.push_back(' ');
}
ch = inf[++i];
}
while (!Stack.isEmpty()) {
pst.push_back(Stack.get());
pst.push_back(' ');
Stack.pop();
}
pst.erase(pst.end() - 1, pst.end());
return pst;
}

int eval(std::string pst) {
TStack <int> stack;
int i = 0, result = 0;
char ch = pst[i];
while (ch) {
if (ch >= '0' && ch <= '9') {
int chislo = 0;
int dec = 1;
while(ch != ' ') {
chislo = chislo + (ch - 48) * dec;
dec = dec * 10;
}
stack.push(chislo);
} else {
char operate = ch;
i++;
int number2 = stack.get();
stack.pop();
int number1 = stack.get();
stack.pop();
int result = vichisl(operate, number1, number2);
stack.push(result);
}
if (i < pst.size()) {
ch = pst[++i];
} else {
ch = 0;
}
}
result = stack.get();
stack.pop();
return result;
}
