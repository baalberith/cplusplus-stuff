#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int BASE = 1000000000; 
const int DIGS = 9;
const int LEN = 1000; 

class liczba {
  private:
    int t[LEN];
    int l; 
    
  public:
    void wypisz() {
      printf("%d", t[l - 1]);
      for (int i = l - 2; i >= 0; i--)
        printf("%0*d", DIGS, t[i]);
    }
    
    void czytaj() {
      char s[LEN * DIGS + 1];
      scanf("%s", s); 
      int j = strlen(s); 
      if (j % DIGS == 0)
        l = j / DIGS;
      else
        l = j / DIGS + 1;
      j--;
      for (int i = 0; i < l; i++) {
        t[i] = 0;
        for (int k = max(0, j - DIGS + 1); k <= j; k++)
            t[i] = 10 * t[i] + (s[k] - '0');
        j -= DIGS;
      }
    }
    
    liczba operator+ (liczba y) {
      liczba z; 
      z.l = min(l, y.l);
      int c = 0; 
      for (int i = 0; i < z.l; i++) {
        z.t[i] = (t[i] + y.t[i] + c) % BASE;
        c = (t[i] + y.t[i] + c) / BASE;
      }
      while (z.l < l) {
        z.t[z.l] = (t[z.l] + c) % BASE;
        c = (t[z.l] + c) / BASE;
        z.l++;
      }
      while (z.l < y.l) {
        z.t[z.l] = (y.t[z.l] + c) % BASE;
        c = (y.t[z.l] + c) / BASE;
        z.l++;
      }
      if (c > 0) {
        z.t[z.l] = c;
        z.l++;
      }
      return z;
    }
    
    liczba operator- (liczba y) {
      liczba z; 
      z.l = l;
      int c = 0; 
      for (int i = 0; i < l; i++) {
        if (i < y.l) 
          z.t[i] = t[i] - y.t[i] + c;
        else 
          z.t[i] = t[i] + c;
        if (z.t[i] < 0) {
          z.t[i] += BASE;
          c = -1;
        } else c = 0;
      }
      while (z.l > 1 && z.t[z.l - 1] == 0)
        z.l--;
      return z;
    }
    
    bool operator< (liczba y) {
      if (l < y.l)
        return true;
      if (l > y.l)
        return false;
      int i = l - 1;
      while (i >= 0 && t[i] == y.t[i])
        i--;
      if (i < 0)
        return false;
      if (t[i] < y.t[i])
        return true;
      return false;
    }
    
    bool operator> (liczba y) {
      return y < *this;
    }

    bool operator== (liczba y) {
      return !(*this < y) && !(y < *this);
    }
    
    liczba operator* (int y) {
      liczba z;
      z.l = l;
      int c = 0;
      for (int i = 0; i < l; i++) {
        z.t[i] = int(((long long)(t[i]) * y + c) % BASE);
        c = int(((long long)(t[i]) * y + c) / BASE);
      }
      while (c > 0) {
        z.t[z.l] = c % BASE;
        c /= BASE;
        z.l++;
      }
      return z;
    }
    
    liczba operator* (liczba y) {
      liczba z, zero;
      zero.l = 1; 
      zero.t[0] = 0;
      z = zero;
      liczba xx, yy;
      xx = *this;
      yy = y;
      while (yy > zero) {
        if (yy % 2 == 1)
          z = z + xx;
        xx = xx * 2;
        yy = yy / 2;
      }
      return z;
    }
    
    int operator% (int y) {
      long long z = (long long)(t[l - 1]) % y;
      for (int i = l - 2; i >= 0; i--)
        z = (z * BASE + t[i]) % y;
      return int(z);
    }
    
    liczba operator/ (int y) {
      liczba z;
      int c = 0; 
      z.l = l;
      for (int i = l - 1; i >= 0; i--) {
        z.t[i] = int(((long long)(c) * BASE + (long long)t[i]) / y);
        c = int(((long long)(c) * BASE + (long long)t[i]) % y);
      }
      while (z.l > 1 && z.t[z.l - 1] == 0)
        z.l--;
      return z;
    }
    
    liczba operator/ (liczba y) {
      liczba pom, z;
      z.l = l - y.l + 1;
      if (z.l <= 0) {
        z.l = 1;
        z.t[0] = 0;
        return z;
      }
      pom.l = y.l;
      for (int i = 0; i < pom.l; i++)
        pom.t[pom.l - i - 1] = t[l - 1 - i];
      int i = l - y.l;
      while (i >= 0) {
        int a = 0;
        int b = BASE - 1;
        while (a < b) {
          int c = (a + b) / 2 + 1;
          if (y * c > pom)
            b = c - 1;
          else
            a = c;
        }
        z.t[i] = a;
        pom = pom - (y * a);
        for (int j = pom.l - 1; j >= 0; j--)
          pom.t[j + 1] = pom.t[j];
        pom.l++;
        i--;
        if (i >= 0)
          pom.t[0] = t[i];
      }
      while (z.l > 1 && z.t[z.l - 1] == 0)
        z.l--;
      return z;
    }
    
    liczba operator% (liczba y) {
      return *this - (y * (*this / y));
    }
};

int main() {
  liczba l1, l2, l3;
  l1.czytaj();
  l2.czytaj();
  l3 = l1 / l2;
  l3.wypisz();
  
  return 0;
}
