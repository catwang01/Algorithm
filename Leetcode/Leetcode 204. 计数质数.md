
[toc]

# Leetcode 204. 计数质数

## 问题描述

[204. 计数质数 - 力扣（LeetCode）](https://leetcode-cn.com/problems/count-primes/)

## 算法

### 解法1: 逐个判断

#### 解法1:实现1:最简单的逐个判断

##### 解法1: c++

超时

```
class Solution {
public:
    int countPrimes(int n) {
        if (n <= 2) return 0; // 特判
        vector<int> primes;
        primes.push_back(2);
        for (int i=3; i<n; i++) {
            bool flag = true;
            for (int prime: primes) {
                if (i % prime == 0) {
                    flag = false;
                    break;
                }
            }
            if (flag) primes.push_back(i);
        }
        return primes.size();
    }
};
```

#### 解法1:实现2:小优化

注意到只需要判断那些满足 $prime \le \left\lceil \sqrt{x}  \right\rceil$ 的质数。

##### 解法1: c++

```
class Solution {
public:
    int countPrimes(int n) {
        if (n <= 2) return 0; // 特判
        vector<int> primes;
        primes.push_back(2);
        int j = 0;
        for (int i=3; i < n; i++) {
            bool flag = true;
            j = 0;
            while (j < primes.size() && primes[j] * primes[j] <= n) {
                if (i % primes[j] == 0) {
                    flag = false;
                    break;
                }
                j++;
            }
            if (flag) primes.push_back(i);
        }
        return primes.size();
    }
};
```

### 解法2: 厄拉多塞筛法

对于一个质数来说 prime 来说，prime 的倍数都应该被排除。

#### 解法2:实现1

##### 解法2: 实现1：c++

```
class Solution {
public:
    int countPrimes(int n) {
        if (n<=2) return 0;
        vector<bool> nums(n, true);

        int ret = 0;
        for (int i=2; i < n; i++) {
            if (nums[i]) { // 排除 prime 的倍数
                for (int j=i*2; j<n; j+=i) {
                    nums[j] = false;
                }
                ret++;
            }
        }
        return ret;
    }
};
```

##### 解法2: 实现1：python

```
class Solution:
    def countPrimes(self, n: int) -> int:
        if n <= 1:
            return 0
        hashtab = [1] * n
        ret = n - 2
        for i in range(2, n):
            x = i + i
            while x < n:
                if hashtab[x]: 
                    hashtab[x] = 0
                    ret -= 1
                x += i
        return ret
```