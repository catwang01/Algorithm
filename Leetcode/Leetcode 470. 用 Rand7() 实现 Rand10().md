[toc]

# Leetcode 470. 用 Rand7() 实现 Rand10()

## 问题描述

[470. 用 Rand7() 实现 Rand10() - 力扣（LeetCode）](https://leetcode-cn.com/problems/implement-rand10-using-rand7/)

## 算法

### 解法1: 拒绝采样

#### 解法1:实现1: 7进制数

调用一次只能得到 1 到 7 的随机数，考虑调用两次。

使用 7 进制数可以让两个数字的地位不相同。
为什么要使用七进制？因为我们可以得到 [1, 7] 上的均匀分布，相当于可以得到 [0, 6] 上的均匀分布，由于 7 进制数是由 0 - 6 构成的，因此一个两位的 7 进制数可以表示为

```
(rand7()-1) * 7 + rand7() - 1
```

由于两位 7 进制数可以表示 0-48 之间的数，因此可以直接返回 `[1,10]` 的数，不在这个范围内的丢掉。

但是，这样抽样的拒绝率偏高，效率比较低。可以考虑将不在 `[1,10]` 范围的均匀地映射到这个范围内。

可以考虑使用取模运算 `%` 来进行映射。由于 `x % n` 可以将 x 映射到 `[0, n-1]` 上。而我们希望映射到 `[1, 10]` 上。因此可以考虑 `ret % 10` 将 ret 映射到 `[0, 9]` 之后再加 1。

要均匀地映射，可以取 ret 在 `[0, 39]` 这个范围中的数。

##### 解法1: c++

```
class Solution {
public:
    int rand10() {
        int ret;
        while (true) {
            ret = (rand7()-1) * 7 + (rand7() - 1);
            if (ret >= 0 && ret <= 39) 
                return ret % 10 + 1;
        }
        return 0;
    }
};
```

##### 解法1: python

```
class Solution:
    def rand10(self):
        while True:
            x1 = rand7() - 1
            x2 = rand7() - 1
            ret = x1 * 7 + x2
            if 0 <= ret <= 39:
                ret = ret % 10 + 1
                break
        return ret
```
