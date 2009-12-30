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
    bool alesser(const Bignum& b) const;
    bool aequal(const Bignum& b) const;
    bool agreater(const Bignum& b) const;
    Bignum aplus(const Bignum& b) const;
    Bignum aminus(const Bignum& b) const;
    Bignum aimul(const int x) const;
    int aimod(const int x) const;
    Bignum aidiv(const int x) const;
    Bignum amultiply(const Bignum& b) const;
  public:
    Bignum();
    Bignum(const Bignum& b);
    Bignum& operator= (const Bignum& b);
    Bignum(const string s);
    Bignum(const long long x);
    operator string() const;
    operator long long() const;
    bool operator< (const Bignum& b) const;
    bool operator> (const Bignum& b) const;
    bool operator== (const Bignum& b) const;
    Bignum operator+ (const Bignum& b) const;
    Bignum& operator+= (const Bignum& b);
    Bignum operator- () const;
    Bignum operator- (const Bignum& b) const;
    Bignum& operator-= (const Bignum& b);
    Bignum operator* (const Bignum& b) const;
    friend ostream& operator<< (ostream &s, const Bignum& b);
    friend istream& operator>> (istream &s, Bignum& b);
};

#endif
