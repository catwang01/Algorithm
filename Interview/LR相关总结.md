
[toc]

# Logistic Regression

## 1. LR的损失函数公式

### 统计视角： 根据极大似然估计可以得到

假设 $y \sim Bernoulli(\pi(x))$ ，

其中 $\pi(x)$ 是关于 $x$  的线性函数。参数为 $\beta$ 即

$$
\pi(x;\beta ) = x^T \beta
$$ 

则样本 $i$ 的似然函数为

$$
L(x_i;\beta) = \pi_i^{y_i} (1-\pi_i)^{1-y_i}
$$ 

取对数，仍然记作 $L$ 

$$
\begin{aligned}
    L(x_i;\beta) &= y_i \log \pi_i + (1-y_i) \log (1-\pi_i) \\
    &= y_i \log x_i^T \beta + (1-y_i) \log (1-x_i^T \beta ) \\
\end{aligned}
$$ 

### 信息论角度：

真实分布: $y \sim Bernoulli(\pi(x))$ ，

关于样本分布，理解起来可能有点费劲：
1. 若样本 $y_i = 1$ ，则表明 $P(y_i=1)=1, P(y_i=0)=0$
2. 若样本 $y_i = 0$ ，则表明 $P(y_i=1)=0, P(y_i=1)=1$

即 $P(y_i=1)=y_i, P(y_i=0)=1-y_i$ 

因此计算真实分布和样本分布的交叉熵

$$
L(y_i, \hat{y}_i) = y_i \log \pi_i  + (1-y_i) \log (1 - \pi_i)
$$ 


（来自李宏毅ppt，注意$\hat{y}$表示的是样本值，和一般的表示方法不同）
![picture from 李宏毅](https://gitee.com/EdwardElric_1683260718/picture_bed/raw/master/img/20200428202534.png)

## 2. 为什么LR不使用MSE做损失函数？

因为当前值远离最优解时，梯度小，不容易收敛。

![picture goes here](https://gitee.com/EdwardElric_1683260718/picture_bed/raw/master/img/20200428203810.png)


预测值为

$$
f(x) = \frac{1}{1 + \exp (-x_i^T \beta )}
$$ 

如果取 MSE 为损失函数，有

$$
L = \sum_{i=1}^{N} (y_i - f(x_i))^2
$$ 

对 $\beta$  求导

$$
\begin{aligned}
    \frac{\partial L}{\partial  \beta }  = -2 \sum_{i=1}^{N} (y - f(x_i)) f(x_i) (1 - f(x_i)) x_i
\end{aligned}
$$ 

假设 $y_i=1$ 
1. 若 $f(x_i)=1$ 时，上式为 0，因此梯度不会更新。这是合理的，因为已经到达了最优值。
2. 若 $f(x_i)=0$ 时，上式为 0，因此梯度不会更新。这是不合理的，因为明明估计是很差的，但是梯度却为0，因此参数无法更新，所以模型难以优化。

## 3. 为什么用 logistic 函数作为link function？

logistic函数：

$$
f(x) = \frac{1}{1+ e^{-x}}
$$

1. 定义域为 $(- \infty, + \infty)$，值域为 $(0, 1)$，因此可以压缩将任意值压缩到$(0, 1)$，形成一个概率。
2. 光滑，容易求导。

导数满足 $f'(x) = f(x)(1-f(x))$

## 4. LR的推导过程

Motivation: 如何用线性回归来解决分类问题？

1. 不是预测分类本身，而是预测概率。

线性回归不能保证预测出来的是概率，因此我们对线性回归的结果$y=X\beta$上面再套一个非线性函数将其压缩到$(0,1)$，因此会得到一个概率。

这个非线性函数是 sigmoid 函数，因此得到:

$$
y = \frac{1}{1 + e ^{-X\beta}}
$$

![\picture goes here](https://gitee.com/EdwardElric_1683260718/picture_bed/raw/master/img/20200428210052.png)

## 5. LR如何解决共线性，为什么深度学习不强调

如何解决：加正则项。加二阶正则项相当于进行了 Laplace 分布的先验

共线性是源于线性模型，而深度学习并不是线性模型。所以说深度学习并不需要进行解决共线性问题。

## 6. LR如何防止过拟合

加正则项。不过实际使用中 LR 一般不需要担心过拟合的问题，因为 LR 只能处理线性关系，不能处理非线性关系。

## 7. LR分布式训练怎么做

## 8. 多分类问题

多分类问题的损失函数

从单样本二分类慢慢过渡。

### 单样本二分类

$$
L(y_i, \hat{y}_i) = - y_i \log \frac{1}{1 + \exp x_i^T \beta } - (1-y_i) \log \frac{\exp x_i^T \beta }{1 + \exp x_i^T \beta }
$$ 

### 单样本多分类

$$
\begin{aligned}
L(y_i, \hat{y}_i) &= - y_{i0} \log \frac{1}{1 + \sum_{i=1}^{K-1} \exp x_i^T \beta_i} \\ 
    &- y_{i1} \log \frac{\exp x_i^T \beta_1 }{1 + \sum_{i=1}^{K-1} \exp x_i^T \beta_1 } \\
    & - \ldots - y_{i,K-1} \log \frac{\exp x_i^T \beta_{K-1} }{1 + \sum_{i=1}^{K-1} \exp x_i^T \beta_{K-1} } 
\end{aligned}
$$ 

### 多样本多分类

$$
L(y, \hat{y}) = \sum_{i=1}^{N} 
\left(- y_{i0} \log \frac{1}{1 + \sum_{i=1}^{K-1} \exp x_i^T \beta_i } 
 - y_{i1} \log \frac{\exp x_i^T \beta_1 }{1 + \sum_{i=1}^{K-1} \exp x_i^T \beta_1 } 
     \ldots
 - y_{i,K-1} \log \frac{\exp x_i^T \beta_{K-1} }{1 + \sum_{i=1}^{K-1} \exp x_i^T \beta_{K-1} } \right)
$$ 


## 9. 什么是线性模型？LR为什么是线性模型？ （飞书算法）

判断一个分类模型是否是线性模型，要看其决策边界是否是线性的。

决策边界指的是样本属于正例和负例概率相等的那条线。对于 lr 来说，决策边界的推导如下：

$$
\begin{aligned}
&p(y=1|x) = \frac{1}{1 + \exp(-X\beta+b)} = \frac{1}{2} \\
&=> \exp(-(X\beta+b)) = 1 \\
&=> X\beta + b = 0
\end{aligned}
$$

即决策边界为 $X\beta + b = 0$，因此是线性的。

## 10. 如何提升LR的模型性能？ （飞书算法）



[toc]
# References

1. [LR公式的推导 - dpwang - CSDN博客](https://blog.csdn.net/dpengwang/article/details/86746233)
2. [(1条消息)为什么说逻辑回归LR是线性分类器？_成长之路-CSDN博客_为什么lr是线性模型](https://blog.csdn.net/xfwdxt/article/details/102516650?utm_medium=distribute.pc_relevant_t0.none-task-blog-BlogCommendFromMachineLearnPai2-1.edu_weight&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-BlogCommendFromMachineLearnPai2-1.edu_weight)
