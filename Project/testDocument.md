为了保证程序的正确性和鲁棒性，我们进行了大量的测试，具体如下：
1. 合法参数有4个，即-n, -r, -e, -a, 当没有输入参数时，应报错：
`./a.out`

2. 当输入的参数不存在时，应报错：
`./a.out -b`

2. 当参数输入组合不合法时，应该报错并给出帮助信息：
`./a.out -n 100`
`./a.out -r 100`
`./a.out -e exercisefile.txt`
`./a.out -a answerfile.txt`
`./a.out -n 100 -e exercisefile.txt`
`./a.out -n 100 -a answer.txt`
`./a.out -r 100 -e exercisefile.txt`
`./a.out -r 100 -a answer.txt`
`./a.out -n 100 -r 100 -e exercisefile.txt -a answer.txt`

3. 当输入了-n和-r参数，但参数后面接的内容不合法时，应该报错：
`./a.out -n 100 -r k10`

4. 当输入了-e和-a参数，但参数后面接的文件不存在或无访问权限时，应该报错：
`./a.out -e illegal.txt -a answerfile.txt`

5. 当-n和-r参数搭配不合法的时候，应该报错：
`./a.out -n 10000 -r 1`
显然，当题目中的数值最大为1时，是不足以生成10000道题目的。

6. 模块：测试生成的题目计算过程不产生负数

7. 模块：测试生成的题目运算符个数不超过3个

8. 模块：测试生成的题目不重复

10. 模块：测试给定一条计算四则运算结果的正确性
