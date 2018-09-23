#ifndef IMPROPERFRACTION_H_INCLUDED
#define IMPROPERFRACTION_H_INCLUDED
class ImproperFraction {
 public :
  void init (int mole, int deno) {
  	//可能还需要求一下gcd
    this -> mole = mole;
    this -> deno = deno;
  }
  void out () {

  }
  ImproperFraction operator + (const ImproperFraction & rhs ) const {
    ImproperFraction res;

    return res;
  }
  ImproperFraction operator - (const ImproperFraction & rhs ) const {
    ImproperFraction res;

    return res;
  }
  ImproperFraction operator * (const ImproperFraction & rhs ) const {
    ImproperFraction res;

    return res;
  }
  ImproperFraction operator / (const ImproperFraction & rhs ) const {
    ImproperFraction res;

    return res;
  }
  bool operator < (const ImproperFraction & rhs ) const {
    return true;
  }
  bool operator = (const ImproperFraction & rhs ) const {
    return true;
  }
  bool operator > (const ImproperFraction & rhs ) const {
    return true;
  }
  bool operator <= (const ImproperFraction & rhs ) const {
    return true;
  }
  bool operator >= (const ImproperFraction & rhs ) const {
    return true;
  }

 private :
  int mole = 0; // 分子
  int deno = 1; // 分母
};


#endif // IMPROPERFRACTION_H_INCLUDED
