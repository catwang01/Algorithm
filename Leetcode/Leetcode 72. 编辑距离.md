
[toc]

# Leetcode 72. 编辑距离

## 问题描述

[72. 编辑距离 - 力扣（LeetCode）](https://leetcode-cn.com/problems/edit-distance/)

给定两个单词 *word1* 和 *word2*，计算出将 *word1* 转换成 *word2* 所使用的最少操作数 。

你可以对一个单词进行如下三种操作：

1.  插入一个字符
2.  删除一个字符
3.  替换一个字符

**示例 1:**
**输入:** word1 = "horse", word2 = "ros"
**输出:** 3
**解释:**

```
horse -> rorse (将 'h' 替换为 'r')
rorse -> rose (删除 'r')
rose  -> ros (删除 'e')
```


## 算法

### 解法1.1：递归

![07511a408d25612dd3cb56c622b54355.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p12398)@w=800

horse 转化为 ros 需要三步

1. 删除e hors vs ros
2. 删除r hos vs ros
3. 替换h为r ros vs ros

#### 解法1.1: 实现
##### 解法1.1: python超时

```
class Solution:
    def minDistance(self, word1: str, word2: str) -> int:
        if word1==word2=='':
            return 0
        if word1=='':
            return len(word2)
        if word2=='':
            return len(word1)
        if word1[-1] == word2[-1]:
            return self.minDistance(word1[:len(word1)-1], word2[:len(word2)-1])
        else:
            return min(
                # 1. delete
                self.minDistance(word1[:len(word1)-1], word2) + 1,
                # 2. insert
                self.minDistance(word1, word2[:len(word2)-1]) + 1,
                # 3. replace
                self.minDistance(word1[:len(word1)-1], word2[:len(word2)-1]) + 1
            )
```

##### 解法1.1: c++ 超时

```
class Solution {
public:
    int minDistance(string word1, string word2) {
        return dp(word1.size(), word2.size(), word1, word2);
    }
    int dp(int n, int m, const string& word1, const string& word2) {
        cout << n << m << endl;
        if (n==0) return m;
        if (m==0) return n;
        if (word1[n-1]==word2[m-1]) 
            return dp(n-1, m-1, word1, word2);
        else
            return 1 + min( 
                        min(dp(n-1, m-1, word1, word2),
                            dp(n, m-1, word1, word2)),
                        dp(n-1, m, word1, word2));
    }
};
```

### 解法1.2：记忆化

对上面的代码添加记忆化，并将用下标传参代替字符串直接传参

#### 解法1.2:实现

##### 解法1.2: python

```
class Solution:
    def minDistance(self, word1: str, word2: str) -> int:

        memo = {}
        def dp(i, j):
            if (i, j) not in memo:
                if i==0:  memo[(0,j)] = j
                elif j==0:  memo[(i,0)] = i
                else:
                    if word1[i-1] == word2[j-1]:
                        memo[(i,j)] = dp(i-1, j-1)
                    else:
                        memo[(i,j)] = min(
                            # 1. delete
                            dp(i-1, j) + 1,
                            # 2. insert
                            dp(i, j-1) + 1,
                            # 3. replace
                            dp(i-1, j-1) + 1
                        )
            return memo[(i,j)]

        return dp(len(word1), len(word2))
```

##### 解法1.2: c++

```
class Solution {
public:
    struct Hasher {
        std::size_t operator() (const pair<int, int>& x) const {
            return x.first * 10007 + x.second;
        }
    };
    unordered_map<pair<int, int>, int, Hasher> memo;
    int minDistance(string word1, string word2) {
        return dp(word1.size(), word2.size(), word1, word2);
    }
    int Min (int x, int y, int z) {
        return min(x, min(y, z));
    }
    int dp(int n, int m, const string& word1, const string& word2) {
        pair<int, int> key(n, m);
        if (memo.find(key) == memo.end()) {
            if (n==0 || m==0) {
                memo[key] = max(n, m);
            } else {
                if (word1[n-1]==word2[m-1]) {
                    memo[key] = dp(n-1, m-1, word1, word2);
                } else {
                    memo[key] =  1 + Min(dp(n-1, m-1, word1, word2),
                                        dp(n, m-1, word1, word2), 
                                        dp(n-1, m, word1, word2)
                                    );
                }
            }
        }
        return memo[key];
    }
};
```

### 解法1.3：dp

将上面的记忆化的递归

用dp数组来保存中间结果 `dp[i][j]` 表示 `word1[:i]` 和 `word2[:j]` 的编辑距离；

则转移方程为

```
if word1[i-1]==word2[i-1]:
    dp[i][j] = dp[i-1][j-1]
else:
    dp[i][j] = min(
            # 1. delete
            dp[i-1][j] + 1,
            # 2. insert
            dp[i][j-1] + 1,
            # 3. replace
            dp[i-1][j-1] + 1
            )
```

#### 解法1.3: 实现

##### 解法1.3: python

```
class Solution:
    def minDistance(self, word1: str, word2: str) -> int:
        n, m = len(word1), len(word2)
        if n==0: return m
        if m==0: return n
        dp = [[0]*(m+1) for _ in range(n+1)]
        for i in range(n+1):
            dp[i][0] = i
        for j in range(m+1):
            dp[0][j] = j

        for i in range(1, n+1):
            for j in range(1, m+1):
                if word1[i-1]==word2[j-1]:
                    dp[i][j] = dp[i-1][j-1]
                else:
                    dp[i][j] = 1 + min(
                        # 1. delete
                        dp[i-1][j],
                        # 2. insert
                        dp[i][j-1],
                        # 3. replace
                        dp[i-1][j-1]
                    ) 
        return dp[n][m]
```

##### 解法1.3: c++

```
class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size(), m = word2.size();
        vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
        for (int i=0; i<=n; i++) dp[i][0] = i;
        for (int j=0; j<=m; j++) dp[0][j] = j;
        for (int i=1; i<=n; i++) {
            for (int j=1; j<=m; j++) {
                if (word1[i-1]==word2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    dp[i][j] =  1 + Min(dp[i-1][j-1],
                                        dp[i][j-1],
                                        dp[i-1][j]);
                }
            }
        }
        return dp[n][m];
    }

    int Min (int x, int y, int z) {
        return min(x, min(y, z));
    }
};
```

### 解法1.4：空间优化

利用滚动数组进行优化，需要两个临时变量

![f79a161de9e7f3c51224cd215be92e86.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p12399)@w=400

#### 解法1.4:实现

##### 解法1.4: python

```
class Solution:
    def minDistance(self, word1: str, word2: str) -> int:
        n, m = len(word1), len(word2)
        if n==m==0:
            return 0
        if n==0: return m
        if m==0: return n
        dp = [0]*(m+1)

        # i == 0
        for j in range(m+1):
            dp[j] = j

        for i in range(1, n+1):
            for j in range(m+1):
                if j==0:
                    tmp1 = dp[0]
                    dp[0] = i
                else:
                    if word1[i-1]==word2[j-1]:
                        tmp2 = dp[j]
                        dp[j] = tmp1
                        tmp1 = tmp2
                    else:
                        tmp2 = dp[j]
                        dp[j] = 1 + min(dp[j], dp[j-1], tmp1)
                        tmp1 = tmp2 
        return dp[m]
```

利用 python 的特性，代码可以化简为只使用一个临时变量

```
class Solution:
    def minDistance(self, word1: str, word2: str) -> int:
        n, m = len(word1), len(word2)
        if n==m==0:
            return 0
        if n==0: return m
        if m==0: return n
        dp = [0]*(m+1)

        # i == 0
        for j in range(m+1):
            dp[j] = j
 
        for i in range(1, n+1):
            for j in range(m+1):
                if j==0:
                    dp[0], tmp = i, dp[0]
                else:
                    if word1[i-1]==word2[j-1]:
                        dp[j], tmp = tmp, dp[j]
                    else:
                        dp[j], tmp = 1 + min(dp[j], dp[j-1], tmp), dp[j]
        return dp[m]
```

##### 解法1.4: c++

```
class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size(), m = word2.size();
        vector<int> dp(m+1, 0);
        int tmp1, tmp2;
        for (int i=0; i<=n; i++) {
            for (int j=0; j<=m; j++) {
                tmp2 = dp[j];
                if (i==0) { 
                    dp[j] = j; 
                } else {
                    if (j==0) {
                        dp[j] = i; 
                    } else {
                        if (word1[i-1]==word2[j-1]) {
                            dp[j] = tmp1;
                        } else {
                            dp[j] =  1 + Min(tmp1, dp[j-1], dp[j]);
                        }
                    }
                }
                tmp1 = tmp2;
            }
        }
        return dp[m];
    }
    
    int Min (int x, int y, int z) {
        return min(x, min(y, z));
    }
};
```

# References

1. [编辑距离面试题详解 - 编辑距离 - 力扣（LeetCode）](https://leetcode-cn.com/problems/edit-distance/solution/bian-ji-ju-chi-mian-shi-ti-xiang-jie-by-labuladong/)
