# 具体设计

## ImproperFraction类
构建一个ImproperFraction的类，然后重载这个类的四种运算 **+-x÷** 以及以及六种逻辑关系**'<'  '=='  '<='  '!='  '>'  '>='**判断，在后续的代码编写之中都是基于这个类进行运算

##### 核心代码如下：

```c++

	class ImproperFraction {
	 public :
	  ImproperFraction(){}
	  ImproperFraction (int Mole, int Deno, int Coef = 0) {
	    int g = std::__gcd (Mole, Deno);
	    g = std::max(g, 1);
	    mole = (Mole + Coef * Deno) / g;
	    deno = Deno / g;
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
	  int mole = 0; // 分子
	  int deno = 1; // 分母 
	};
```
## 题集的生成
##### 表达式的生成：
在这里选择的是rand() 随机生成 运算符个数，类型以及每个被运算的  	数值。
##### 表达式的合法性判断：
 在生成过程之中，有两个要点会导致表达式非法
1.运算过程中出现负值
2.在÷运算后面出现0

解决办法：
两个特殊判断即可
  
##### 表达式的去重：
表达式的重复有两种情况:
1.完完全全的重复，如出现两个1 + 2 + 3 的表达式
2.运算顺序上的重复，如:
>###### 1 + 2 + 3 和 2 + 1 + 3重复
>###### 2 + 3 x 4 和 4 x 3 + 2重复
                             
解决办法：
对于(1)的情况只需要将生成的表达式保存进C++STL的set之中即可自动去重。
对于(2)的情况，则是按照一定规则生成表达式来避免这一情况，规则如下：
>###### 1.默认左边的运算符的优先度高于右边
>###### 2.第一个数字一定不小于第二个数值
因此1 + 2 + 3和2 + 3 x 4不会被生成，而只会生成2 + 1 + 3和4 x 3 + 2
  
 ##### 题集无法生成要求的数量：
 例如：
传入的参数是 -n 10000 -r 1 的时候，很明显无法生成10000道题目，因此陷入死循环的生成中

解决方案：
设置一个时间戳time，当生成表达式的部分循环了1000000次之后自动跳出循环，终止生成表达式 
  
 ##### 答案的生成：
 在表的是合法性判断的时候，会判断最终的数值是否小于0，在这里就已经计算标准答案，保存并打印到answer.txt即可
##### 核心代码如下：

``` C++

	void questionSetGenerate (int limit, int number) {
	  std::set<std::string>expressions;
	  std::vector<std::string>exercise;
	  std::vector<ImproperFraction>answer;
	  ImproperFraction zero = ImproperFraction(0, 1);
	  int time = 0;
	  while (expressions.size() < number && time < 1000000) {
	    time ++;
	    int sz = expressions.size();
	    int opnumber = rand() % 3 + 1;
	    ImproperFraction a[5];
	    ImproperFraction res = ImproperFraction(0, 1);
	    const ImproperFraction zero = ImproperFraction(0, 1);
	    char op[4];
	    
	    for (int i = 0; i <= opnumber; i++) {
	      a[i] = ImproperFraction(rand() % (limit * limit), std::max(1, rand() % limit));
	      if (i) {
	        op[i] = oper[rand() % 4];
	      }
	    }
	    std::string exp = "";
	    bool flag = true;
	    if (a[0] < a[1]) {
	      std::swap (a[0], a[1]);
	    }
	
	    for (int i = 0; i <= opnumber; i++) {
	      if (i) {
	        if (op[i] == '+') {
	          res = res + a[i];
	        } else if (op[i] == '*') {
	          res = res * a[i];
	        } else if (op[i] == '-') {
	          res = res - a[i];
	        } else {
	          if (a[i] == zero) {
	            flag = false;
	            break;
	          }
	          res = res / a[i];
	        }
	        exp = exp + ' ';
	        exp = exp + op[i];
	        exp = exp + ' ';
	      } else {
	        res = res + a[i];
	      }
	      fractionToString(a[i], exp);
	      if (res < zero) {
	        flag = false;
	        break;
	      }
	    }
	    if (flag) {
	      expressions.insert(exp);
	      if (expressions.size() > sz) {
	        exercise.push_back(addbrackets(exp));
	        answer.push_back(res);
	      }
	    }
	  }
	}

```
 