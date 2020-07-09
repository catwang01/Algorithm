[toc]

# Leetcode 84. 柱状图中最大的矩形

## 问题描述

[84. 柱状图中最大的矩形 - 力扣（LeetCode）](https://leetcode-cn.com/problems/largest-rectangle-in-histogram/)


## 算法

### 法一：bruteforce

穷举i,j，计算区间 `a[i]，...，a[j]` 对应的矩形的面积

时间复杂度：$O(n^3)$
两层循环，复杂度为 $\Theta(n^2)$；求最小值和求和两种操作的复杂度合起来为 $O(n)$，总的复杂度为 $O(n^3)$
空间复杂度：$O(1)$

#### 解法1: 实现

##### 解法1: python

```
class Solution:
    def largestRectangleArea(self, heights: List[int]) -> int:
        n = len(heights)
        max_s = 0
        for i in range(n):
            for j in range(i+1, n+1):
                s = min(heights[i:j]) * (j-i)
                max_s = max(max_s, s)
        return max_s
```

### 解法2： 小改进——分类（中心扩散法）（超时）

#### 解法2: 实现

bruteforce方法遍历了所以可能的解来计算最优解。我们对解进行分类，并计算每类中的最优解，并对每类的最优解求最优解来得到全局最优解。

可以**以柱子i为最小值的连续柱子构成的矩形为一类**这样分类的好处时在同一类中，矩形的高是固定的，都是 `heights[i]`

在这个类中，最优解是显然的，只需要使宽度为从当前位置向左右两边扩散，直到到达比自己小的或者到达边界为止。

设 left 为第i个柱子左侧比它小的柱子的最大的下标，即左侧第一个小于 heights[i] 的数的下标。
$$left = max_{-1 \le k \le i-1} \{k: heights[k] < heights[i]\}$$

如果不存在这样的数，则规定 left = -1，这样规定的好处是可以和其实情况一起处理，不需要单独讨论。

类似的，定义 right 为第i个柱子左侧比它小的柱子的最小的下标，即

$$right = min_{i+1 \le k \le n-1} \{k: heights[k] < heights[i]\}$$

如果不存在这样的数，则规定 right = n，这样规定的好处是可以和其实情况一起处理，不需要单独讨论。

则第 i 类对应的最优解为 $heights[i] * (right - left -1)$

下面给出一个例子

![d64ecfc7a9869efaf17f9d5b7193f279.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p10516)


##### 解法2: python

```
class Solution:
    def largestRectangleArea(self, heights: List[int]) -> int:
        result = 0
        n = len(heights)
        for i in range(n):
            # left是小于heights[i]的柱子坐标的最大值
            left = i-1
            # right是小于heights[i]的柱子坐标的最小值
            right = i+1 
            while left >=0 and heights[left] >= heights[i]:
                left -= 1
            while right < n and heights[right] >= heights[i]:
                right += 1
            result = max(result, (right - left - 1)* heights[i])
        return result
```

##### 解法2: c++

注意这个实现和上面的有点小不同。上面的实现左右区间都包含，而这个实现左区间包含，右区间不包含。

```cpp
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        if (!n) return 0;
        if (n==1) return heights[0];
        int ret = 0;
        for (int i=0; i<n; i++) 
        {
            int l = i, r = i + 1; // l 包含 j 不包含
            while (l-1>=0 && heights[l-1] >= heights[i]) 
            {
                l--;
            }
            // l - 1 < 0 || heights[l-1] < heights[i]
            while ( r < n && heights[r] >= heights[i]) 
            {
                r++;
            }
            // r == n || heights[r] < heights[i]
            ret = max(ret, (r-l) * heights[i]);
        }
        return ret;
    }
};
```

### 解法2：法2再改进

之前我们计算 left, right 时，每次都重新遍历i-1, i-2, i-3, ..., 0，冗余计算多；

实际上，我们可以得上一次计算的left和right的结果，由于需要利用到历史数据，所以可以用n元列表保存left，right的值。

![8d8fea86217bbf32df5c0cbe627a1de0.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p10517)

```
class Solution:
    def largestRectangleArea(self, heights: List[int]) -> int:
        n = len(heights)
        if n == 0:
            return 0
        if n == 1:
            return heights[0]
        left, right = [None] * n, [None] * n
        # 计算left列表
        left[0] = -1
        for i in range(1, n):
            j = i - 1
            while j>=0 and heights[j] >= heights[i]: # 注意这里是等于
                j = left[j]
            left[i] = j

        # 计算right列表
        right[-1] = n
        for i in range(n-2, -1, -1):
            j = i+1
            while j<n and heights[i] <= heights[j]: # 注意这里是等于
                j = right[j]
            right[i] = j

        return max([heights[i] * (right[i] - left[i] - 1) for i in range(n)])
```

### 解法4：单调栈——1

#### 解法4:实现

实际上思路和法二是一样的，只不过使用了单调栈来计算left和right

```cpp
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        if (!n) return 0;
        if (n==1) return heights[0];

        int ret = 0;
        stack<int> st;
        vector<int> left_first_smaller(n, -1), // 默认值为-1
                    right_first_smaller(n, n); // 默认值为 n

        for (int i=0; i<n; i++) 
        {
            while (!st.empty() && heights[st.top()] > heights[i]) 
            {
                right_first_smaller[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
        while (!st.empty()) st.pop();
        
        for (int i=0; i<n; i++)
        {
            while (!st.empty() && heights[st.top()] >= heights[i]) 
            {
                st.pop();
            }
            if (!st.empty()) left_first_smaller[i] = st.top();
            st.push(i);

        }
        
        for (int i=0; i<n; i++)
        {
           ret = max(ret, heights[i] * (right_first_smaller[i] - left_first_smaller[i] - 1));
        }
        return ret;
    }
};
```

### 解法5: 单调栈——2

注意在 `heights` 数组末尾添加了-1，用来将所有的元素出栈。

#### 解法5:实现

```cpp
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        heights.push_back(-1); // heights最后添加一个-1，小于所有的元素，用来将所有的index从栈内弹出
                                // 只有在i从栈中弹出时才会计算第i类的最大面积
        stack<int> s;
        s.push(-1);
        int min_height, max_area = 0;
        for(int i=0; i<=n; i++)
        {
            while (s.top()!=-1 && heights[s.top()] >= heights[i])
            {
                min_height = heights[s.top()];
                s.pop();
                max_area = max(max_area, (i - s.top() - 1) * min_height);
            }
            s.push(i);
        }
        return max_area;
    }
};
```

# References
1. [84. 柱状图中最大的矩形/C++ - Zolewit的博客](https://blog.csdn.net/Zolewit/article/details/88863970)