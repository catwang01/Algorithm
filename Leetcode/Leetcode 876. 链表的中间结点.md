[toc]

# Leetcode 876. 链表的中间结点

## 问题描述

[876. 链表的中间结点 - 力扣（LeetCode）](https://leetcode-cn.com/problems/middle-of-the-linked-list/)

## 算法

### 解法1.1:

遍历一遍链表，将结果保存到数组中，最后返回数组中间索引的元素 list[n//2]

#### 解法1.1:实现

##### 解法1.1:java

```
class Solution {
    public ListNode middleNode(ListNode head) {
        ListNode p = head;
        List<ListNode> list = new ArrayList<ListNode>();
        while(p != null) {
            list.add(p);
            p = p.next;
        }
        return list.size()==0? p : list.get(list.size() >>> 1);
    }
}
```

### 解法1.2

不使用数组保存元素，而是先遍历一遍得到所有元素的个数n。之后在遍历一遍，在n//2处返回

#### 解法1.2:实现

##### 解法1.2:java

```
class Solution {
    public ListNode middleNode(ListNode head) {
        ListNode p = head;
        int n = 0;
        while(p != null) {
            n += 1;
            p = p.next;
        }
        p = head;
        for (int i=0; i<n/2; i++) p = p.next;
        return p;
    }
}
```

##### 解法1.2:c++

```
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        int len = getLen(head);
        for (int i=0; i<len /2 ; i++) {
            head = head->next;
        }
        return head;
    }
    int getLen(ListNode* head) {
        int ret = 0;
        while (head) {
            head = head->next;
            ret ++;
        }
        return ret;
    }
};
```

### 解法2: 快慢指针

快指针比慢指针多走两步。

注意一些很细节的边界条件！比如while循环不仅要检查 fast 结点是否为空；还要检查 fast->next 结点是否为空。

#### 解法2:

##### 解法2: c++

```
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode* slow = head,  *fast = head;
        // 这样写不需要特判, head为空结点和只有一个结点的情况可以排除
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
};
```

##### 解法2:python

```
class Solution:
    def middleNode(self, head: ListNode) -> ListNode:
        slow, fast = head, head

        while fast is not None:
            fast = fast.next
            if fast is not None:
                fast = fast.next
                slow = slow.next
        return slow
```

