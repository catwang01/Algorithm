[toc]

# Nowcoder 两个链表的第一个公共结点

## 问题描述

[两个链表的第一个公共结点_牛客网](https://www.nowcoder.com/practice/6ab1d9a29e88450685099d45c9e31e46?tpId=13&tqId=11189&tPage=2&rp=2&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking)

## 算法

### 解法1

#### 解法1:实现

##### 解法1:c++

```
class Solution {
public:
    ListNode* FindFirstCommonNode( ListNode* p1, ListNode* p2) {
        ListNode* cur1 = p1, *cur2 = p2;
        while (cur1!=cur2) { // 注意 null==null 返回1。因此即使公共结点为空，也不会报错
            cur1 = cur1==NULL ? p2: cur1->next;
            cur2 = cur2==NULL ? p1: cur2->next;
        }
        return cur1;
    }
};
```

### 解法2: 计算长度

#### 解法2:实现

##### 解法2:c++

```
class Solution {
public:
    ListNode* FindFirstCommonNode( ListNode* p1, ListNode* p2) {
        int len1 = getLen(p1), len2 = getLen(p2);
        if (len1 < len2) {
            int n = len2 - len1;
            while (n--) p2 = p2->next;
        } else {
            int n = len1 - len2;
            while (n--) p1 = p1->next;
        }
        while (p1!=NULL) {
            if (p1==p2) return p1;
            p1 = p1->next;
            p2 = p2->next;
        }
        return NULL;
    }
    int getLen(ListNode* node) {
        int ret = 0;
        while (node !=NULL) {
            node = node->next;
            ret++;
        }
        return ret;
    }
};
```

##### 解法1: python

```
class Solution:
    def FindFirstCommonNode(self, pHead1, pHead2):
        if pHead1 is None or pHead2 is None:
            return None
        len1, len2 = self.getLen(pHead1), self.getLen(pHead2)
        if len1  <= len2:
            for i in range(len2-len1):
                pHead2 = pHead2.next
            while pHead2 is not None:
                if pHead1 == pHead2:
                    return pHead1
                pHead1 = pHead1.next
                pHead2 = pHead2.next
            return None
        else:
            return self.FindFirstCommonNode(pHead2, pHead1)

    def getLen(self, head):
        ret = 0
        while head is not None:
            head = head.next
            ret += 1
        return ret
```
