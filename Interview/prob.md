[toc]

## 相关企业

1. [experience22-京东.md](experience22-京东.md)
2. [experience21-bat面试题.md]( experience21-bat面试题.md )
3. [experience27-微软算法.md](experience27-微软算法.md)

## 问题

1. ②：第二轮面试略简单，第一个题目是概率题，给你2K+1个硬币，问扔完之后正面比反面多的概率是多少。

答案：1/2

设反面出现的次数为 $i$，则所求概率为

$$
\begin{aligned}
p &= \sum_{i=1}^k  \tbinom{2k+1}{i} \left( \frac{1}{2} \right)^i \left( \frac{1}{2} \right)^{2k+1-i} \\ 
&= \left( \frac{1}{2} \right)^{2k+1} \sum_{i=1}^k  \tbinom{2k+1}{i} 
\end{aligned}
$$

而 

$$
\sum_{i=1}^k  \tbinom{2k+1}{i}  = \frac{1}{2} \sum_{i=1}^{2k+1}  \tbinom{2k+1}{i}  = \frac{1}{2}  2^{2k+1} =  2^{2k}
$$

所以

$$
p = \left( \frac{1}{2} \right)^{2k+1} 2^{2k} =  \frac{1}{2}
$$

2. 信息流的抽样
    方法是抽取到第 k 个数的时间，以 1/k 的概率选择。
相关企业： 
    1. [experience21-bat面试题.md]( experience21-bat面试题.md ) 信息流采样，有n份数据，但是n的长度并不知道，设计一个采样算法，使得每份被选择的概率是相同的。

3. 模型融合的时候，如果每个分类器正确率为0.5，投票法能不能得到正确率0.95
相关企业：
    - [experience27-微软算法.md](experience27-微软算法.md)