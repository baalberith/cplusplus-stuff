#include "bignums.h"

#include <sstream>
#include <iomanip>

using namespace std;

bool Bignum::alesser(const Bignum& b) const {
  int n1 = num.size();
  int n2 = b.num.size();
  
  if (n1 < n2)
    return true;
  else if (n1 > n2)
    return false;
  
  int i = n1 - 1;
  
  while (i >= 0 && num[i] == b.num[i])
    i -= 1;
  
  if (i < 0)
    return false;
  
  if (num[i] < b.num[i])
    return true;
  else
    return false;
}

bool Bignum::aequal(const Bignum& b) const {
  return !(*this).alesser(b) && !b.alesser(*this);
}

bool Bignum::agreater(const Bignum& b) const {
  return b.alesser(*this);
}

Bignum Bignum::aplus(const Bignum& b) const {
  int n1 = num.size();
  int n2 = b.num.size();
  
  Bignum res;
  res.num.resize(max(n1, n2));
  
  int n = min(n1, n2);
  int r = 0;
  
  for (int i = 0; i < n; i++) {
    res.num[i] = (num[i] + b.num[i] + r) % BASE;
    r = (num[i] + b.num[i] + r) / BASE;
  }
  
  while (n < n1) {
    res.num[n] = (num[n] + r) % BASE;
    r = (num[n] + r) / BASE;
    n++;
  }
  
  while (n < n2) {
    res.num[n] = (b.num[n] + r) % BASE;
    r = (b.num[n] + r) / BASE;
    n++;
  }
  
  if (r > 0) {
    res.num[n] = r;
    n++;
  }
  
  res.num.resize(n);
  
  return res;
}

Bignum Bignum::aminus(const Bignum& b) const {
  int n1 = num.size();
  int n2 = b.num.size();
  
  Bignum res;
  res.num.resize(n1);
  
  int n = n1;
  int r = 0;
  
  for (int i = 0; i < n1; i++) {
    if (i < n2)
      res.num[i] = num[i] - b.num[i] + r;
    else
      res.num[i] = num[i] + r;
    
    if (res.num[i] < 0) {
      res.num[i] += BASE;
      r = -1;
    } else r = 0;
  }
  
  while (n > 1 && res.num[n - 1] == 0)
    n--;
  
  res.num.resize(n);
  
  return res;
}

Bignum Bignum::aimul(const int x) const {
  int n1 = num.size();
  
  Bignum res;
  res.num.resize(n1 + DIGS);
  
  int n = n1;
  int r = 0;
  
  for (int i = 0; i < n1; i++) {
    res.num[i] = ((long long)(num[i]) * x + r) % BASE;
    r = ((long long)(num[i]) * x + r) / BASE;
  }
  
  while (r > 0) {
    res.num[n] = r % BASE;
    r = r / BASE;
    n++;
  }
  
  res.num.resize(n);
  
  return res;
}

int Bignum::aimod(const int x) const {
  int n1 = num.size();
  
  long long y = (long long)(num[n1 - 1]) % x;
  
  for (int i = n1 - 2; i >= 0; i--) 
    y = (y * BASE + num[i]) % x; 
    
  return y;
}

Bignum Bignum::aidiv(const int x) const {
  int n1 = num.size();
  
  Bignum res;
  res.num.resize(n1);
  
  int n = n1;
  int r = 0;
  
  for (int i = n1 - 1; i >= 0; i--) {
    res.num[i] = ((long long)(r) * BASE + (long long)(num[i])) / x;
    r = ((long long)(r) * BASE + (long long)(num[i])) % x;
  }
  
  while (n > 1 && res.num[n - 1] == 0)
    n -= 1;
  
  res.num.resize(n);
  
  return res;
}

Bignum Bignum::amultiply(const Bignum& b) const {
  int n1 = num.size();
  int n2 = b.num.size();
  
  Bignum res, zero(0);
  res.num.resize(n1 + n2);
  
  Bignum b1(*this), b2(b);
  res.num[0] = 0;
  
  while (b2.agreater(zero)) {
    if (b2.aimod(2) == 1) 
      res = res.aplus(b1);
    b1 = b1.aimul(2);
    b2 = b2.aidiv(2);
  }
  
  int n = res.num.size();
  while (n > 1 && res.num[n - 1] == 0)
    n--;
  res.num.resize(n);
  
  return res;
}

Bignum::Bignum() {
  minus = 0;
}

Bignum::Bignum(const Bignum& b) {
  num.assign(b.num.begin(), b.num.end());
  minus = b.minus;
}

Bignum& Bignum::operator= (const Bignum& b) {
  if (this != &b) {
    num.assign(b.num.begin(), b.num.end());
    minus = b.minus;
  }
  return *this;
}

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

Bignum::Bignum(const long long x) {
  ostringstream ostr;
  ostr << x;
  *this = Bignum(ostr.str());
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

Bignum::operator long long() const {
  int n = num.size();
  long long x = 0;
  for (int i = n - 1; i >= 0; i--) 
    x = BASE * x + num[i];
  return minus * x;
}

bool Bignum::operator< (const Bignum& b) const {
  int m1 = minus;
  int m2 = b.minus;
  
  bool comp;
  
  if (m1 == 1 && m2 == 1)
    comp = (*this).alesser(b);
  else if (m1 == -1 && m2 == -1) {
    comp = (*this).alesser(b);
    if (!(*this).aequal(b))
      comp = !comp;
  }
  else if (m1 == 1 && m2 == -1)
    comp = false;
  else if (m1 = -1 && m2 == 1)
    comp = true;
  
  return comp;
}

bool Bignum::operator> (const Bignum& b) const {
  return b < *this;
}

bool Bignum::operator== (const Bignum& b) const {
  return !(*this < b) && !(*this > b);
}

Bignum Bignum::operator+ (const Bignum& b) const {
  int m1 = minus;
  int m2 = b.minus;
  
  Bignum res;
  
  if (m1 == 1 && m2 == 1) {
    res = (*this).aplus(b);
    res.minus = 1;
  }
  else if (m1 == -1 && m2 == -1) {
    res = (*this).aplus(b);
    res.minus = -1;
  }
  else if (m1 == 1 && m2 == -1) {
    if ((*this).alesser(b)) {
      res = b.aminus(*this);
      res.minus = -1;
    }
    else {
      res = (*this).aminus(b);
      res.minus = 1;
    }
  }
  else {
    if (b.alesser(*this)) {
      res = (*this).aminus(b);
      res.minus = -1;
    }
    else {
      res = b.aminus(*this);
      res.minus = 1;
    }
  }
  
  return res;
}

Bignum& Bignum::operator+= (const Bignum& b) {
  *this = *this + b;
  return *this;
}

Bignum Bignum::operator- () const {
  Bignum res(*this);
  res.minus = (-1) * minus;
  return res;
}

Bignum Bignum::operator- (const Bignum& b) const {
  return (*this) + (-b);
}

Bignum& Bignum::operator-= (const Bignum& b) {
  *this = *this - b;
  return *this;
}

Bignum Bignum::operator* (const Bignum& b) const {
  int m1 = minus;
  int m2 = b.minus;
  
  Bignum res = (*this).amultiply(b);
  
  int m = m1 * m2;
  if (*this == Bignum(0) || b == Bignum(0)) m = 1;
  res.minus = m;
  
  return res;
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
