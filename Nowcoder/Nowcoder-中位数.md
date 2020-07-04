
[toc]

# Nowcoder 中位数

## 问题描述

[中位数_牛客网](https://www.nowcoder.com/practice/2364ff2463984f09904170cf6f67f69a?tpId=40&&tqId=21367&rp=1&ru=/activity/oj&qru=/ta/kaoyan/question-ranking)

## 算法

### 解法1: 使用大根堆

#### 解法1:实现

##### 解法1: c++


```
#include <iostream>
#include <queue>

using namespace std;

const int debug = 0;

int main( ) {
    int N, x;
    priority_queue<int> heap;
    while (cin >> N) {
        if (N==0) break;
        int mid = 0;
        bool isodd = N & 1;
        int size = N / 2  + 1;
        if (debug) cout << "isodd: " << isodd << " N: " << N <<  " size: " << size << endl;
        while (!heap.empty()) heap.pop();
        while (N--) {
            cin >> x;
            heap.push(x);
            if ((int)heap.size() > size) {
                heap.pop();
            }
        }
        if (isodd) {
            cout << heap.top() << endl;
        } else {
            mid += heap.top(); 
            if (debug) cout << "top: " << heap.top() << endl;
            heap.pop();
            mid += heap.top();
            if (debug) cout << "top: " << heap.top() << endl;
            cout << mid / 2 << endl;
        }
    }
    return 0;
}
```

### 解法二：使用小根堆

#### 解法二：python

```
import heapq

try:
    while True:
        n = int(input().strip())
        if n == 0: 
            break
        h = []
        heap_size = n // 2 + 1 
        for i in range(n):
            x = int(input().strip())
            if len(h) < heap_size:
                heapq.heappush(h, x)
            else:
                if x > h[0]:
                    heapq.heapreplace(h, x)
        if n & 1:
            print(h[0])
        else:
            s = h[0]
            heapq.heappop(h)
            s += h[0]
            print(s // 2)
except:
    pass
```

### 解法3: 快速选择

比较坑的一点是python要加 try except 才能 ac，不知道是为什么。

#### 解法3: python

```
def quickSelect(A, k, low, high):
    # [low, i) <= pivot
    # [i, j) > pivot
    # [j, high) unknow
    pivot = A[high-1]
    i = j = low
    while j < high:
        if A[j] <= pivot:
            A[i], A[j] = A[j], A[i]
            i += 1
        j += 1
    if i == k:
        return pivot
    elif i > k:
        return quickSelect(A, k, low, i-1)
    else:
        return quickSelect(A, k, i, high)
    
try:
    while True:
        n  = int(input().strip())
        if n == 0: break
        A = [int(input().strip()) for _ in range(n)]
        if n & 1:
            print(quickSelect(A, n // 2 + 1, 0, n))
        else:
            print((quickSelect(A, n // 2, 0, n) + quickSelect(A, n // 2 + 1, 0, n)) // 2)
except:
    pass
```