[toc]

# Leetcode 402. 移掉K位数字

## 问题描述

[402. 移掉K位数字 - 力扣（LeetCode）](https://leetcode-cn.com/problems/remove-k-digits/)

## 解法1: 贪心1

### 解法1:

考虑选择第一个数。我们需要在**所有可能的第一个数的数**中选择最小的那个。

而第一个数的可能值为 num[0], ..., num[n-(k-1)-1] （后 k - 1 个数挑出来保底）

在其中选择最小的数作为第一位数，假设这个数为 num[i]，那么接下来的问题转换为在 num[i+1, ..., n-1] 上规模为 k 的一个子问题。

时间复杂度：最坏时间复杂度 $O(n^2)$ 当数字为单调递增时取到
空间复杂度：$O(1)$

#### 解法1: 实现： $O(n^2)$ 实现

##### 解法1: 实现：c++

```
class Solution {
public:
    string removeKdigits(string num, int k) {
        if (num.size() <= k) return "0"; // 全部删除
        string ret;
        helper(0, num.size(), num, ret, num.size() - k);
        int i=0;
        while (ret.size() && ret[i] == '0') i++;
        return ret.size()==i ? "0" : ret.substr(i, ret.size()-i);
    }
    
    void helper(int i, int j, const string& num, string& ret, int k) // num[i:j]
    {
        if (k==0) return;
        int idx=i;
        for (int l=i; l<j-(k-1); l++)
        {
            if (num[l] < num[idx]) idx = l;
        }
        ret += num[idx];
        helper(idx+1, j, num, ret, k-1);
    }
};
```

##### 解法1: 实现：c++: stl 写法

```
class Solution {
public:
    string removeKdigits(string num, int k) {
        if (num.size() <= k) return "0"; // 全部删除
        string ret;
        helper(num.begin(), num.end(), ret, num.size() - k);
        int i=0;
        while (ret.size() && ret[i] == '0') i++; // 去掉前导零
        return ret.size()==i ? "0" : ret.substr(i, ret.size()-i); // 去掉前导0后是否为空
    }
    
    void helper(string::iterator i, string::iterator j, string& ret, int k) // num[i:j]
    {
        if (k==0) return;
        auto pMin = min_element(i, j-(k-1));
        ret += *pMin;
        helper(pMin+1, j, ret, k-1);
    }
};
```

#### 解法1: 实现2: 单调队列优化

上面的之所以是 $O(n^2)$ 复杂度，是因为需要在不同的窗口中求许多次最小值，由于窗口会重叠，因此会有许多重复计算。

考虑如何优化这个计算。这个实际上类似与滑动窗口的最小值的问题。只不过这个窗口大小不是固定的。

初始情况下，我们的窗口为 [0, n-s+1)，我们需要求这个窗口的最小值。假设这个窗口中的最小值的 idx 为 i，那么我们下一个窗口为 [i+1, n-s+2)

时间复杂度：$O(n)$
空间复杂度：$O(n)$

##### 解法1: 实现2: c++

```
class Solution {
public:
    string removeKdigits(string num, int k) {
        int n = num.size();
        if (n <= k) return "0"; // 全部删除
        deque<int> st;
        string ret;
        int i = 0, j;
        int s = n - k; // 选取的个数
        while (s) // 选取个数为0时退出
        {
            j = i;
            while (j < n - (s - 1))
            {
                while (j < n - (s - 1) && st.size() && num[st.back()] > num[j])
                    st.pop_back();
                st.push_back(j++);
            }
            s--;
            ret += num[st.front()]; st.pop_front(); // 最小的加入结果
            i = j;
        }
        i = 0;
        while (ret.size() && ret[i] == '0') i++; // 去掉前导零
        return ret.size()==i ? "0" : ret.substr(i, ret.size()-i); // 去掉前导0后是否为空
    }
};
```

##### 解法2：实现：window 类

```
class Window {
    public:
        string num;
        int size, right, left;
        deque<int> minDq;
        Window(string num): num(num), size(0), left(0), right(0) {}
        void moveright()
        {
            while (minDq.size() && num[minDq.back()] > num[right])
                minDq.pop_back();
            minDq.push_back(right);
            right++; size++;
        }
        
        int minIdx() { 
            return minDq.size() ? minDq.front(): -1; 
        }

        void moveleft() {
            if (left == minIdx()) 
                minDq.pop_front();
            left++; size--;
        }

};
class Solution {
public:
    string removeKdigits(string num, int k) {
        int n = num.size();
        if (n <= k) return "0"; // 全部删除
        string ret;
        Window window(num);
        int s = n - k;
        while (s)
        {
            window.moveright();
            if (window.right == n - (s - 1))
            {
                int idx = window.minIdx();
                ret += num[idx];
                while (idx == window.minIdx())  window.moveleft();
                s--;
            }
        }
        int i = 0;
        while (ret.size() && ret[i] == '0') i++; // 去掉前导零
        return ret.size()==i ? "0" : ret.substr(i, ret.size()-i); // 去掉前导0后是否为空
    }
};
```