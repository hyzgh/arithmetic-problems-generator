#ifndef IMPROPERFRACTION_H_INCLUDED
#define IMPROPERFRACTION_H_INCLUDED
class ImproperFraction {
 public :
  void init (int mole, int deno) {
  	//���ܻ���Ҫ��һ��gcd
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
  int mole = 0; // ����
  int deno = 1; // ��ĸ
};


#endif // IMPROPERFRACTION_H_INCLUDED
