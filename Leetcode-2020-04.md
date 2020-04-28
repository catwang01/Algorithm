[toc]

# Leetcode 4月刷题记录

| 时间| 题目链接 | 题解| 备注| tag |
| :----: | ------------------------------------------------------------ | ---------------------------- | ----------------------------------------- | ------------ |
| 2020-04-01 |||||
|| [2019校招真题在线编程_网易_丰收_牛客网](https://www.nowcoder.com/practice/83b419c027fa490aa60669b0e7dc06a3?tpId=98&tqId=32834&tPage=1&rp=1&ru=%252Fta%252F2019test&qru=%252Fta%252F2019test%252Fquestion-ranking) | AC 100% || 前缀和 + 二分法 |
|| [瞌睡_2019校招真题在线编程_网易_牛客网](https://www.nowcoder.com/practice/93f2c11daeaf45959bb47e7894047085?tpId=98&tqId=32833&tPage=1&rp=1&ru=%252Fta%252F2019test&qru=%252Fta%252F2019test%252Fquestion-ranking) | AC 100% || 比较简单的滑动窗口，窗宽为k |
|| [2019校招真题在线编程_网易_俄罗斯方块_牛客网](https://www.nowcoder.com/practice/9407e24a70b04fedba4ab3bd3ae29704?tpId=98&tqId=32832&tPage=1&rp=1&ru=%252Fta%252F2019test&qru=%252Fta%252F2019test%252Fquestion-ranking) | AC 100 % || 简单，就是一个求最小值的问题 |
|| [2019校招真题在线编程_牛牛的背包问题_牛客网](https://www.nowcoder.com/practice/bf877f837467488692be703735db84e6?tpId=98&tqId=32831&tPage=1&rp=1&ru=%2Fta%2F2019test&qru=%2Fta%2F2019test%2Fquestion-ranking) | AC 80% | 有特殊用例需要特殊考虑 | 递归 |
|| [2019校招真题在线编程_网易_牛牛的闹钟_牛客网](https://www.nowcoder.com/practice/9173e83d1774462f81255a26feafd7c6?tpId=98&tqId=32830&tPage=1&rp=1&ru=%2Fta%2F2019test&qru=%2Fta%2F2019test%2Fquestion-ranking) | AC 100 % || 二分法 |
||||||
| 2020-04-02 | 
| 2020-04-04 |
| |[1402. 做菜顺序 - 力扣（LeetCode）](https://leetcode-cn.com/problems/reducing-dishes/)| | | 贪心 |
| | [Nowcoder 网易 2019校招真题在线编程 塔_牛客网](https://www.nowcoder.com/practice/54868056c5664586b121d9098d008719?tpId=98&tqId=32837&tPage=1&rp=1&ru=%2Fta%2F2019test&qru=%2Fta%2F2019test%2Fquestion-ranking) | 10：26-9:58 = 28min 没有做出 | 不会使用 python 实现大根堆。不会用c++的堆 | 堆 |
| | [网易_2019校招真题在线编程_小易的字典_牛客网](https://www.nowcoder.com/practice/12b1b8ef17e1441f86f322b250bff4c0?tpId=98&tqId=32838&tPage=1&rp=1&ru=%2Fta%2F2019test&qru=%2Fta%2F2019test%2Fquestion-ranking) | 22:57 - 22:26 = 29 min AC40% | 原因：组合数计算错误 | 推荐 递归 + 组合数计算 |
| | [快手_2019校招真题在线编程_获得最多的奖金_牛客网](https://www.nowcoder.com/practice/247f7bd088764aefa7474cff27489095?tpId=98&tqId=32839&tPage=1&rp=1&ru=%2Fta%2F2019test&qru=%2Fta%2F2019test%2Fquestion-ranking) | 11:20-22:57=23min 没有AC | C++ 的 printf使用错误，不应该使用 %d，而应该使用 %lld | 普通的双指针|
|2020-04-05 | [1403. 非递增顺序的最小子序列 - 力扣（LeetCode）](https://leetcode-cn.com/problems/minimum-subsequence-in-non-increasing-order/) | 不会做 没有 AC | 没有想到用贪心 | 贪心法 |
|2020-04-06 |||| |
| | [72. 编辑距离](https://leetcode-cn.com/problems/edit-distance/) | AC || 经典的dp。从递归到dp|
| | [460. LFU缓存](https://leetcode-cn.com/problems/lfu-cache/) | 不会 | | 这个东西需要了解红黑树。看了一下有关红黑树的内容。 |
| 2020-04-08 | | | | |
|| [面试题13. 机器人的运动范围](https://leetcode-cn.com/problems/ji-qi-ren-de-yun-dong-fan-wei-lcof/) | | | |
| 2020-04-09 | | | | |
| | [22. 括号生成](https://leetcode-cn.com/problems/generate-parentheses/) | 9:00 - 9:30 没有 AC | 虽然明白是一个 dfs 问题，但是卡在了判断括号是否有效上。原来的思路：要判断括号是不是有效，需要使用栈。但是如果共用一个栈的话，之后的遍历会修改栈的内容。而且不好恢复。因此不会做了。**解决方法是不使用栈来判断括号是否有效。而只计算已经使用的左括号和右括号的个数。如果已经使用的右括号的个数大于左括号的个数，则不是有效括号。可以这样做的原因是左括号和右括号的总数是已知的。如果未知的话，就不可以这样做了。**| dfs 推荐 |
||[486. 预测赢家 - 力扣（LeetCode）](https://leetcode-cn.com/problems/predict-the-winner/) | | | 博弈论的套路题 dp |
|| [1406. 石子游戏 III - 力扣（LeetCode）](https://leetcode-cn.com/problems/stone-game-iii/) | || 博弈论的套路题 dp |
| | [小A最多会新认识的多少人_哔哩哔哩_2019校招真题在线编程_牛客网](https://www.nowcoder.com/practice/1fe6c3136d2a45fa8ef555b459b6dd26?tpId=98&&tqId=33021&rp=1&ru=/activity/oj&qru=/ta/2019test/question-ranking) | 17:56-18:26AC 100% | | bfs 或者 并查集 |
| | [几个岛_滴滴_2018校招真题在线编程_牛客网](https://www.nowcoder.com/practice/1ecd3d9e09664cde94919b65ea06b47c?tpId=90&&tqId=30919&rp=1&ru=/activity/oj&qru=/ta/2018test/question-ranking)| 18min 0% | | 并查集 |
| | [集合合并_小米_2019校招真题在线编程_牛客网](https://www.nowcoder.com/practice/c747216a5db24df385392f1a6b90a084?tpId=98&&tqId=32922&rp=1&ru=/activity/oj&qru=/ta/2019test/question-ranking)| 28 min 0% | | 并查集 |
| | [幼儿园分班_小红书_2019校招真题在线编程_牛客网](https://www.nowcoder.com/practice/e503f18d56754ad9bcf8631adf63721d?tpId=98&&tqId=33029&rp=1&ru=/activity/oj&qru=/ta/2019test/question-ranking) | 100% || 递归 |
| 2020-04-10 || ||
| | [1385. 两个数组间的距离值](https://leetcode-cn.com/problems/find-the-distance-value-between-two-arrays/)| | | 二分法 |
| | [1399. 统计最大组的数目](https://leetcode-cn.com/problems/count-largest-group/)| | | 没有什么知识点，简单 |
| | [1394. 找出数组中的幸运数](https://leetcode-cn.com/problems/find-lucky-integer-in-an-array/) | | | 超级简单，不推荐 |
| |[1396. 设计地铁系统](https://leetcode-cn.com/problems/design-underground-system/) | | | 简单，不推荐 |
| | [1375. 灯泡开关 III - 力扣（LeetCode）](https://leetcode-cn.com/problems/bulb-switcher-iii/) | | | 没有什么知识 |
| | [1377. T 秒后青蛙的位置 - 力扣（LeetCode）](https://leetcode-cn.com/problems/frog-position-after-t-seconds/) | | 不知道当时为什么没有做出来。可能是被无向树吓到了 | bfs 问题 | 
| | [图的遍历_美团_2019校招真题在线编程点评笔试题_牛客网](https://www.nowcoder.com/questionTerminal/5427af99168b45f4a14aec195b28a839?f=discussion) | 22min 0% |没有想到是无向图的遍历 | 推荐 bfs |
| | [1386. 安排电影院座位 - 力扣（LeetCode）](https://leetcode-cn.com/problems/cinema-seat-allocation/) |超时|没有看清数据范围|hash问题。可以使用位运算来装b|
| | [二分图判定_牛客网](https://www.nowcoder.com/practice/f4b8d0481c7b4278b9b406b636e3c7db?tpId=98&&tqId=32900&rp=2&ru=/activity/oj&qru=/ta/2019test/question-ranking) | AC 100% || 基础的bfs |
| | [2. 两数相加 - 力扣（LeetCode）](https://leetcode-cn.com/problems/add-two-numbers/) | | | 链表 加法进位类型 |
| | [445. 两数相加 II - 力扣（LeetCode）](https://leetcode-cn.com/problems/add-two-numbers-ii/) | | | 栈或者逆序的思路想不到 |
| | [66. 加一 - 力扣（LeetCode）](https://leetcode-cn.com/problems/plus-one/) | | | 简单的递归 |
| 2020-04-12 | |
| |[回文素数_爱奇艺_2018校招真题在线编程_牛客网](https://www.nowcoder.com/practice/4802faa9afb54e458b93ed372e180f5c?tpId=90&&tqId=30793&rp=2&ru=/activity/oj&qru=/ta/2018test/question-ranking) ||| 简单的判断。分别判断回文数和质数 |
| | [循环数比较_爱奇艺_2018校招真题在线编程_牛客网](https://www.nowcoder.com/practice/24575008c6134b6fa4fab8ea0ea82a99?tpId=90&&tqId=30788&rp=2&ru=/activity/oj&qru=/ta/2018test/question-ranking) | | |比较简单。逐位比较 |
| | [字符串组合_2018校招真题在线编程_牛客网](https://www.nowcoder.com/practice/837f4d04f5cb4f26a8215b2b95cc76a5?tpId=90&&tqId=30823&rp=1&ru=/activity/oj&qru=/ta/2018test/question-ranking)|||1. 按照长度来遍历，遍历区间为 [1, len(s)] 2. 使用 set 来去重。 python 中的set 不能排序，因此打印之前需要排序； c++ 中的 set 可以自动排序。因此无需排序。 | 
| 2020-04-13 |
| | [区间表达_爱奇艺_2018校招真题在线编程_牛客网](https://www.nowcoder.com/practice/826c2f28ee2a414cac87eb0304eca1a0?tpId=90&&tqId=30797&rp=2&ru=/activity/oj&qru=/ta/2018test/question-ranking) | | 比较基础，没有什么特殊的解法 | 
| 2020-04-14 | 
| | [257. 二叉树的所有路径 - 力扣（LeetCode）](https://leetcode-cn.com/problems/binary-tree-paths/) | ||判断叶结点 |
| | [100. 相同的树 - 力扣（LeetCode）](https://leetcode-cn.com/problems/same-tree/)| ||练习了二叉树 |
| | [101. 对称二叉树 - 力扣（LeetCode）](https://leetcode-cn.com/problems/symmetric-tree/) | ||练习了二叉树 |
| | [111. 二叉树的最小深度 题解 - 力扣（LeetCode）](https://leetcode-cn.com/problems/minimum-depth-of-binary-tree/) | ||判断叶结点|
| | [129. 求根到叶子节点数字之和 - 力扣（LeetCode）](https://leetcode-cn.com/problems/sum-root-to-leaf-numbers/) | ||判断叶结点|
| 2020-04-16 | |
| | [56. 合并区间 - 力扣（LeetCode）](https://leetcode-cn.com/problems/merge-intervals/)| | | 不是很难，贪心 | 
| | [种树_拼多多_2019校招真题在线编程_牛客网](https://www.nowcoder.com/practice/52f25c8a8d414f8f8fe46d4e62ef732c?tpId=98&tqId=32964&tPage=1&rp=1&ru=/ta/2019test&qru=/ta/2019test/question-ranking) |||回溯法。注意遇到第一个解就return。可以保证字典序最小|
| 2020-04-17 | |
| | [爬楼梯_小米_ 2019校招真题在线编程_牛客网](https://www.nowcoder.com/practice/b178fcef3ed4448c99d7c0297312212d?tpId=98&tqId=32905&rp=1&ru=%2Fta%2F2019test&qru=%2Fta%2F2019test%2Fquestion-ranking&tPage=5) | | | 简单的dp，但是为了防止整数溢出，需要自己写大数相加 |
| | [55. 跳跃游戏 - 力扣（LeetCode）](https://leetcode-cn.com/problems/jump-game/) | ||使用dp过不了|
| | [连续子数组最大和_流利说_2019校招真题在线编程 _牛客网](https://www.nowcoder.com/practice/03d341fb6c9d42debcdd38d82a0a545c?tpId=98&tqId=33068&tPage=1&rp=1&ru=/ta/2019test&qru=/ta/2019test/question-ranking) | | |基础的dp |
| 2020-04-19 | | | | |
|剑指offer | [替换空格_牛客网](https://www.nowcoder.com/practice/4060ac7e3e404ad1a894ef3e17650423?tpId=13&tqId=11155&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking) | | | 剑指offer|
|剑指offer | [从尾到头打印链表_牛客网](https://www.nowcoder.com/practice/d0267f7f55b3412ba93bd35cfa8e8035?tpId=13&tqId=11156&tPage=1&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking) | | | 比较简单，使用栈| 
|剑指offer | [重建二叉树_牛客网](https://www.nowcoder.com/practice/8a19cbe657394eeaac2f6ea9b0f6fcf6?tpId=13&tqId=11157&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking) | || 学习了c++find 的使用|
| 剑指offer| [旋转数组的最小数字_牛客网](https://www.nowcoder.com/practice/9f3231a991af4f55b95579b44b7a01ba?tpId=13&tqId=11159&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking&tPage=1) || | 二分法 | 
|剑指offer| [变态跳台阶_牛客网](https://www.nowcoder.com/practice/22243d016f6b47f2a6928b4313c85387?tpId=13&tqId=11162&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking) | | | dp，不难| 
|剑指offer| [矩形覆盖_牛客网](https://www.nowcoder.com/practice/72a5a919508a4251859fb2cfb987a0e6?tpId=13&tqId=11163&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking&tPage=1) | | | dp |
| 剑指offer | [二进制中1的个数_牛客网](https://www.nowcoder.com/practice/8ee967e43c2c4ec193b040ea7fbb10b8?tpId=13&tqId=11164&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking) || | 这个有更难理解的作法，还没有看|
|剑指offer | [链表中倒数第k个结点_牛客网](https://www.nowcoder.com/practice/529d3ae5a407492994ad2a246518148a?tpId=13&tqId=11167&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking&tPage=1) | | | 快慢指针 |
| 剑指offer | [树的子结构_牛客网](https://www.nowcoder.com/practice/6e196c44c7004d15b1610b9afca8bd88?tpId=13&tqId=11170&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking) ||| 推荐！感觉里面有什么规律，但是目前还无法总结出来|
| 剑指offer | [栈的压入、弹出序列_牛客网](https://www.nowcoder.com/practice/d77d11405cc7470d82554cb392585106?tpId=13&tqId=11174&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking)||| |
| 剑指offer | [合并两个排序的链表_牛客网](https://www.nowcoder.com/practice/d8b6b4358f774294a89de2a6ac4d9337?tpId=13&tqId=11169&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking) |||
| 剑指offer | [包含min函数的栈_牛客网](https://www.nowcoder.com/practice/4c776177d2c04c2494f2555c9fcc1e49?tpId=13&tqId=11173&tPage=1&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking) |||
| 剑指offer | [二叉树的镜像_牛客网](https://www.nowcoder.com/practice/564f4c26aa584921bc75623e48ca3011?tpId=13&tqId=11171&tPage=1&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking) | | |
| 剑指offer|[调整数组顺序使奇数位于偶数前面_牛客网](https://www.nowcoder.com/practice/beb5aa231adc45b2a5dcc5b62c93f593?tpId=13&tqId=11166&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking&tPage=1)| | | |
| 剑指offer | [从上往下打印二叉树_牛客网](https://www.nowcoder.com/practice/7fe2212963db4790b57431d9ed259701?tpId=13&tqId=11175&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking) | | | 简单的层次遍历 |
| 剑指offer | [第一个只出现一次的字符_牛客网](https://www.nowcoder.com/practice/1c82e8cf713b4bbeb2a5b31cf5b0417c?tpId=13&tqId=11187&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking&tPage=2) | || 简单，看不出有什么考点 |
| 剑指offer | [字符串的排列_牛客网](https://www.nowcoder.com/practice/fe6b651b66ae47d7acce78ffdd9a96c7?tpId=13&tqId=11180&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking&tPage=2)| ||| 回溯，推荐| 
| 剑指offer | [整数中1出现的次数（从1到n整数中1出现的次数）_牛客网](https://www.nowcoder.com/practice/bd7f978302044eee894445e244c7eee6?tpId=13&tqId=11184&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking&tPage=2) ||| dp。 todo logn 的算法想不到| 
| 剑指offer |[二叉搜索树与双向链表_牛客网](https://www.nowcoder.com/practice/947f6eb80d944a84850b0538bf0ec3a5?tpId=13&tqId=11179&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking&tPage=2) || | 书上的思路想不到。todo|
| 2020-04-20 | | | | | 
| | [200. 岛屿数量 - 力扣（LeetCode）](https://leetcode-cn.com/problems/number-of-islands/) | || bfs 或 并查集|
| 剑指offer | [两个链表的第一个公共结点_牛客网](https://www.nowcoder.com/practice/6ab1d9a29e88450685099d45c9e31e46?tpId=13&tqId=11189&tPage=2&rp=2&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking) | || |
| 剑指offer | [数字在排序数组中出现的次数_牛客网](https://www.nowcoder.com/practice/70610bf967994b22bb1c26f9ae901fa2?tpId=13&tqId=11190&tPage=2&rp=2&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking) ||| 二分法 |
| 2020-04-21 | |
| 剑指offer | [和为S的两个数字_牛客网](https://www.nowcoder.com/practice/390da4f7a00f44bea7c2f3d19491311b?tpId=13&tqId=11195&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking&tPage=3) || 两数之和。比起排序法，双指针比较重要 |
| | [590. N叉树的后序遍历 - 力扣（LeetCode）](https://leetcode-cn.com/problems/n-ary-tree-postorder-traversal/) | | | |
| 剑指offer | [二叉树的深度_牛客网](https://www.nowcoder.com/practice/435fb86331474282a3499955f0a41e8b?tpId=13&tqId=11191&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking&tPage=2) | | 看了关于颜色标记法的题目 | 
| 2020-04-24 | |
| Leetcode-剑指offer | [面试题51. 数组中的逆序对 - 力扣（LeetCode）](https://leetcode-cn.com/problems/shu-zu-zhong-de-ni-xu-dui-lcof/) | | | 这个比较难 |
| Leetcode-剑指offer | [面试题58 - I. 翻转单词顺序 - 力扣（LeetCode）](https://leetcode-cn.com/problems/fan-zhuan-dan-ci-shun-xu-lcof/)| | | 滑动窗口 |
| Leetcode-剑指offer | [面试题58 - II. 左旋转字符串 - 力扣（LeetCode）](https://leetcode-cn.com/problems/zuo-xuan-zhuan-zi-fu-chuan-lcof/) | | | 很简单 |
| Leetcode-剑指offer | [面试题61. 扑克牌中的顺子.md](Leetcode/Leetcode%20面试题61.%20扑克牌中的顺子.md)| | 没有什么知识点|
| 2020-04-25 | |
| Leetcode-剑指offer | [Leetcode 343. 整数拆分.md](Leetcode/Leetcode%20343.%20整数拆分.md) | | ||
| Leetcode-剑指offer | [Leetcode 160. 相交链表.md](Leetcode/Leetcode%20160.%20相交链表.md) | | ||
| Leetcode-剑指offer | [面试题41. 数据流中的中位数 - 力扣（LeetCode）](https://leetcode-cn.com/problems/shu-ju-liu-zhong-de-zhong-wei-shu-lcof/) | [面试题41. 数据流中的中位数.md](Leetcode/面试题41.%20数据流中的中位数.md) | | 堆;二分法;中位数 |
| Nowcoder-剑指offer | [Nowcoder 两个链表的第一个公共结点.md](Leetcode/Nowcoder%20两个链表的第一个公共结点.md) | | ||
| 2020-04-26 | | | |
| | [Leetcode 21. 合并两个有序链表.md](Leetcode/Leetcode%2021.%20合并两个有序链表.md) | | 基础的链表题；注意设置头指针| 链表 |
| | [23. 合并K个排序链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/merge-k-sorted-lists/)| [Leetcode 23. 合并K个排序链表.md](Leetcode/Leetcode%2023.%20合并K个排序链表.md) | | 学习了c++中priority_queue 的使用 | 堆;分治|
| Leetcode 周赛| [Leetcode 5394. 对角线遍历 II.md](Leetcode/Leetcode%205394.%20对角线遍历%20II.md) | | ||
| Leetcode 周赛| [5180. 带限制的子序列和 - 力扣（LeetCode）](https://leetcode-cn.com/problems/constrained-subset-sum/) | [Leetcode 5180. 带限制的子序列和.md](Leetcode/Leetcode%205180.%20带限制的子序列和.md) | | 单调队列 |
| Leetcode 周赛| [5392. 分割字符串的最大得分 - 力扣（LeetCode）](https://leetcode-cn.com/problems/maximum-score-after-splitting-a-string/) | [Leetcode 5392. 分割字符串的最大得分.md](Leetcode/Leetcode%205392.%20分割字符串的最大得分.md) | | 这个比较简单。没有什么知识点 |
| 推荐Leetcode 周赛| [5180. 带限制的子序列和 - 力扣（LeetCode）](https://leetcode-cn.com/problems/constrained-subset-sum/) | | | 单调队列 |
| Leetcode-剑指offer | [面试题41. 数据流中的中位数 - 力扣（LeetCode）](https://leetcode-cn.com/problems/shu-ju-liu-zhong-de-zhong-wei-shu-lcof/) | [Leetcode 面试题41. 数据流中的中位数.md](Leetcode/Leetcode%20面试题41.%20数据流中的中位数.md) | | 单调队列 |
| 推荐 面试被问到了 | [25. K 个一组翻转链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/reverse-nodes-in-k-group/) | [Leetcode 25. K 个一组翻转链表.md](Leetcode/Leetcode%2025.%20K%20个一组翻转链表.md) | 学到了断链操作 | 链表 |
| 推荐 | [92. 反转链表 II - 力扣（LeetCode）](https://leetcode-cn.com/problems/reverse-linked-list-ii/)| [Leetcode 92. 反转链表 II.md](Leetcode/Leetcode%2092.%20反转链表%20II.md) | | 链表 |
| 2020-04-27 | | | |
| 推荐 | [33. 搜索旋转排序数组 - 力扣（LeetCode）](https://leetcode-cn.com/problems/search-in-rotated-sorted-array/) | [Leetcode 33. 搜索旋转排序数组.md](Leetcode/Leetcode%2033.%20搜索旋转排序数组.md) |       |  二分法   | 
| 推荐 |  [876. 链表的中间结点 - 力扣（LeetCode）](https://leetcode-cn.com/problems/middle-of-the-linked-list/) | [Leetcode 876. 链表的中间结点.md](Leetcode/Leetcode%20876.%20链表的中间结点.md) |       |    链表;快慢指针  |   
| 推荐 | [206. 反转链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/reverse-linked-list/) | [Leetcode 206. 反转链表.md](Leetcode/Leetcode%20206.%20反转链表.md) |    注意要调整head->next=NULL!   |     递归    |
| 推荐 |   [148. 排序链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/sort-list/) | [Leetcode 148. 排序链表.md](Leetcode/Leetcode%20148.%20排序链表.md) |       |   链表;归并排序   |   
| 比较推荐 |  [75. 颜色分类 - 力扣（LeetCode）](https://leetcode-cn.com/problems/sort-colors/) | [Leetcode 75. 颜色分类.md](Leetcode/Leetcode%2075.%20颜色分类.md) |   学到了switch使用;学习了循环不变式的使用,具体可以看 [快速排序 partition 过程（重点在设计循环不变量） - 颜色分类 - 力扣（LeetCode）](https://leetcode-cn.com/problems/sort-colors/solution/kuai-su-pai-xu-partition-guo-cheng-she-ji-xun-huan/)  |   双指针;快排 |  
| |  [61. 旋转链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/rotate-list/) | [Leetcode 61. 旋转链表.md](Leetcode/Leetcode%2061.%20旋转链表.md) |       |      | 
| 推荐！可以综合三个链表题的知识 |    [143. 重排链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/reorder-list/) | [Leetcode 143. 重排链表.md](Leetcode/Leetcode%20143.%20重排链表.md) |       |   链表  |  
| 比较推荐 |  [83. 删除排序链表中的重复元素 - 力扣（LeetCode）](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list/) | [Leetcode 83. 删除排序链表中的重复元素.md](Leetcode/Leetcode%2083.%20删除排序链表中的重复元素.md) | 比较简单的链表  |   链表  |  
| 比较推荐 |  [82. 删除排序链表中的重复元素 II - 力扣（LeetCode）](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list-ii/) | [Leetcode 82. 删除排序链表中的重复元素 II.md](Leetcode/Leetcode%2082.%20删除排序链表中的重复元素%20II.md) |       |    链表  |       
| Leetcode-剑指offer  | [面试题18. 删除链表的节点 - 力扣（LeetCode）](https://leetcode-cn.com/problems/shan-chu-lian-biao-de-jie-dian-lcof/) | [Leetcode 面试题18. 删除链表的节点.md](Leetcode/Leetcode%20面试题18.%20删除链表的节点.md) |       |    链表  |  
| Leetcode-剑指offer| [面试题35. 复杂链表的复制 - 力扣（LeetCode）](https://leetcode-cn.com/problems/fu-za-lian-biao-de-fu-zhi-lcof/) | [Leetcode 面试题35. 复杂链表的复制.md](Leetcode/Leetcode%20面试题35.%20复杂链表的复制.md) |    这个比较难想到   |   链表 |     
| | [86. 分隔链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/partition-list/) | [Leetcode 86. 分隔链表.md](Leetcode/Leetcode%2086.%20分隔链表.md) |    注意断链！   |    链表  |  
|   |  [234. 回文链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/palindrome-linked-list/)   | [Leetcode 234. 回文链表.md](Leetcode/Leetcode%20234.%20回文链表.md) |       |   链表   |     
| 2020-04-28 | | | |
| Leetcode-剑指offer | [面试题52. 两个链表的第一个公共节点 - 力扣（LeetCode）](https://leetcode-cn.com/problems/liang-ge-lian-biao-de-di-yi-ge-gong-gong-jie-dian-lcof/comments/) | [Leetcode 面试题52. 两个链表的第一个公共节点.md](Leetcode/Leetcode%20面试题52.%20两个链表的第一个公共节点.md) |   套路    |    链表  |   
