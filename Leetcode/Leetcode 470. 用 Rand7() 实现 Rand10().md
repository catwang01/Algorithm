[toc]

# Leetcode 470. 用 Rand7() 实现 Rand10()

## 问题描述

[470. 用 Rand7() 实现 Rand10() - 力扣（LeetCode）](https://leetcode-cn.com/problems/implement-rand10-using-rand7/)

# Todo - 2020-04-29 14:35 -- by ed  没有想到怎么叙述比较好

## 算法

### 解法1: 拒绝采样

调用一次只能得到 1 到 7 的随机数，考虑调用两次。

使用 7 进制数可以让两个数字的地方不相同。

#### 解法1:实现1: 7进制数

##### 解法1: c++

```
class Solution {
public:
    int rand10() {
        int ret;
        while (true) {
            ret = (rand7()-1) * 7+ (rand7() - 1);
            if (ret >= 1 && ret <= 40) 
                return ret % 10 ? ret % 10: 10;
        }
        return 0;
    }
};
```

