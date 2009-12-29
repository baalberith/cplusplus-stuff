#include "bignums.h"
#include <sstream>
#include <iomanip>

using namespace std;

Bignum::Bignum(const string s) {
  minus = s[0] == '-' ? -1 : 1;
  
  string str;
  if (minus == -1) 
    str = s.substr(1);
  else str = s;
  int len = str.size();
  
  int n = len % DIGS == 0 ? len / DIGS : len / DIGS + 1;
  num.resize(n);
  
  for (int i = 0; i < n; i++) {
    num[i] = 0;
    for (int k = max(0, len - DIGS); k < len; k++)
      num[i] = 10 * num[i] + (str[k] - '0');
    len -= DIGS;
  }
}

Bignum::operator string() const {
  string str1 = minus == -1 ? "-" : "";
  
  ostringstream ostr;
  int n = num.size();
  ostr << num[n - 1]; 
  for (int i = n - 2; i >= 0; i--) 
    ostr << setw(DIGS) << setfill('0') << num[i];
  
  string str2 = ostr.str();
  return str1 + str2;
}

ostream & operator<<(ostream &s, const Bignum& b) {
  s << (string) b;
  return s;
}

istream & operator>>(istream &s, Bignum& b) {
  string str;
  s >> str;
  b = Bignum(str);
  return s;
}
