[toc]


大菜菜带小鹅 4月8日
编者荐语：

群内同学的总结

以下文章来源于AI蜗牛车 ，作者空










机器学习岗蒟蒻

暑期实习总结






算

法




















 本人本科双非，华南某985硕士，本硕都是计算机专业。本科玩过一段时间ACM，巨菜（现在想想，不管是考研还是求职，这段经历都为我带来了许多便利）。

【大菜菜：自称巨菜，稳是金牌选手】

有一篇SCI一区的论文，方向比较偏，是智能电网相关的，面试官都不太感兴趣。有一个国际大数据比赛的一等奖和一个国内数据挖掘比赛的冠军







 壹丨面试情况 



简单介绍一下本人找暑期实习的情况，从2月中旬开始准备，投了字节闪电内推，鹅厂提前批，阿里CBU和企业金融的预面试。字节闪电内推简历被筛，鹅厂拿到了推荐岗的offer，阿里CBU过了一面，企业金融过了二面。拿到鹅厂offer后把其他家的面试都推了，因为想着就算发了offer可能也还是会选鹅厂。



【大菜菜：鹅厂天下第一，不要犹豫】



整个实习的过程从开始准备到结束大概就是一个月，这一个月基本上也是边面试边刷面经，补基础，还算十分充实吧233。事后想想，自己的六轮面试都过了，真的是十分幸运。



 贰丨简历




简历一定要重视！简历的内容决定了你能否被捞，一定程度决定了你面试的时候会被问什么。



关于如何编写简历，我觉得有几点建议可以跟大家分享一下：



① 头像完全可以不放，如果要放，请尽量放西装证件照，或者说高P过的照片。给HR和面试官一个比较好的初印象。



② 简历要突出重点。学历的地方要写清楚拿过什么奖学金，拿了几次，绩点排名多少，论文的部分要把期刊/会议的级别写显眼一些。这些都是HR比较关注的。比赛建议按照难点-方案这样子的格式去写，避免写一大堆方案，面试官抓不到感兴趣的点。



③ 不太熟的技术不要写在简历上面。面试的时候面试官可能会问你简历上涉及的东西，问了后发现你一知半解会很降分。个人觉得，一个知识面不宽但是对相关的知识都比较熟悉的印象远比什么都一知半解好。



④ 博客，github如果有比较亮眼的成果可以写在简历上，可以自我介绍时讲，HR会比较感兴趣。



⑤ 简历尽可能简洁，不重要的奖项（或者说跟你最好的奖项相比比较弱）可以去掉，只写出你最亮眼的地方。比如一个rank不高的比赛，写到简历上可能是个扣分项。当然，如果没有更好的奖项了，可以写上去表明自己做过这方面的工作。





  叁丨面试 



我们在牛客上可以看到很多人的面经，同样一个岗位，有的人很难，有的人很轻松。我认为的原因有：



① 简历。经历比较丰富的人，一般面试上来会被问比较亮眼的经历，一轮面试的一半左右时间会花在这上面，而且因为是自己做过的工作，被问时基本不会有什么压力。所以整体的面试难度会降低。



② 话题的引导。这个算是我自己几次面试中领悟到的，我们在面试时要有意讲话题引导到自己擅长的领域，比如我一般会有意避开NLP，CV，让面试官问我机器学习相关的知识。所以面试官经常会说我“对机器学习比较熟悉，不过某些方面可以再加强一下”，这个印象其实我觉得还好，反正把握好自己擅长的地方，积极避开不擅长的领域相当重要。



③ 运气。这个无可厚非，无法避免。有的部门面试就是很难，有的部门面试就是比较水，或者说这个部门认为你的经历比较对口，那么面试难度也会降低不少。



在等待面试的期间，应该积极去牛客网刷对应的面经，把可能出现的问题抄下来，一个个去巩固。面试问的题目在牛客面经上基本都是高频问题。



  肆丨几个建议 



① 分享，交流。我本人和熟人相处时会比较放得开。因此，我会和关系比较好的朋友/同学分享，讨论每一次的面试录音。找出一些不足，一些可以改进的地方。另外，面试完在牛客网，QQ群分享面经也是一个不错的行为，受了别人帮助，也要回报。



【大菜菜：同学你十分活跃，和我准备校招时采取的策略一致，分享自己/解答他人疑惑 对自己确实帮助确实很大】

【其他同学：这么好的QQ群哪里找？群号:768055618】



② 多关注招聘信息。招牌期间会有很多群，建议多加，了解一些全面的情况。



③ 不要一开始就面想去的公司，理由大家都懂。可以多投一些二线公司，或者不想去的一线公司，攒攒面经。



④ 像阿里的预面试，鹅厂的提前批，这种机会不要错过。可以积攒丰富的面试经验。



  伍丨准备工作 




本人只针对机器学习/数据挖掘岗提出建议，CV，NLP岗可能情况不一样哈。

机器学习/数据挖掘主要需要准备的内容包括：

① ML相关的知识：这部分知识我下面会列出一些比较高频的问题。需要特别注意GBDT,xgb和lgb的区别，建议实际使用过并看过原始论文。需要熟练手撸的简单算法有LR, NB, Kmeans。对于LR和树模型这种工程使用较多的，需要知道跟并行相关的一些知识。比如LR如何处理千万级别的数据样本，xgb如何并行等。

② 数学知识：这一块主要是高数，线代，概率论，凸优化。高数上（加上无穷级数），线代，概率论需要熟练掌握，凸优化重点掌握一维搜索方法，一阶/二阶优化方法，KKT条件，对偶问题，线性规划，二次规划。

③ 基础算法。这部分的重要性不用多说，刷leetcode。剑指offer的题目一定要达到秒杀级别。基本的都会了之后，算法岗重点强化DP，记忆化搜索这两方面。对于笔试，建议多去牛客刷往年的真题，注意笔试的题目难度往往远高于面试。（当然不会要求全部AC）

④ 场景问题：对于机器学习/数据挖掘岗,现在大多数的公司业务都是反欺诈（异常检测）/推荐系统，对于这两方面的基本内容和传统方法要能讲出来一些东西。这也是必问的问题。

⑤ 智力题：其实这个应该和算法题归为一部分，智力题考来考去其实就这么几道——疯狗，毒水，海盗分金币，两根蜡烛，三门问题等。

⑥ DL相关知识：就算是机器学习岗，也需要了解一些深度学习的基本知识，常用的模型，如何调参等。最好了解一个框架（建议tensorflow或pytorch）。

⑦ 语言方面：建议熟悉C++ 和 python至少其一。





 陆丨个人整理的一些高频问题 




1. lightgbm, xgboost RF和GBDT的异同（这个问题属于必问问题，对于ID3,C4.5,CART也要了解，对于xgb的算法原理要充分理解，比如损失函数的推导过程，为什么要使用二阶泰勒展开。最好有一些调参经验）

2. svm损失函数推导

3. 朴素贝叶斯公式推导与实现

4. 处理不平衡常用方法

5. 卷积层相比FC层有哪些优势？

6. 非线性分类算法有哪些

7. 如何判断一个算法是线性的还是非线性的？

8. stacking/boosting/bagging的区别

9. 手动实现堆排序

10. 求AUC

11. L1和L2的区别

12. 实现快排

13. LR的实现，优点，如何并行，特征有共线性会怎么样？

14.pca和lda

15. 常见激活函数的优缺点

16.从方差和偏差的角度比较bagging和boosting

17. 经验风险、期望风险、结构风险

18. 分层采样和蓄水池采样，O（N）的洗牌算法

19. SVM与LR的区别

20. 一阶优化器，二阶优化器

21. 手写kmeans

22. BN/LN/WN的区别

23. 实际场景下做softmax容易出现一些问题，怎么解决

24. 扔鸡蛋问题（了解到O（kn）的做法即可）

26. 进程和线程的区别

27. Python/C++多线程,多进程如何使用

28. Python迭代器，装饰器

29. Bootstrap抽样

30. 特征选择方法

31. 野指针是什么意思

32. 64匹马，八个赛道，找出最快的四匹，最坏情况下最少要比多少次（更常见的是25匹马，5个赛道找出最快的3匹）。

33. 12个小球，其中有一个与其他的重量不一样，给你一个天平，最坏情况下最少称多少次可以找出重量不同的小球。

34. 1000杯水中有一瓶是毒药，小老鼠喝一滴一小时就会死，给你10只小老鼠，在一小时内找出这瓶水 。

35. P-R曲线和ROC曲线的区别

36. 什么是凸问题？

37. 常见的凸优化方法？

38. CNN/RNN/LSTM的原理

39. 从方差，偏差，噪声的角度解释泛化误差

40. 特征工程相关。比如如何处理类别特征？onehot，tfidf会出现什么问题之类。

41. 词嵌入embedding相关知识（主要是word2vector）

42. 梯度爆炸/梯度消失

43. 池化层，卷积层的作用

44. dropout（训练和测试阶段分别如何处理）

45. MLE,MAP和贝叶斯估计的区别

46. DNN反向传播的推导

47. LR为什么用交叉熵而不是MSE？

48. 为什么LR权重可以全部初始化为0，NN不行

49. 常见的几个聚类算法

50. 异常检测/推荐基本方法（这个视部门业务而定）

51. 判别式模型和生成式模型





  柒丨相关书籍和连接 













本人看书不多，就推几本比较热门的书籍吧。

① 西瓜书，南瓜书，统计学习基础。适合拿来刷机器学习基础

② 动手学深度学习，花书。适合拿来刷深度学习基础。特别是前者，有pytorch版本的代码实现。

③ 深入理解XGBOOST。最近很火的一本书，看了一下质量相当不错。

④ 剑指offer。这本不买也行，leetcode和牛客有对应题目

⑤ 程序员面试宝典。题目较多，较全，较难。在掌握了剑指offer和基本算法内容之后，可以作为进阶食用。



相关链接



① 本人鹅厂pcg推荐岗暑期实习面经：https://www.nowcoder.com/discuss/381945?toCommentId=5544852

② 本人阿里巴巴算法暑期实习面经：https://www.nowcoder.com/discuss/373146?toCommentId=5564924

③ 阿泽（几篇机器学习的文章质量很高）：https://www.zhihu.com/people/is-aze

④ 刘建平的博客（老码农了，同样质量相当高）：https://www.cnblogs.com/pinard/




 最终丨后话


算法岗虽竞争较大，但手里有一些筹码，准备充分的话其实也还好。

有时间的情况下，建议丰富竞赛，实习经历。

论文也是硬通货，但是难度确实更大。

当然有时候也很看运气，但是运气毕竟是不可控的。

希望这篇文章可以帮到你早日拿到offer~



[机器学习岗蒟蒻暑期实习总结](https://mp.weixin.qq.com/s?src=11&timestamp=1597034345&ver=2513&signature=RGTKdkfBsCJuYg43ZRnnG-p88YaSDbc4d24Ixx6GrP1P-JSl6BKXtmd3NaqGHuWUSB2ouaoUfmCAy4s6khppJ335KD3xkBuUaGUbsooyKfDbZMNsJDCRh4XAIB8P8IuK&new=1)
