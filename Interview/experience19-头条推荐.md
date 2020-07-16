[toc]

[今日头条推荐系统算法岗日常实习面试经验_da_kao_la的博客-CSDN博客_头条 推荐算法面试](https://blog.csdn.net/da_kao_la/article/details/88858220?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-6.edu_weight&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-6.edu_weight)

今日头条推荐系统算法岗日常实习面试经验

## 一面
深度学习基础
Adam的原理、公式 (没答上来)

找了一个简书的讲解，挺好的，有需要的同学可以移步简单认识Adam优化器

Dropout的原理 (为什么训练时有dropout测试时没有dropout，这样会发生scale的偏移吗)

答：不会，因为训练时dropout机制会把dropout_rate = p的输出乘以1/(1-p)

Batch Normalization的原理

答：在mini_batch上进行而不是在整个数据集上进行。在训练集上有BN测试集上没有BN，这样不会发生数值上的偏移，道理类似dropout，即记录下训练集上的BN参数（均值、标准差、\beta、\gamma）作为网络参数的一部分。

为什么要用ReLU替代tanh/sigmoid/softmax

答：ReLU求导的值要么是0要么是1，不会引起梯度消失或梯度爆炸

ResNet

答：通过x + f(x)的结果，让深层网络获得不差于浅层网络的学习能力，从而允许网络变得更深

算法题
给定数组nums和整数target，求最少用nums中的整数多少次，使得这些数之和为target。比如给定nums = [3, 5, 12], target = 13, 答案为3 (13 = 3 + 5 + 5)

答：BFS求最少的组合（我答得太啰嗦了，面试官就没让写代码）

标准答案是动态规划，其实是动态规划里面很经典的问题，当时没想起来（汗）
附动态规划的题解

class Solution {
   public int coinChange(int[] nums, int target) {
       int[] dp = new int[target + 1];
       Arrays.fill(dp, 0x3f3f3f3f);
       dp[0] = 0;
       Arrays.sort(nums);
       int i = 0;
       for (i = 1; i <= target; ++i) {
           for (int c: nums) {
               if (i >= c) {
                   dp[i] = Math.min(dp[i], dp[i-c] + 1);
               } else {
                   break;
               }
           }
       }
       return dp[target] == 0x3f3f3f3f? -1: dp[target];
   }
}

结果是面试官换了一道题

给定一个Y形链表和Y头部两个头指针，求第一个汇合点

答：用两个指针r1, r2从两个头指针开始遍历（不妨记两个头指针为l1, l2），计算从l1, l2出发Y形链表的长度len1, len2. 不妨设len1 < len2, 则先将l2移动(len2 - len1)次，再将l1, l2同步移动，直到l1 == l2.

## 二面

矩阵求逆是如何操作的？【答：高斯消元】描述过程？【答：左边一个A，右边一个I，消消消，消到左边的A变成I，右边的I就变成了A的逆矩阵】为什么可以这样算？如何证明？

答：高斯消元由矩阵行变换组成，矩阵行变换等价于左乘另外一个系数矩阵，所以当左边的A变到I，A就左乘了A的逆矩阵，同时右边的I也左乘了A的逆矩阵得到A的逆矩阵。这就是高斯消元法的原理。（马后炮分析，面试的时候没答上来，是面试官提示的）

一个负载均衡里面产生的数学问题：现在有两台服务器A和B，后台算法是A和B都有1/2的概率被访问，如果访问的服务器宕机，则会以1/2的概率继续请求两个服务器。现在服务器B宕机了，求平均访问的次数？

答：这是一个随机变量求期望的问题。记平均访问的次数为p，

​ p = 1/2 * 1 + (1/2)^2 * 2 + (1/2)^3 * 3 + … + (1/2)^n * n + …

令q = 1/2 * p = (1/2)^2 * 1 + (1/2)^3 * 2 + … + (1/2)^n * (n-1) + …

故p = 2 (p - q) = 2 * [1/2 + (1/2)^2 + (1/2)^3 + …] = 2 * (1/2)/[1 - (1/2)] = 2

merge两个有序数组，写代码，写测试用例，【有bug抛了个ArrayIndexOutOfBound异常，于是改改改】改了哪里？这里的while替换成if可不可以？【答：可以】

计算n个节点的二叉树有多少种形态？【答：递推，在面试官提醒下写出递推式】写代码，写测试用例

public class Main {
    private static int[] dp;
    public static int dynamic_programming(int n)  
    {
        dp = new int[n+1];
        dp[0] = 1;
        dp[1] = 1;
        for (int i=2; i<=n; i++)
        {
            for (int j=0; j<i; j++)
            {
                dp[i] += dp[j] * dp[i-1-j];
            }
        }
        return dp[n];
    }
    
    public static void main(String[] args) {
        int n = 4;
        System.out.println(dynamic_programming(n));		// 14
    }
};

如果让你设计推荐系统，将100个图片按顺序推荐给100个用户，如何设计算法？【答：什么什么矩阵，术语忘了。。。】100万个图片和100万个用户呢？【答：稀疏矩阵】计算这个矩阵的时候，用户的哪些信息可以利用？【浏览、点击、搜索；个人信息】社交媒体可以利用吗？【可以，好友偏好，群组偏好】

## 三面

Python的shuffle函数内部是如何实现的？【呃。。。没有读过shuffle的源码】说说如果你来实现，你会如何实现？【每次random出一个index，和shuffle过的数组未shuffle部分的头交换】如何评价你提出的算法shuffle的性能？【首先定义两个数组间的“相似度”为两数组各个位置相同的数的个数，运行N次shuffle算法，计算得到的N个无序数组两两之间的相似度之和S，S越小，shuffle算法的无序性越好】

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

两个字符串的编辑距离：给定两个字符串s1, s2，定义三种操作：增（一个字符）、删（一个字符）、改（一个字符变另一字符），求从s1变到s2最少需要的操作次数？【答：动态规划】写出状态转移方程？【写了伪码】看看这一行是不是可以优化？【想想想，好像是可以优化】嗯，是这样的

针对我的一作在投论文提的问题：基于深度学习的图学习方法为什么优于传统基于图谱理论的标签传播算法？

答：（不知道对不对，瞎答的）

时间开销上，图谱理论要计算矩阵求逆，时间开销大，深度学习都是矩阵乘法
分类精度上，由于图割问题是非凸问题，图谱理论将其转化成凸问题求解，存在对偶间隙；深度学习模型直接拟合非凸函数
后记
2019年3月28日更新：上午通过电话进行了40分钟的HR面，重点问了面试自评（面试中自己感觉最闪光的地方和不足的地方）和大学学习生活（为什么选择软件工程专业，如果让你给外行人讲解软件工程专业是做什么的，你会如何说），比较轻松，主要就是聊聊天；下午收到HR通知，通过面试，开始走入职审批流程。人生中的第一次实习面试就这样结束了，回想起来真是梦一般的感觉呢~今后也要继续加油啦