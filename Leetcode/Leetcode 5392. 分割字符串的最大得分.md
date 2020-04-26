[toc]

# Leetcode 5392. 分割字符串的最大得分

## 问题描述

[5392. 分割字符串的最大得分 - 力扣（LeetCode）](https://leetcode-cn.com/problems/maximum-score-after-splitting-a-string/)

## 算法

### 解法1: 从右边逐个加入到左边

时间复杂度: $O(n)$ 
空间复杂度：$O(1)$ 

#### 解法1:实现

##### 解法1: c++

```
from collections import Counter
class Solution:
    def maxScore(self, s: str) -> int:
        # 初始将第一个放在左边，其它都放在右边
        score = (s[0]=='0') + Counter(s[1:]).get('1', 0)
        ret = score
        # 再逐个从右边加入到左边
        for i in range(1, len(s)-1):
            if s[i]=='0': # 如果是'0' 在右边的时候不会计算分数，加入到左边之后会计算分数。因此分数加1
                score += 1
                ret = max(ret, score)
            else:   # 反之分数 -1
                score -= 1
        return ret
```

