#ifndef IMPROPERFRACTION_H_INCLUDED
#define IMPROPERFRACTION_H_INCLUDED
#include <algorithm>
#include <stdio.h>

class ImproperFraction {
 public :
  ImproperFraction (int Mole, int Deno, int Coef = 0) {
    int g = std::__gcd (Mole, Deno);
    g = std::max(g, 1);
    mole = (Mole + Coef * Deno) / g;
    deno = Deno / g;
  }
  void out () {
    int coef = mole / deno;
    if (coef != 0) {
      printf ("%d", coef);
      if (mole % deno) {
        printf ("\'%d/%d", mole % deno, deno);
      }
    } else if (mole % deno) {
      printf ("%d/%d", mole % deno, deno);
    } else {
      putchar ('0');
    }
    putchar (' ');
  }
  int getdeno () {
    return deno;
  }
  int getmole () {
    return mole;
  }

  ImproperFraction operator + (const ImproperFraction & rhs ) const {
    int DENO = deno * rhs.deno;
    int MOLE = mole * rhs.deno + rhs.mole * deno;
    ImproperFraction res = ImproperFraction (MOLE, DENO);
    return res;
  }
  ImproperFraction operator - (const ImproperFraction & rhs ) const {
    int DENO = deno * rhs.deno;
    int MOLE = mole * rhs.deno - rhs.mole * deno;
    ImproperFraction res = ImproperFraction (MOLE, DENO);
    return res;
  }
  ImproperFraction operator * (const ImproperFraction & rhs ) const {
    int DENO = deno * rhs.deno;
    int MOLE = mole * rhs.mole;
    ImproperFraction res = ImproperFraction (MOLE, DENO);
    return res;
  }
  ImproperFraction operator / (const ImproperFraction & rhs ) const {
    int DENO = deno * rhs.mole;
    int MOLE = mole * rhs.deno;
    ImproperFraction res = ImproperFraction (MOLE, DENO);
    return res;
  }
  bool operator < (const ImproperFraction & rhs ) const {
    return mole * rhs.deno < rhs.mole * deno;
  }
  bool operator == (const ImproperFraction & rhs ) const {
    return mole * rhs.deno == rhs.mole * deno;
  }
  bool operator != (const ImproperFraction & rhs ) const {
    return !(mole * rhs.deno == rhs.mole * deno);
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
