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
std::string pstfx;
int i = 0;
char x = inf[i];
char tem = 0;
TStack <char> stackChar;
while (x) {
int pr;
pr = priority(x);
if (pr > -1) {
if ((pr == 0 || pr > priority(tem) ||
stackChar.isEmpty()) && x != ')') {
if (stackChar.isEmpty())
tem = x;
stackChar.push(x);
} else if (x == ')') {
while (stackChar.get() != '(') {
pstfx.push_back(stackChar.get());
pstfx.push_back(' ');
stackChar.pop();
}
stackChar.pop();
if (stackChar.isEmpty())
tem = 0;
} else {
while (!stackChar.isEmpty() &&
priority(stackChar.get()) >= pr) {
pstfx.push_back(stackChar.get());
pstfx.push_back(' ');
stackChar.pop();
}
if (stackChar.isEmpty())
tem = x;
stackChar.push(x);
}
} else {
pstfx.push_back(x);
pstfx.push_back(' ');
}
x = inf[++i];
}
while (!stackChar.isEmpty()) {
pstfx.push_back(stackChar.get());
pstfx.push_back(' ');
stackChar.pop();
}
pstfx.erase(pstfx.end() - 1, pstfx.end());
return pstfx;
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
