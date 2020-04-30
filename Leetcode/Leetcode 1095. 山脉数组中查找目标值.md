[toc]

# Leetcode 1095. 山脉数组中查找目标值

## 问题描述

[1095. 山脉数组中查找目标值 - 力扣（LeetCode）](https://leetcode-cn.com/problems/find-in-mountain-array/)

## 算法

### 解法1: 二分法

#### 解法1:实现

##### 解法1: c++

```
int checkAsc(int midVal, int target) {
    if (midVal==target) {
        return 0;
    } else {
        return midVal > target? 1: -1;
    }
}

int checkDesc(int midVal, int target) {
    if (midVal==target) {
        return 0;
    } else {
        return midVal > target ? -1: 1;
    }
}

class Solution {
public:
    int findInMountainArray(int target, MountainArray &mountainArr) {
        int len = mountainArr.length();
        int peak = findPeak(0, len-1, mountainArr);
        int ret = bisearch(0, peak, target, mountainArr, checkAsc);
        return ret==-1 ? 
                bisearch(peak, len-1, target, mountainArr, checkDesc):
                ret;
    }

    // 用于找到峰值
    int findPeak(int low, int high, MountainArray &mountainArr) {
        while (low < high) {
            int mid = low + (high - low) /2 ;
            if (mountainArr.get(mid) > mountainArr.get(mid+1)) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        return low;
    }
    // 接受一个 check 函数以简化代码
    int bisearch(int low, int high, int target, MountainArray& mountainArr, int (*check)(int, int)) {
        int mid, midVal, flag;
        while (low <= high) {
            mid = low + (high - low) / 2;
            midVal = mountainArr.get(mid);
            flag = check(midVal, target);
            switch(flag) {
                case 0:
                    return mid;
                case 1:
                    high = mid - 1;
                    break;
                case -1:
                    low = mid + 1;
                    break;
            }
        }
        return -1;
    }
};
```

