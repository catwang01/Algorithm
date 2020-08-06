[toc] 

## 相关公司

1. [experience2-京东算法.md](experience2-京东算法.md)
2. [experience5-360 商业化ML 面经.md](experience5-360%20商业化ML%20面经.md)
3. [experience19-头条推荐.md](experience19-头条推荐.md)
4. [experience18-新浪算法.md](experience18-新浪算法.md)
5. [experience1-京东算法.md](experience1-京东算法.md)
6. [experience22-京东.md](experience22-京东.md)
7. [experience7-京东算法.md](experience7-京东算法.md)

7. [experience20-京东算法.md](experience20-京东算法.md)
8. [experience21-bat面试题.md](experience21-bat面试题.md)
9. [experience23-didi算法.md](experience23-didi算法.md)

## ML相关

### 其它

1.过拟合、欠拟合是什么，有什么解决方案 [experience20-京东算法.md](experience20-京东算法.md)

2. bagging和boosting是什么，有什么区别，是怎么把弱模型变成强模型的 [experience20-京东算法.md](experience20-京东算法.md)
- boosting和bagging的区别？ [experience21-bat面试题.md](experience21-bat面试题.md)
- bagging为什么能减小方差？ [experience21-bat面试题.md](experience21-bat面试题.md)

3. AUC的原理介绍一下 [experience21-bat面试题.md](experience21-bat面试题.md)

## 特征工程相关

1. 在做特征工程时采用了哪些方法呢？ 常见的筛选特征的方法有哪些？ ( 飞书算法 )

2. 如果模型发生过拟合，应该怎么样处理，如果调参后（已无法通过调参解决问题）还是过拟合，又该怎么办？ [experience18-新浪算法.md](experience18-新浪算法.md)

3. 属性选择的方法有哪些，具体说明。 [experience18-新浪算法.md](experience18-新浪算法.md)

4. 开放题：你觉得影响模型效果的因素有什么，并排个序。（我回答的是特征>模型>优化器，才疏学浅只答了这些hh，大家有什么Trick在评论里分享一下哦） [experience1-京东算法.md](experience1-京东算法.md)

5. one-hot、 label-encoder对于category类型变量的处理方式，

6. 样本不平衡的处理方法（涉及到业务知识）

7. 样本不平衡怎么做 [experience23-didi算法.md](experience23-didi算法.md)

京东 算法：GBDT的原理、LR的原理、对数据倾斜处理的方法

### svm

1. 然后推导SVM的原理 [experience22-京东.md](experience22-京东.md)

2. 然后logistic和SVM的区别 [experience22-京东.md](experience22-京东.md)

3. SVM为什么需要核函数，以及用了核函数之后数据的维度是变低还是变高了； [experience22-京东.md](experience22-京东.md)

### 聚类相关

3. 聚类算法了解程度、kmeans介绍、K值选择、kmeans++算法

### XGBoost && GBDT && RF

1. 对xgboost的了解 ( 京东算法 )

2. (todo) xgboost和lightgbm的区别 ( 京东算法x2 )

3. GBDT和Xgboost的区别，哪些是解决过拟合问题的。[experience18-新浪算法.md](experience18-j新浪算法.md)
- XGBOOst和GBDT的区别。 [experience21-bat面试题.md](experience21-bat面试题.md)

4. GBDT和随机森林有什么区别 [experience21-bat面试题.md](experience21-bat面试题.md)

4. (todo) GBDT+LR模型融合的方法，以及对比只用GBDT和用GBDT+LR有什么区别？哪种方法更加有效？ [experience18-新浪算法.md](experience18-新浪算法.md)
- GBDT+LR是怎么做的? [experience21-bat面试题.md](experience21-bat面试题.md)

5. GBDT，Xgboost，RF模型在实际应用中的参数，以及如何调参，Bagging和Boosting采样的区别，[experience18-新浪算法.md](experience18-新浪算法.md)

6. 进行bagging和Boosting的数学意义是什么。 [experience18-新浪算法.md](experience18-新浪算法.md)

7. GBDT的原理，如何做分类和回归 [experience21-bat面试题.md](experience21-bat面试题.md)

8. 随机森林的随机体现在哪方面 [experience21-bat面试题.md](experience21-bat面试题.md)

9. 树集成模型有哪几种实现方式：Bagging和Boosting，回答过程中又问到了很多细节。AdaBoost是如何改变样本权重，GBDT分类树拟合的是什么？ [experience21-bat面试题.md](experience21-bat面试题.md) 

10. CART分类树和ID3以及C4.5有什么区别？ [experience21-bat面试题.md](experience21-bat面试题.md) 

12. 比赛相关：lgb&xgb，这两个模型相较于gbdt的优化？boosting的过程？boosting中每一轮loss是怎么样计算的？（这一部分之前看过，但是没特意去看。。。）
[experience5-360 商业化ML 面经.md](experience5-360%20商业化ML%20面经.md)

13. lightgbm相对xgboost的改进 [experience23-didi算法.md](experience23-didi算法.md)

14. 介绍bagging和boosting
相关企业：
    - [experience27-微软算法.md](experience27-微软算法.md)

### LR相关

1. LR的随机梯度实现
3. 口述逻辑回归，写下其损失函数
4. 口述逻辑回归 [experience7-京东算法.md](experience7-京东算法.md)
2. 什么是线性模型？LR为什么是线性模型？ （飞书算法）
4. 如何提升LR的模型性能？ （飞书算法）
5. 对于LR来说，LR如果多了一维冗余特征，其权重和AUC会怎样变化（权重变为1/2, AUC不会变化） [experience1-京东算法.md](experience1-京东算法.md)
6. 写出LR的损失函数（交叉熵损失函数） [experience1-京东算法.md](experience1-京东算法.md)
7. 写交叉熵，Softmax [experience1-京东算法.md](experience1-京东算法.md)
8. 神经网络里面的损失函数有哪些 [experience21-bat面试题.md](experience21-bat面试题.md)
交叉熵损失函数，0-1分类的交叉熵损失函数的形式。什么是凸函数？0-1分类如果用平方损失为什么用交叉熵而不是平方损失？ [experience21-bat面试题.md](experience21-bat面试题.md)
9. 用pytorch写下逻辑回归训练过程 [experience7-京东算法.md](experience7-京东算法.md)
10. 如果逻辑回归的所有样本的都是正样本， 那么它学出来的超平面是怎样的？ [experience21-bat面试题.md](experience21-bat面试题.md)
11. 哪些场景下的分类问题不适用于交叉熵损失函数？ [experience21-bat面试题.md](experience21-bat面试题.md)


### 正则相关

2. 正则化手段 [experience1-京东算法.md](experience1-京东算法.md)
4、口述l1和l2正则化

3. 从原理上解释L1, L2正则（如L1正则为什么能够起到特征选择的作用） [experience1-京东算法.md](experience1-京东算法.md)
4. L1和L2的区别？L1有什么缺点？L2呢？平时用L1多还是用L2多？为什么正则化选L2呢？为什么不选L1？L1为什么产生稀疏解？ （飞书算法）
5. L1和L2有什么区别，从数学角度解释L2为什么能提升模型的泛化能力。 [experience21-bat面试题.md](experience21-bat面试题.md)
6. 深度学习中，L2和dropout有哪些区别？ [experience21-bat面试题.md](experience21-bat面试题.md)
7. L1正则化有哪些好处 [experience21-bat面试题.md](experience21-bat面试题.md)
8. early stop对参数有什么影响？ [experience21-bat面试题.md](experience21-bat面试题.md)

## DL相关

### 优化器相关

1. 几种梯度下降的方法和优缺点？ (飞书算法)

2. (todo) 平时怎么选择优化器？讲一下adam的优点 [experience2-京东算法.md](experience2-京东算法.md)

3. Adam的原理、公式 (没答上来) [experience19-头条推荐.md](experience19-头条推荐.md)

4. 说说Adam等优化器的区别（从Momentum到RMSprop到Adam以及Adam可能不会收敛，还说了NAG和AdaGrad） [experience1-京东算法.md](experience1-京东算法.md)

5. 推导梯度下降公式 [experience7-京东算法.md](experience7-京东算法.md)

6. sgd和batch梯度下降区别, 一个batch指的什么 [experience7-京东算法.md](experience7-京东算法.md)

### 激活函数相关

1. sigmoid和relu的区别？平时用什么用的多？为什么用relu多呢？ （飞书算法）

2. 口述了解的激活函数，为什么要激活函数 (京东算法)

3. Sigmoid，Tanh，Relu等激活函数的优缺点（这里之前没有复习到，后面想了想应该从梯度消失，数据压缩，0均值方面来解释；当然，说的越多越好，比如Relu的神经元dead啥的，越能体现你的知识广度） [experience1-京东算法.md](experience1-京东算法.md)
Relu、Sigmoid和tanh分别有什么不同； [experience22-京东.md](experience22-京东.md)

3. 为什么要用ReLU替代tanh/sigmoid/softmax
答：ReLU求导的值要么是0要么是1，不会引起梯度消失或梯度爆炸 [experience19-头条推荐.md](experience19-头条推荐.md)

5. dnn中如果把中间层的激活函数去掉会怎样？去掉激活函数的dnn与逻辑回归有什么区别？ [experience1-京东算法.md](experience1-京东算法.md)

- [experience21-bat面试题.md](experience21-bat面试题.md)

### CNN 相关

1. (todo) resnet结构 [experience2-京东算法.md](experience2-京东算法.md)
2. ResNet (todo) [experience19-头条推荐.md](experience19-头条推荐.md)

答：通过x + f(x)的结果，让深层网络获得不差于浅层网络的学习能力，从而允许网络变得更深

3. 用CNN去处理文本信息的时候，如果只有一层CNN，设计一个模型结构，以及参数的大小； [experience22-京东.md](experience22-京东.md)

4. 为什么CNN作用这么强大，可以处理图像以及文本信息；还有几个编程题，不过都巨简单就不说了。 [experience22-京东.md](experience22-京东.md)

5. Pooling种类，区别以及适用场景 [experience1-京东算法.md](experience1-京东算法.md)

6. 谈谈1*1卷积 [experience1-京东算法.md](experience1-京东算法.md)

7. dnn和cnn区别 [experience7-京东算法.md](experience7-京东算法.md)
8. cnn为什么参数共享 [experience7-京东算法.md](experience7-京东算法.md)

### RNN 相关

#### LSTM 和 GRU

1. lstm结构 [experience2-京东算法.md](experience2-京东算法.md)

2. (todo) gru跟lstm有什么区别？ [experience2-京东算法.md](experience2-京东算法.md)

3. RNN公式 [experience22-京东.md](experience22-京东.md)

4. 然后写了一下RNN（GRU）的公式 [experience22-京东.md](experience22-京东.md)

- LSTM的公式 [experience21-bat面试题.md](experience21-bat面试题.md)

- RNN为什么出现梯度消失及BPTT的推导 [experience21-bat面试题.md](experience21-bat面试题.md)

5. LSTM各个门的作用？我口头讲了一下LSTM的计算公式，然后又问为什么用sigmoid&tanh？然后衍生到LSTM为了解决RNN的什么问题&GRU是否了解？然后我又口述了GRU的计算公式以及两个门的作用
[experience5-360 商业化ML 面经.md](experience5-360%20商业化ML%20面经.md)

### BN

1. bn怎么实现的？inference时候具体怎么做的？ [experience2-京东算法.md](experience2-京东算法.md)

2. 然后又讲到神经网络，BN层的作用？每个Batch_size的样本的均值的问题？ （这个不太理解是什么问题了，我答的是根据大数定律batch均值期望跟所有样本均值相接近，答完就觉得很扯。。。面试官说其实是动量，计算时会用到之前的batch_size的均值）
[experience5-360 商业化ML 面经.md](experience5-360%20商业化ML%20面经.md)

3. Batch Normalization的原理
答：在mini_batch上进行而不是在整个数据集上进行。在训练集上有BN测试集上没有BN，这样不会发生数值上的偏移，道理类似dropout，即记录下训练集上的BN参数（均值、标准差、\beta、\gamma）作为网络参数的一部分。 
[experience19-头条推荐.md](experience19-头条推荐.md)

### Dropout

1. Dropout的原理 (为什么训练时有dropout测试时没有dropout，这样会发生scale的偏移吗) [experience19-头条推荐.md](experience19-头条推荐.md)

2. Dropout，Layer Normalization， residual net的作用； [experience22-京东.md](experience22-京东.md)

### Attention

1. Attention机制 [experience1-京东算法.md](experience1-京东算法.md)

2. Attention注意力机制的原理 [experience22-京东.md](experience22-京东.md)

### 其它

1. 说下神经网络正向和反向过程，最后面试官画了个图，让我求导。 [experience7-京东算法.md](experience7-京东算法.md)

2. 神经网络中网络权重W初始化为0有什么问题？ [experience1-京东算法.md](experience1-京东算法.md)

## 推荐系统相关

### 百度 系统设计：推荐系统有A信息如下，类似于user_id、ad_id、ad信息，B信息如下，包括图像信息、ad_id(即ad与原生图像之间的信息)，对于出现的广告，如何对该广告进行合理配图

### 百度 推荐系统的框架了解（召回和ranking）

### 百度 系统设计：推荐系统还有融合框架，假如通过两种不同的召回和ranking系统得到结果，如何在两种备选结果中最终给用户推荐出最适合的十个广告

### dp & wide

1. Wide &Deep的原理 [experience21-bat面试题.md](experience21-bat面试题.md)

### DIN

CTR预估模型的演化过程中的着手点 [experience1-京东算法.md](experience1-京东算法.md)

1. DIN结构，DIN提出动机以及与之前模型的区别 [experience1-京东算法.md](experience1-京东算法.md)
2. DIN中Attention机制实现 [experience1-京东算法.md](experience1-京东算法.md
3. DIN 和 DIEN 网络结构介绍 [experience1-京东算法.md](experience1-京东算法.md)

### 4. DIN结构，DIN提出动机以及与之前模型的区别
### 6. DIN中Attention机制实现
### 4、deepwalk优缺点 (京东算法)
### 5、对推荐算法有什么了解 (京东算法)

### CTR相关

#### 6、ctr中会遇到什么问题，怎么解决 (京东算法)
#### 5. CTR预估模型的演化过程中的着手点

### FM模型

1. 谈谈Youtube的那篇《Deep Neural Networks for YouTube Recommendations》 [experience1-京东算法.md](experience1-京东算法.md)
2. 谈谈FM与DeepFM [experience1-京东算法.md](experience1-京东算法.md)
3. 谈谈FM的泛化能力 [experience1-京东算法.md](experience1-京东算法.md)

4. FM模型与LR区别 (京东算法)

5. 口述deepfm (京东算法)

6. DeepFM与FM的关联，并描述DeepFM的结构 [experience1-京东算法.md](experience1-京东算法.md)

7. 你平时有没有读过推荐算法的论文？
[experience22-京东.md](experience22-京东.md)
8. 聊一下一个你了解的推荐算法（本菜鸡只知道协同过滤算法）。
[experience22-京东.md](experience22-京东.md)
9. DeepFM介绍 [experience21-bat面试题.md](experience21-bat面试题.md)
10. FM推导 [experience21-bat面试题.md](experience21-bat面试题.md)
11. LR和FM的区别？FM需要进行交叉特征的选择么？如果在LR选了一部分特征做交叉之后，取得了比FM更好的效果，这是为什么？如果FM变成DeepFM之后，效果超过了LR，这又是为什么？ [experience21-bat面试题.md](experience21-bat面试题.md)
12. deepFM相对wide&deep改进 [experience23-didi算法.md](experience23-didi算法.md)

## NLP相关

讲一下文本分类模型。
给一个新的文本分类任务，会怎么选模型？
6、word2vec和bert区别 (京东算法)
w2v的原理，

## 开放题

1. 开放题：如果让你去解决一个陌生领域的问题，从分析问题到设计模型以及评价指标，你会怎么做？

2. 矩阵求逆是如何操作的？【答：高斯消元】描述过程？【答：左边一个A，右边一个I，消消消，消到左边的A变成I，右边的I就变成了A的逆矩阵】为什么可以这样算？如何证明？ [experience19-头条推荐.md](experience19-头条推荐.md)
答：高斯消元由矩阵行变换组成，矩阵行变换等价于左乘另外一个系数矩阵，所以当左边的A变到I，A就左乘了A的逆矩阵，同时右边的I也左乘了A的逆矩阵得到A的逆矩阵。这就是高斯消元法的原理。（马后炮分析，面试的时候没答上来，是面试官提示的）

3. 一个负载均衡里面产生的数学问题：现在有两台服务器A和B，后台算法是A和B都有1/2的概率被访问，如果访问的服务器宕机，则会以1/2的概率继续请求两个服务器。现在服务器B宕机了，求平均访问的次数？
[experience19-头条推荐.md](experience19-头条推荐.md)
答：这是一个随机变量求期望的问题。记平均访问的次数为p，

​ p = 1/2 * 1 + (1/2)^2 * 2 + (1/2)^3 * 3 + … + (1/2)^n * n + …

令q = 1/2 * p = (1/2)^2 * 1 + (1/2)^3 * 2 + … + (1/2)^n * (n-1) + …

故p = 2 (p - q) = 2 * [1/2 + (1/2)^2 + (1/2)^3 + …] = 2 * (1/2)/[1 - (1/2)] = 2

4. 如果让你设计推荐系统，将100个图片按顺序推荐给100个用户，如何设计算法？【答：什么什么矩阵，术语忘了。。。】100万个图片和100万个用户呢？【答：稀疏矩阵】计算这个矩阵的时候，用户的哪些信息可以利用？【浏览、点击、搜索；个人信息】社交媒体可以利用吗？【可以，好友偏好，群组偏好】
[experience19-头条推荐.md](experience19-头条推荐.md)

5. Python的shuffle函数内部是如何实现的？【呃。。。没有读过shuffle的源码】说说如果你来实现，你会如何实现？【每次random出一个index，和shuffle过的数组未shuffle部分的头交换】如何评价你提出的算法shuffle的性能？【首先定义两个数组间的“相似度”为两数组各个位置相同的数的个数，运行N次shuffle算法，计算得到的N个无序数组两两之间的相似度之和S，S越小，shuffle算法的无序性越好】

附：Python内置模块random.py的Random类的shuffle方法的实现：

```
def shuffle(self, x, random=None):
        """Shuffle list x in place, and return None.

        Optional argument random is a 0-argument function returning a
        random float in [0.0, 1.0); if it is the default None, the
        standard random.random will be used.

        """

        if random is None:
            randbelow = self._randbelow
            for i in reversed(range(1, len(x))):
                # pick an element in x[:i+1] with which to exchange x[i]
                j = randbelow(i+1)
                x[i], x[j] = x[j], x[i]
        else:
            _int = int
            for i in reversed(range(1, len(x))):
                # pick an element in x[:i+1] with which to exchange x[i]
                j = _int(random() * (i+1))
                x[i], x[j] = x[j], x[i]
```
[experience19-头条推荐.md](experience19-头条推荐.md)

4. 主要有MLP手动求梯度，
5. [experience22-京东.md](experience22-京东.md)

6. 给你十亿个用户的数据，寻找每个用户最相似的10个用户（要求可以有一个很好的分布式算法）。
[experience22-京东.md](experience22-京东.md)

7. 比如基于内容如何进行标题的改写（把看起来很平常的标题转为标题党的标题）； [experience22-京东.md](experience22-京东.md)

8. 给定一个网页，如何推荐网页最后面的广告信息； [experience22-京东.md](experience22-京东.md)

9. 如何设计一个命名实体识别的的Neural模型； [experience22-京东.md](experience22-京东.md)

10. 如果你想往模型中加入一个特征，如何判定这个特征是否有效？ [experience21-bat面试题.md](experience21-bat面试题.md)


14. 推荐系统中你认为最重要的环节是什么？ [experience21-bat面试题.md](experience21-bat面试题.md)

15. 多臂老虎机中，有许多方法，比如e-greedy，timponson采样，UCB，这些方法都有哪些适用场景？ [experience21-bat面试题.md](experience21-bat面试题.md)

16. 如何预测一家店分品类的销量 [experience21-bat面试题.md](experience21-bat面试题.md)

18. 模型在线下评估和线上使用时，往往出现线上实际效果不如线下效果的情况，请分析可能的原因。 [experience21-bat面试题.md](experience21-bat面试题.md)

19. 在CTR预估问题中，假设训练数据的正负样本数为1:4，测试数据中的正负样本数也为1:4，那么此时模型对测试集，学到的平均点击率为1/（1+4）,假设此时采取了欠采样策略，使正负样本数为1:1，对同样的测试集进行预测，平均点击率应该是多少？（样本量很大，初始总样本数为10亿） [experience21-bat面试题.md](experience21-bat面试题.md)

## HR

1. 说一下自己的优缺点
2. 内推你的人是谁？从他那了解了哪些信息？
3. 谈谈对部门业务的了解
4. 你觉得如果你来实习的话，你最想提升自己的哪些方面？或者说相比其他人，你的优势和劣势在哪里？
5. 目前还有公司在面试吗？进展如何？


在做模型优化的时候动机是什么？样本不平衡有没有考虑采样？数据量多大，跑了多久；

