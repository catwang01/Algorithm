[toc]

# Leetcode 22. 括号生成

## 问题描述

[22. 括号生成 - 力扣（LeetCode）](https://leetcode-cn.com/problems/generate-parentheses/)

## 算法

### 解法一：dfs

![037abb654485535379c960e49d2a33f1.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p12555)@w=700

1. 停止条件：当 path 中的字符数为 2n 时停止，即

```
if len(path)==2*n:
    result.append(path)
    return 
```

2. 答案更新

```
for k, v in candidates.items():
    if v > 0:
        candidates[k] -= 1
        dfs(path+k)
        candidates[k] += 1
```

3. 剪枝

剪枝的规则是：如果剩余的右括号的个数小于剩余的左括号的个数，那么不可能组成有效括号。

用一个check函数来判断是否可以产生一个有效的解。对于每一个 `(` 赋值为 -1， 对于每一个 `)` 赋值为 1，对于path中的每个字符，依次累加其对应的值。如果这个值大于0，说明此时的右括号有多余的无法匹配，因此返回为 False；如果这个值总是小于等于0，返回为 True

```
valMap = {'(':-1, ')':1}
def check(path):
    val = 0
    for s in path:
        val += valMap[s]
        if val > 0: return False
    return True
```

#### 解法1：实现

##### 解法1: python

```
class Solution:
    def generateParenthesis(self, n: int) -> List[str]:
        candidates = {'(':n, ')':n}
        valMap = {'(':-1, ')':1}
        
        def check(path):
            val = 0
            for s in path:
                val += valMap[s]
                if val > 0: return False
            return True

        result = []
        def dfs(path):
            if check(path):
                if len(path)==2*n:
                    result.append(path)
                    return 
                for k, v in candidates.items():
                    if v > 0:
                        candidates[k] -= 1
                        dfs(path+k)
                        candidates[k] += 1
        dfs("")
        return result
```

##### 解法1：python

```
class Solution:
    def generateParenthesis(self, n: int) -> List[str]:
        if n == 0: return []
        path = []
        self.dfs(n, n, "", path)
        return path

    # left 表示剩余的左括号的个数
    # right 表示剩余的右括号的个数
    def dfs(self, left, right, current, path):
        if (left == 0):
            path.append(current + ")" * right)
            return

        if left == right:
            self.dfs(left-1, right, current + "(", path)

        if left < right:
            self.dfs(left, right - 1, current + ")", path)
            self.dfs(left-1, right, current + "(", path)
```

##### 解法1: c++

```
class Solution {
public:
    vector<string> ret;
    vector<string> generateParenthesis(int n) {
        dfs(n, n, "");
        return ret;
    }
    void dfs(int left, int right, string s) {
        if (left==0 && right==0) {
            ret.push_back(s);
        }
        if (left > right) return;
        if (left > 0) {
            dfs(left-1, right, s + "(");
        }
        if (right > 0) {
            dfs(left, right-1, s + ")");
        }
    }
};
```


### 解法2: bfs

下面的 bfs 是参考 [1] 写出的。这个代码的意思是说清楚 bfs 和 dfs 的区别，以及为什么在实现dfs时需要使用递归。

在用递归实现 dfs 传的参数实际上就是节点的属性，dfs 使用了系统的栈，因此不需要自己定义栈。而节点的属性被当作参数传入，因此就不需要显式定义结点。

将这个bfs代码中的队列换成栈，就得到了不使用递归实现的 dfs

#### 解法2: 实现

##### 解法2: c++

```
class Node {
    public:
        int left, right;
        string s;
        Node (int left_=0, int right_=0, string s_="") : left(left_), right(right_), s(s_) {}
};

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        queue<Node> q;
        vector<string> ret;
        q.push(Node(n, n, ""));
        Node node;
        while (!q.empty()) {
            node = q.front(); q.pop();
            // 停止条件
            if (node.left == 0 && node.right==0) {
                ret.push_back(node.s);
                continue;
            }
            // 剪枝
            if (node.left < 0 || node.right <0 || node.left > node.right) {
                continue;
            }
            q.push(Node(node.left-1, node.right, node.s + "("));
            q.push(Node(node.left, node.right-1, node.s + ")"));
        }
        return ret;
    }
};
```

# References
1. [回溯算法（深度优先遍历）+ 广度优先遍历 + 动态规划 - 括号生成 - 力扣（LeetCode）](https://leetcode-cn.com/problems/generate-parentheses/solution/hui-su-suan-fa-by-liweiwei1419/)