
[toc]

# Leetcode 348. 判定井字棋胜负

## 问题描述

[348. 判定井字棋胜负 - 力扣（LeetCode）](https://leetcode-cn.com/problems/design-tic-tac-toe/)

## 算法

### 解法1: 计数法

我们考虑所有可能的胜利情况：一个 n x n 的棋盘，要胜利，只可能是
1: n 行摆满，n 种可能
2. n 列摆满， n 种可能
3. 对角线摆满，两条对角线，两种可能

一共 2n + 2 种可能。

我们将这 2 n + 2 种可能编号，每一种可能称为一个 path。
我们用一个数字来统计某个玩家在 path 上占有的格数。则那么某个玩家取胜等价于这个玩家有一个 path 上占有格数为 n。

考虑到，当某个玩家 move 一次是，只会影响至多 4 条 path，（横 + 竖 + 两条对角线），至少2 两条 path （横 + 竖）。因此可以用一个 point2path 映射，来计算每个点影响那些 path。如

#### 复杂度分析：

时间复杂度：
- __init__: $O(1)$
- move $O(1)$

空间复杂度：$O(2 * (2n + 2)) = O(n)$ 每个玩家需要保存 2n+2 条路径

#### 解法1: 实现1

##### 解法1： 实现1: python

```
class TicTacToe:

    def __init__(self, n: int):
        """
        Initialize your data structure here.
        """
        player1 = { path: 0 for path in range(2 * n + 2)}
        player2 = { path: 0 for path in range(2 * n + 2)}
        self.player = [player1, player2]
        self.n = n
        
    def move(self, row: int, col: int, playerNo: int) -> int:
        """
        Player {player} makes a move at ({row}, {col}).
        @param row The row of the board.
        @param col The column of the board.
        @param player The player, can be either 1 or 2.
        @return The current winning condition, can be either:
                0: No one wins.
                1: Player 1 wins.
                2: Player 2 wins.
        """
        player = self.player[playerNo-1]
        paths = [row, self.n + col]
        if row == col:
            paths.append(2 * self.n) # diagnal
        if row + col == self.n - 1:
            paths.append(2 * self.n + 1) # anti-diagnal
        for path in paths:
            player[path] += 1
            if player[path] == self.n: return playerNo
        return 0


# Your TicTacToe object will be instantiated and called as such:
# obj = TicTacToe(n)
# param_1 = obj.move(row,col,player)
```

### 解法2: 计数法改进

#### 解法2: 实现

##### 解法2: 实现1： python

```
class TicTacToe:

    def __init__(self, n: int):
        """
        Initialize your data structure here.
        """
        self.paths = [0] * (2 * n + 2)
        self.n = n
        
    def move(self, row: int, col: int, playerNo: int) -> int:
        """
        Player {player} makes a move at ({row}, {col}).
        @param row The row of the board.
        @param col The column of the board.
        @param player The player, can be either 1 or 2.
        @return The current winning condition, can be either:
                0: No one wins.
                1: Player 1 wins.
                2: Player 2 wins.
        """
        paths = [row, self.n + col]
        if row == col: paths.append(2 * self.n) # diagnal
        if row + col == self.n - 1: paths.append(2 * self.n + 1) # anti-diagnal
        for pathNo in paths:
            if playerNo == 1:
                self.paths[pathNo] += 1
            else:
                self.paths[pathNo] -= 1
            if abs(self.paths[pathNo]) == self.n: return playerNo
        return 0
```