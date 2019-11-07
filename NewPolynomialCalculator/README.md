# 数据结构与算法实验项目1 一元稀疏多项式计算器

## 【问题描述】

  设计一个一元稀疏多项式简单计算器。

## 【实现要求】

  一元稀疏多项式简单计算器的基本功能是：

(1) 输入并建立多项式。

1. 输入并建立多项式。
2. 输出多项式,输出形式为整数序列：$n,c_1,e_1,c_2,e_2,...,c_n,e_n$
3. 多项式_a_和_b_相加，建立多项式_a+b_。
4. 多项式_a_和_b_相减，建立多项式_a-b_。
5. 计算多项式在_x_处的值。
6. 求多项式_a_的导函数_a'_。
7. 多项式_a_和_b_相乘，建立乘积多项式_ab_。
8. 加分项: 在前几点的基础上进行拓展创新，如计算器的仿真界面，拓展功能，个性设计等。

## 【测试数据】

1. $(2x+5x^{8}-3.1x^{11})+(7-5x^{8}+11x^{9})=(-3.1x^{11}+11x^{9}+2x+7)$
2. $(6x^{-3}-x+4.4x^{2}-1.2x^{9})-(-6x^{-3}+5.4x^{2}-x^{2}+7.8x^{15})=(-7.8x^{15}-1.2x^{9}+12x^{-3}-x)$
3. $(1+x+x^{2}+x^{3}+x^{4}+x^{5}+x^{6})+(-x^{3}-x^{4})=(1+x+x^{2}+x^{5})$
4. $(x+x^{3})+(-x-x^{3})=0$
5. $(x+x^{100})+(x^{100}+x^{200})=(x+2x^{100}+x^{200})$
6. $(x+x^{2}+x^{3})+0=x+x^{2}+x^{3}$

## 【实现提示】

  思路：用带头结点的单链表或顺序表的方式存储多项式，并自定义输入和输出的表示形式。可尝试采用多种数据结构形式实现。

## 【检查时间和要求】

  2019 学年秋季学期第 5 周实验课（2019 年9 月23 日）。
  
  评分要求：功能实现(50%)，程序输入界面(30%)，代码规范(20%)。