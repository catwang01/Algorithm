
[toc]

ed 实习

## 小米

![46defc2c769106ea9be2e8534dbcc999.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p14034)

[【实习】【小米】搜索与推荐算法工程师 - 实习(Intern)版 - 北大未名BBS](https://bbs.pku.edu.cn/v2/post-read.php?bid=896&threadid=17739319)

## 知乎

![9c581750da1dd0d0b561d863d9ab9472.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p14035)


[【实习】知乎推荐算法实习生-北京 - 实习(Intern)版 - 北大未名BBS](https://bbs.pku.edu.cn/v2/post-read.php?bid=896&threadid=17560785)

## 奇智研究院

![c9680ce31358897fef80b9a8202e1939.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p14036)

[【实习】创新奇智 人工智能算法实习生 - 实习(Intern)版 - 北大未名BBS](https://bbs.pku.edu.cn/v2/post-read.php?bid=896&threadid=17740739)

## 微软

[【实习】【微软】Bing搜索NLP算法实习生 - 实习(Intern)版 - 北大未名BBS](https://bbs.pku.edu.cn/v2/post-read.php?bid=896&threadid=17740680)

![2f9bd0a0121db3284c2d88a3ea5bd065.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p14045)

# bing 算法实习生面经

## 一面 1h 2020-08-03 16:00-17:00

1. 由于简历里面有提到爬虫，因此问了一些关于爬虫的问题。问题不是很深，大概就是你知道有这么个东西就可以的程度。
    1. 海量数据url如何高效去重（bloom filter）
    2. 如何判断那个网页应该入库（不知道面试管想听什么内容。我说的是可以训练一个模型去输出是否是垃圾网页，类似于垃圾邮件过滤）
    3. 知道 robots 协议吗。有什么用

2. 算法题：设计一个栈。要求

1. 栈的底层只能用大小为 n 的数组，不能有其他空间开销
2. 实现 O(1) 的pop 和 O(1) 的 append。其中 append 支持无限次调用，如果append 的元素超过n个，会覆盖掉最开始 append 入栈的元素
3. pop 最多将最近 append 的 n 个元素输出。

这个是要重复利用 n 个大小的，可以使用 mod 运算。但是其中有一点，需要区分哪个元素是头，那个元素是尾。我是用 python 实现的，初始化所有元素为 None，pop 的时候也将数组尾部赋值为 None。面试官说这种方式有些取巧。让我不用 None 来实现。我说再添加一个指针，虽然最后实现了功能。但是面试官觉得那种实现方式比较难懂。说添加一个变量，来记录栈中的有效数据即可。

3. 有几十G的文件，其中是电话号码。只有8G内存，问如何进行排序。我说了使用归并排序来进行外部排序。面试官说可以，但是有更好的方法。然后满满引导我，电话号码的特点是什么，是唯一性。我下去想了想，可能是用前缀树来保存。所有的电话号码，然后遍历一边就可以输出，但是当时没有回答出来就结束面试了。

一面不久，晚上就打电话约二面了

## 二面 1h 2020-08-03 10:30-11:30

二面比较迷，连自我介绍都没有，就直接上来做题，做完题就结束了。
题目有三道：
1. [剑指 Offer 22. 链表中倒数第k个节点 - 力扣（LeetCode）](https://leetcode-cn.com/problems/lian-biao-zhong-dao-shu-di-kge-jie-dian-lcof/)

2. [236. 二叉树的最近公共祖先 - 力扣（LeetCode）](https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/) 我用递归实现了。让用非递归做。我说保存父结点的指针。还不满意，然后就没有做出来。

3. 有 n 个无重复字符串，需要找到这些字符串的前缀，满足两个条件：1. 一个前缀只对应一个字符串；2. 前缀长度尽可能短。

这个是用字典树做的。楼主之前对字典树没有接触过，但是一面涉及到了，就稍微看了下。结果没想到三面又问到。如果我说没听说过字典树，估计就当场直接结束面试了，所以我就硬着头皮说这个可以用字典树做，但是我昨天才知道这种数据结构，不太熟之类的。结果面试官就说没事，把它当做一棵普通的树就可以了，然后就硬着头皮做。不过幸好最后也算是给出了一个答案了。不过面试官不是很满意，并把他的结果告诉我了。


一天后就打电话告诉我二面过了，向我确认意向。楼主也算终于拿到了第二份实习。