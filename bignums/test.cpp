#include "bignums.h"
#include <iostream>
#include <cassert>

using namespace std;

int main() {
  string s = "9876543210123456789";
  assert(s == (string) Bignum(s));
  cout << Bignum(s) << endl;
  
  return 0;
}
