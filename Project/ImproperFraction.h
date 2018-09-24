#ifndef IMPROPERFRACTION_H_INCLUDED
#define IMPROPERFRACTION_H_INCLUDED
#include <algorithm>
#include <stdio.h>
using namespace std;

class ImproperFraction {
 public :
  void init (int mole, int deno, int coef = 0) {
    int g = __gcd (mole, deno);
    this -> mole = (mole + coef * deno) / g;
    this -> deno = deno / g;
  }
  void out () {
    int coef = mole / deno;
    if (coef != 0) {
      printf ("%d\'", a);
      if (mole % deno) {
        printf ("%d/%d", mole % deno, deno);
      }
    } else if (mole % deno) {
      printf ("%d/%d", mole % deno, deno);
    } else {
      putchar ('0');
    }
    putchar (" ");
  }
  ImproperFraction operator + (const ImproperFraction & rhs ) const {
    int DENO = deno * rhs.deno;
    int MOLE = mole * rhs.deno + rhs.mole * deno;
    ImproperFraction res;
    res.init (MOLE, NENO);
    return res;
  }
  ImproperFraction operator - (const ImproperFraction & rhs ) const {
    int DENO = deno * rhs.deno;
    int MOLE = mole * rhs.deno - rhs.mole * deno;
    ImproperFraction res;
    res.init (MOLE, NENO);
    return res;
  }
  ImproperFraction operator * (const ImproperFraction & rhs ) const {
    int DENO = deno * rhs.deno;
    int MOLE = mole * rhs.mole;
    ImproperFraction res;
    res.init (MOLE, NENO);
    return res;
  }
  ImproperFraction operator / (const ImproperFraction & rhs ) const {
    int DENO = deno * rhs.mole;
    int MOLE = mole * rhs.deno;
    ImproperFraction res;
    res.init (MOLE, NENO);
    return res;
  }
  bool operator < (const ImproperFraction & rhs ) const {
    return mole * rhs.deno < rhs.mole * deno;
  }
  bool operator == (const ImproperFraction & rhs ) const {
    return mole * rhs.deno == rhs.mole * deno;
  }
  bool operator <= (const ImproperFraction & rhs ) const {
    return (*this) < rhs || (*this) == rhs;
  }
  bool operator > (const ImproperFraction & rhs ) const {
    return !((*this) <= rhs);
  }
  bool operator >= (const ImproperFraction & rhs ) const {
    return (*this) > rhs || (*this) == rhs;
  }

 private :
  int mole = 0; // ·Ö×Ó
  int deno = 1; // ·ÖÄ¸
};


#endif // IMPROPERFRACTION_H_INCLUDED
