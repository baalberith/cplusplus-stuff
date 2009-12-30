#include "bignums.h"
#include <iostream>
#include <cassert>

using namespace std;

int main() {
  string s = "-9876543210123456789";
  assert(s == (string) Bignum(s));
  cout << Bignum(s) << endl;
  
  long long l = -1234567891011121314LL;
  assert(l == (long long) Bignum(l));
  cout << Bignum(l) << endl;
  
  Bignum b1, b2;
  char op;
  
  while (cin >> b1 >> op >> b2) {
    switch (op) {
      case '+' : 
        cout << b1 + b2 << endl;
        break;
      case '-' : 
        cout << b1 - b2 << endl;
        break;
      case '*' : 
        cout << b1 * b2 << endl;
        break;
    }
  }
  
  return 0;
}
