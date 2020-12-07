[TOC]

# LEETCODE 1024. 视频拼接

## 问题描述

[1024. 视频拼接 - 力扣（LEETCODE）](HTTPS://LEETCODE-CN.COM/PROBLEMS/VIDEO-STITCHING/)

## 算法

### 解法1: DP

`DP[I]` 表示 `[0, I)` 区间被覆盖的最少片段数

则得到递推式

```
FOR J IN RANGE(0, LEN(CLIPS)):
    IF CLIPS[J][0] <= I <= CLIPS[J][1]:
        DP[I] = MIN(DP[I], DP[CLIPS[J][0]] + 1) 
```

时间复杂度： $O(NT)$， N 是片段数
空间复杂度： $O(T)$


##### 解法1：实现：PYTHON

```
CLASS SOLUTION:
    DEF VIDEOSTITCHING(SELF, CLIPS: LIST[LIST[INT]], T: INT) -> INT:
        DP = [FLOAT('INF')] * (T + 1)
        DP[0] = 0
        FOR I IN RANGE(1, T+1):
            FOR CLIP IN CLIPS:
                IF CLIP[0] <= I <= CLIP[1]:
                    DP[I] = MIN(DP[I], DP[CLIP[0]] + 1)
        RETURN DP[T] IF DP[T] != FLOAT('INF') ELSE -1
```

### 解法2：贪心

```
1. START = 0, RET = 空集
2. 找到 IDX = ARGMAX(CLIPS[J][1] | CLIPS[J][0] <= START)
    IF 能找到这样的 IDX:
        CLIPS[IDX] 添加到 RET 中，更新 START = CLIPS[IDX][1]
    ELSE:
        无法完成任务，返回 0
3. 
    IF START >= T: 
        返回 LEN(RET)
    ELSE:
        回到 2
```

我们固定 START = 0，我们每次都去满足 `CLIPS[J][1] <= START` 的区间中找那个 `CLIPS[J][1]` 最大的，然后添加到结果中。并且更新 START = `CLIPS[J][1]`
#### 贪心法证明

我们仿照算法导论中对于活动问题的证明。为了清晰起见，我们用 .START 表示区间的起点，即 CLIPS[J][0]，用 .END 表示区间的终点即 CLIPS[J][1]

1. 令 $S_J = \{CLIP \IN CLIPS | CLIP.END >= J \}$ 表示满足的终点大于 J 的所有区间的集合。假设 $S_J$ 上的最优解为 $A_J = \{A_1, ..., A_K\}$（其中 $A_1, \DOTS, A_K$ 是根据 .START 排序好序的。再令 $M$ 表示 $S_J$ 中终点最大的区间

2. 如果 $M = A_1$，那么说明 M 一定在最优解中
3. 如果 $M \NEQ A_1$，根据 M 的定义，一定有 $M.END >= A_1.END$，那么 $A'_J = A_J - \{A_1\} + {M_1}$ 必然也是解。由于  $| A_J' | = | A_J |$，说明 $A_J'$ 也是最优解。

这说明，$S_J$ 中终点最大的区间，必然在最优解中。


#### 解法2: 实现1： BRUTEFORCE 版

时间复杂度： $O(N^2)$
空间复杂度：$O(1)$

##### 解法2: 实现1: PYTHON

```
CLASS SOLUTION:
    DEF VIDEOSTITCHING(SELF, CLIPS: LIST[LIST[INT]], T: INT) -> INT:
        START = 0
        RET = 0
        WHILE START < T:
            END = -FLOAT("INF")
            FOR CLIP IN CLIPS: # 这个时间复杂度为 O(N)
                IF CLIP[0] <= START AND CLIP[1] >= END:
                    END = CLIP[1]
            IF END == START:
                RETURN -1
            ELSE:
                RET += 1
                START = END
        RETURN RET
```

#### 解法2: 实现： 滑动窗口


因为在上一个实现中每次都需要对于 CLIP[0] <= START 的那些区间求最大终点。我们可以将 CLIPS 按照起点升序的方式排序，这样我们就不需要考虑那些 CLIP[0] > START 的区间了。

##### 解法2: 实现：PYTHON

```
CLASS SOLUTION:
    DEF VIDEOSTITCHING(SELF, CLIPS: LIST[LIST[INT]], T: INT) -> INT:
        CLIPS.SORT(KEY=LAMBDA CLIP: (CLIP[0], -CLIP[1]))
        IF T == 0:
            RETURN 0
        START = END = 0 
        RET = 0 
        I = 0  
        WHILE I < LEN(CLIPS):
            J = I 
            END = START
            # 求满足 CLIPS[J][0] <= START 的最大终点
            WHILE J < LEN(CLIPS) AND CLIPS[J][0] <= START:
                IF CLIPS[J][1] > END:
                    END = CLIPS[J][1]
                J += 1
            IF START == END:
                RETURN -1
            RET += 1
            IF END >= T:
                RETURN RET
            START = END
            I = J
        RETURN -1
```
