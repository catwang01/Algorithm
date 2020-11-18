[toc]

# Leetcode 1013. 将数组分成和相等的三个部分

## 问题描述

[1013. 将数组分成和相等的三个部分 - 力扣（LeetCode）](https://leetcode-cn.com/problems/partition-array-into-three-parts-with-equal-sum/submissions/)

## 算法

### 解法一：bruteforce

时间复杂度： $O(n^3)$
空间复杂度： $O(1)$

#### 解法一：实现

##### 解法一：c++

```
class Solution {
public:
    bool canThreePartsEqualSum(vector<int>& A) {
        int n = A.size();
        if (n <= 2) return false;
        for (int i=1; i<n-1; i++ ) {
            for (int j=i+1; j<n; j++) {
                int x=sum(0,i,A);
                int y=sum(i,j,A);
                int z=sum(j,n,A);
                if (x==y && y==z) {
                        cout << "x: " << x << " y: " << y << " z:" << z << endl;
                        return true;
                }
            }
        }
        return false;
    }
    int sum(int i, int j, vector<int> & A) {
        int s = 0;
        for (int k=i; k<j; k++) s += A[k];
        return s;
    }
};
```


### 解法二：前缀数组 + 优化

时间复杂度： $O(n^2)$
空间复杂度： $O(n)$

#### 解法二：实现

##### 解法二：c++ 超时

![cc5f22443fd0241e994b4c23cfeda095.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p11093)
 
```
 class Solution {
public:
    bool canThreePartsEqualSum(vector<int>& A) {
        int n = A.size();
        if (n <= 2) return false;
        int preSum[n+1] = {0};
        for (int i=1; i<n+1; i++) {
            preSum[i] = preSum[i-1] + A[i-1];
        }
        // for (int num: preSum) cout << num << endl;
        for (int i=1; i<n-1; i++ ) {
            for (int j=i+1; j<n; j++) {
                int x=sum(0,i,preSum);
                int y=sum(i,j,preSum);
                int z=sum(j,n,preSum);
                if (x==y && y==z) {
                        cout << "x: " << x << " y: " << y << " z:" << z << endl;
                        return true;
                }
            }
        }
        return false;
    }
    int sum(int i, int j, int* preSum) {
        return preSum[j] - preSum[i];
    }
};
```

### 解法三

时间复杂度： $O(n)$
空间复杂度： $O(n)$

#### 解法三：实现

##### 解法三：c++ AC

```
class Solution {
public:
    bool canThreePartsEqualSum(vector<int>& A) {
        int n = A.size();
        if (n <= 2) return false;
        int preSum[n+1] = {0};
        for (int i=1; i<n+1; i++) {
            preSum[i] = preSum[i-1] + A[i-1];
        }
        if (preSum[n] % 3 == 0) {
            int target = preSum[n] / 3;
            for (int i=1; i<n-1; i++) {
                if (preSum[i]==target) {
                    for (int j=i+1; j<n; j++) {
                        if (preSum[j]== 2 * target) {
                            return true;
                        }
                    }
                }
            }
        } 
        return false;
    }
};
```
   
### 解法四：双指针

#### 解法四：实现

##### 解法四：实现：python

```
class Solution:
    def canThreePartsEqualSum(self, A: List[int]) -> bool:
        n = len(A)
        if n < 3: return False

        s = sum(A)
        if s % 3 != 0: return False
        
        s //= 3
        
        # [0, i) s_left
        s_left = A[0] # 注意，这里没有从 s_left=0 i=0 开始
                    # 而是从 s_left=A[0], i=1 开始，一方面是为了避免 s=0 时会发生的错误
                    # 另一方面，由于三个区间均为空，因此至少会有一个元素，这样做也不会有任何问题
        i = 1
        while i < n and s_left != s:
            s_left += A[i]
            i += 1
        if i == n:
            return False
        
        # (j, n-1] s_right
        s_right = A[n-1]
        j = n-2
        # [i, j]
        while j - i + 1 >= 1 and s_right != s:
            # [i,j] 这个区间的元素个数为 j-i+1 由于这个区间不能为空，因此需要有 j-i+1 >= 1
            s_right += A[j]
            j -= 1
        if j - i + 1 < 1: 
            return False
        return True
```