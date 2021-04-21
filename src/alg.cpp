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
}
}

int vichisl(char operate, int num1, int num2) {
switch (operate) {
case ('+'): return num1 + num2;
break;
case('-'): return num1 - num2;
break;
case('*'): return num1 * num2;
break;
case('/'): return num1 / num2;
break;
}
}

std::string infx2pstfx(std::string inf) {
std::string pstfx;
int i = 0;
char ch = inf[0];
char top = 0;
TStack <char> StackChar;
while (ch) {
int prioritet;
prioritet = priority(ch);
if (prioritet > -1) {
if ((prioritet == 0) || (prioritet > priority(top)
|| StackChar.isEmpty()) && ch != ')') {
if (StackChar.isEmpty()) {
top = ch;
}
StackChar.push(ch);
} else if (ch == ')') {
while (StackChar.get() != '(') {
pstfx.push_back(StackChar.get());
pstfx.push_back(' ');
StackChar.pop();
}
StackChar.pop();
if (StackChar.isEmpty()) {
top = 0;
}
} else {
while ((StackChar.isEmpty() != 0) && (priority(StackChar.get()) >= prioritet)) {
pstfx.push_back(StackChar.get());
pstfx.push_back(' ');
StackChar.pop();
}
if (StackChar.isEmpty()) {
top = ch;
}
StackChar.push(ch);
}
} else {
pstfx.push_back(ch);
pstfx.push_back(' ');
}
ch = inf[++i];
}
while (!StackChar.isEmpty()) {
pstfx.push_back(StackChar.get());
pstfx.push_back(' ');
StackChar.pop();
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
