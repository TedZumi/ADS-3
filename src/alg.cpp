// Copyright 2021 NNTU-CS
#include <string>
#include "tstack.h"

int priority(char ch) {
  switch (ch) {
    case '(' : return 0;
    case ')' : return 1;
    case '+' : return 2;
    case '-' : return 2;
    case '*' : return 3;
    case '/' : return 3;
    default: return -1;
  }
}

std::string infx2pstfx(std::string inf) {
  TStack<char> stack1;
  std::string str = "";
  for (int i = 0; i < inf.size(); i++) {
    char ch = inf[i];
    int k = priority(ch);
    if (k == -1) {
      str.push_back(ch);
      str.push_back(' ');
    } else {
      if (stack1.isEmpty() || k == 0 || k > priority(stack1.get())) {
        stack1.push(ch);
      } else {
        if (ch == ')') {
          while (true) {
            char sym = stack1.get();
            stack1.pop();
            if (sym != '(') {
              str.push_back(sym);
              str.push_back(' ');
            } else {
              break;
            }
          }
        } else {
          while (!stack1.isEmpty()) {
            char lastStackEl = stack1.get();
            stack1.pop();
            if (priority(lastStackEl) >= k) {
              str.push_back(lastStackEl);
              str.push_back(' ');
            }
          }
          stack1.push(ch);
        }
      }
    }
  }
  while (!stack1.isEmpty()) {
    char lastStackEl = stack1.get();
    stack1.pop();
    str.push_back(lastStackEl);
    str.push_back(' ');
  }
  return str;
}

int calc(int k1, int k2, char ch) {
  switch (ch) {
    case '+': {
      return k1 + k2;
      break;
    }
    case '-': {
      return k1 - k2;
      break;
    }
    case '*': {
      return k1 * k2;
      break;
    }
    case '/': {
      return k1 / k2;
      break;
    }
    default: {
      return -1;
      break;
    }
  }
}

int eval(std::string pst) {
  TStack<int> stack2;
  for (int i = 0; i < pst.size(); i++) {
    char ch = pst[i];
    if (ch == ' ') {
      continue;
    }
    int prior = priority(ch);
    if (prior == -1) {
      stack2.push(ch - 48);
    } else {
      int k1 = stack2.get();
      stack2.pop();
      int k2 = stack2.get();
      stack2.pop();
      int result = calc(k2, k1, ch);
      stack2.push(result);
    }
  }
  return stack2.get();
}
