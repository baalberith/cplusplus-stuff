#ifndef _bignums_h_
#define _bignums_h_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Bignum {
  private:
    static const int BASE = 1000000000;
    static const int DIGS = 9;
    vector<int> num;
    int minus;
  public:
    Bignum(const string s);
    operator string() const;
    friend ostream& operator<<(ostream &s, const Bignum& bi);
    friend istream& operator>>(istream &s, Bignum& bi);
};

#endif
    