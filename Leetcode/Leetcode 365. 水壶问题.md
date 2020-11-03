[toc]

# Leetcode 365. 水壶问题

## 问题描述

[365. 水壶问题 - 力扣（LeetCode）](https://leetcode-cn.com/problems/water-and-jug-problem/)

## 算法

### 解法1.1：dfs——递归

#### 解法1.1：实现

##### 解法1.1 :python 超出最大递归层数

```
class Solution:
    def canMeasureWater(self, x: int, y: int, z: int) -> bool:
        passed = set()
        flag = False
        
        def dfs(v1, v2):
            nonlocal flag
            if flag == True or (v1, v2) in passed:
                return
            if v1 == z or v2 == z or v1 + v2 == z:
                flag = True
                return
            passed.add((v1, v2))
            # 倒掉x
            if v1 > 0 and (0, v2) not in passed:
                dfs(0, v2)
            # 倒掉y
            if v2 > 0 and (v1, 0) not in passed:
                dfs(v1, 0)
            # 装满x
            if v1 < x and (x, v2) not in passed:
                dfs(x, v2)
            # 装满y
            if v2 < y and (v1, y) not in passed:
                dfs(v1, y)
            # 用将y中的倒入x
            if v1 < x and v2 > 0:
                need = x - v1
                if v2 > need:
                    dfs(x, v2 - need)
                else:
                    dfs(v1 + v2, 0)
            # 将x中的倒入y
            if v1 > 0 and v2 < y:
                need = y - v1
                if v1 > need:
                    dfs(v1-need, y)
                else:
                    dfs(0, v2 + v1)
        dfs(0, 0)
        return flag
```

#### 解法1:实现2:

##### 解法1: 实现2: python

```
class Solution:
    def canMeasureWater(self, x: int, y: int, z: int) -> bool:
        
        seen = set()
        def help(i, j): # 假设A壶 i 升水，B壶j升水
            if (i, j) in seen: return False
            seen.add((i, j))
            
            if i == z or j == z or i + j == z:
                return True
            
            return help(x, j) or help(0, j) \ # A 壶倒空或倒满
                    or help(i, 0) or help(i, y) \ # B 壶倒空或倒满
                    or help(max(x - (y-j), 0), min(j+i, y)) \   # A 壶倒入B壶中
                    or help(min(i+j, x), max(y - (x-i), 0)) # B 壶倒入 A

            # A 倒入 B
            # if x > y - j: # A中的水比B需要的水多
            #     ret = ret or help(x - (y - j), y) # A把B装满还有剩
            # else:
            #     ret = ret or help(0, j + i) # A全倒入B
            # 化简为 help(max(x - (y-j), 0), min(j+i, y)) \   # A 壶倒入B壶中

            # B 倒入 A
            # if y > x - i:
            #     ret = ret or help(x, y - (x - i))
            # else:
            #     ret = ret or help(i + j, 0)
            # 化简为  help(min(i+j, x), max(y - (x-i), 0)) \  # A 壶倒入B壶中

        return help(0, 0)
```

### 解法1.2：dfs——栈

由于直接递归回超出递归层数限制，因此可以用栈代替。

#### 解法1.2:实现

##### 解法1.2: python

```
class Solution:
    def canMeasureWater(self, x: int, y: int, z: int) -> bool:
        passed, stack = set(), [(0, 0)]
        while stack:
            v1, v2 = stack.pop()
            if (v1, v2) in passed:
                continue
            if v1 == z or v2 == z or v1 + v2 == z:
                return True
            passed.add((v1, v2))
            if v1 > 0 and (0, v2) not in passed:
                stack.append((0, v2))
            if v2 > 0 and (v1, 0) not in passed:
                stack.append((v1, 0))
            if v1 < x and (x, v2) not in passed:
                stack.append((x, v2))
            if v2 < y and (v1, y) not in passed:
                stack.append((v1, y))
            if v1 < x and v2 > 0:
                need = x - v1
                if v2 > need:
                    stack.append((x, v2 - need))
                else:
                    stack.append((v1 + v2, 0))
            if v1 > 0 and v2 < y:
                need = y - v2
                if v1 > need:
                    stack.append((v1-need, y))
                else:
                    stack.append((0, v2 + v1))
        return False
```

##### 解法1.2: java

```
import java.util.Arrays;
import java.util.Stack;

class Solution {
    public boolean canMeasureWater(int x, int y, int z) {
        Set<List<Integer>> passed = new HashSet<List<Integer>>();
        Stack<List<Integer>> stack = new Stack<List<Integer>>();
        stack.add(Arrays.asList(0, 0));
        List<Integer> list;

        while (!stack.empty()) {
            List<Integer> pots = stack.pop();
            Integer v1 = pots.get(0), v2 = pots.get(1);
            if (passed.contains(pots)) continue;
            if (v1==z || v2==z || v1 + v2 == z)  return true;
            passed.add(pots);

            if (v1 > 0) {
                list = Arrays.asList(0 ,v2);
                if (!passed.contains(list))
                    stack.push(list);
            }

            if (v2 > 0) {
                list = Arrays.asList(v1, 0);
                if (!passed.contains(list))
                    stack.push(list);
            }

            if (v1 < x) {
                list = Arrays.asList(x, v2);
                if (!passed.contains(list))
                    stack.push(list);
            }  

            if (v2 < y) {
                list = Arrays.asList(v1, y);
                if (!passed.contains(list)) 
                    stack.push(list);
            }

            if (v1 < x && v2 > 0) {
                Integer need = x - v1;
                if (v2 > need) {
                    list = Arrays.asList(x, v2 - need);
                    if (!passed.contains(list)) 
                        stack.push(list);
                } else {
                    list = Arrays.asList(v1 + v2, 0);
                    if (!passed.contains(list))
                        stack.push(list);
                }
            }

            if (v2 < y && v1 > 0) {
                Integer need = y - v2;
                if (v1 > need) {
                    list = Arrays.asList(v1 - need, y);
                    if (!passed.contains(list))
                        stack.push(list);
                } else {
                    list = Arrays.asList(0, v2 + v2);
                    if (!passed.contains(list))
                        stack.push(list);
                }
            }
        }
        return false;
    }
};
```
