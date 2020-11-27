[toc]

# Leetcode 209. 长度最小的子数组

## 问题描述

[209. 长度最小的子数组 - 力扣（LeetCode）](https://leetcode-cn.com/problems/minimum-size-subarray-sum/)

给定一个含有 n 个正整数的数组和一个正整数 s ，找出该数组中满足其和 ≥ s 的长度最小的连续子数组。如果不存在符合条件的连续子数组，返回 0。

示例: 

输入: s = 7, nums = [2,3,1,2,4,3]
输出: 2
解释: 子数组 [4,3] 是该条件下的长度最小的连续子数组。

进阶:
如果你已经完成了 $O(n)$ 时间复杂度的解法, 请尝试 $O(nlog n)$ 时间复杂度的解法。

## 算法

### 解法一：bruteforce

时间复杂度： $O(n^3)$
空间复杂度： $O(1)$

#### 解法一c++

超时
 
```
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int n = nums.size();
        if (n==0) return 0;
        int minLen = INT_MAX;
        for (int i=0; i<n; i++) {
            for (int j=i; j<n; j++) {
                int subsum = 0;
                for(int k=i; k<=j; k++) {
                    subsum += nums[k];
                }
                if (subsum >= s && j-i+1 < minLen) {
                    minLen = j-i+1;
                }
            }
        } 
        if (minLen == INT_MAX) return 0;
        else return minLen;
    }
};
```

### 解法一前缀数组优化

上面求部分和用了累加；有许多重复计算，可以利用前缀数组来代替，减低时间复杂度


时间复杂度：$O(n^2)$
空间复杂度：$O(n)$ 用了一个数组来保存前缀和

```
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int n = nums.size();
        if (n==0) return 0;
        int prefixSum[n+1] = {0}; // 添加一项0
        for (int i=1; i<n+1; i++) {
            prefixSum[i] = prefixSum[i-1] + nums[i-1];
        } 
        int minLen = INT_MAX;
        for (int i=1; i<n+1; i++) {
            for (int j=i; j<n+1; j++) {
                int subsum = prefixSum[j] - prefixSum[i-1];
                if (subsum >= s && j-i+1 < minLen) {
                    minLen = j-i+1;
                }
            }
        } 
        if (minLen == INT_MAX) return 0;
        else return minLen;
    }
};
```

### 解法一二分法优化

上面的解法一中遍历了 i,j；可以使用二分法来代替；思路如下：

对于任意一个i，想要求最小的 j，满足 prefixSum[j] - prefixSum[i-1] >= s，即 prefixSum[j] >= s + prefixSum[i-1]

这相当于一个二分法的问题：给定 target，在已排序的数组 A 中寻找满足 A[j] >= target 最小的 j 

时间复杂度： $O(nlogn)$
空间复杂度： $O(n)$

#### 解法一二分法优化c++

```
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int n = nums.size();
        if (n==0) return 0;
        int prefixSum[n+1] = {0}; // 添加一项0
        for (int i=1; i<n+1; i++) {
            prefixSum[i] = prefixSum[i-1] + nums[i-1];
        } 
        int minLen = INT_MAX;
        for (int i=1; i<n+1; i++) {
            int j = bisearch(prefixSum, i, n, s + prefixSum[i-1]);
            if (j!=-1 && j-i+1 < minLen) {
                minLen = j-i+1;
            }
        } 
        if (minLen == INT_MAX) return 0;
        else return minLen;
        // 测试二分法是正确
        // int A[] = {1,2,3};
        // for (int i=0; i<5; i++) {
        //     cout << i << ": " << bisearch(A, 0, 2, i) << endl;
        // }
        // return 0;
    }

    int bisearch(int A[], int low, int high, int target) {
        if (target > A[high]) return -1;
        while (low < high) {
            int mid = low + (high - low) / 2;
            if (A[mid] < target) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        return low;
    }
};
```

### 解法二：滑动窗口

时间复杂度： $O(n)$
空间复杂度： $O(1)$

#### 解法2: 实现1： while 循环扩展窗口

![098360058362399ca286eba309e5eddc.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p10470)
 
![20589f37fc838e415e62b9eb07b81ed1.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p10471)

##### 解法2：实现1:python

```
class Solution:
    def minSubArrayLen(self, s: int, nums: List[int]) -> int:
        n = len(nums)
        left = right = 0
        ret = n + 1
        window = 0
        while left < n:
            while right < n and window + nums[right] < s:
                window += nums[right]
                right += 1
            # right == n or window + nums[right] >= s
            if right < n:
                ret =  min(ret, right - left + 1)
                window -= nums[left]
                left += 1
            else:
                break
        return ret if ret < n + 1 else 0
```


#### 解法2: 实现2: while 循环收缩窗口

扩张窗口：为了找到一个可行解，找到了就不再扩张
收缩窗口：在长度上优化该可行解，直到条件被破坏
寻找下一个可行解，然后再优化到不能优化……

##### 解法2: 实现2: python

```
class Solution:
    def minSubArrayLen(self, s: int, nums: List[int]) -> int:
        n = len(nums)
        left = right = 0
        ret = n + 1
        window = 0
        while right < n:
            window += nums[right]
            while window >= s:
                ret = min(ret, right - left + 1)
                window -= nums[left]
                left += 1
            right += 1
        return ret if ret < n + 1 else 0
```
