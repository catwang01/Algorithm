[toc]

# Leetcode 138. 复制带随机指针的链表

## 问题描述

[138. 复制带随机指针的链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/copy-list-with-random-pointer/)

## 算法

### 解法1

```
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (!head) return NULL;
        unordered_map<Node*, Node*> hash;
        for (Node* p=head; p!=NULL; p=p->next)
        {
            hash[p] = new Node(p->val);
        }
        for (Node* p=head; p!=NULL; p=p->next)
        {
            hash[p]->next = hash[p->next];
            hash[p]->random = hash[p->random];
        }
        return hash[head];  
    }
};
```

### 解法2: 利用next 关系来表示 hash

##### 解法2: 实现： c++

```
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (!head) return NULL;
        for (Node* p=head; p!=nullptr; p=p->next->next)
        {
            Node* node = new Node(p->val);
            node->next = p->next;
            p->next = node;
        }
        for (Node* p=head; p!=nullptr; p=p->next->next)
        {
            p->next->random = p->random==nullptr ? nullptr : p->random->next;
        }
        Node* newhead = head->next;
        for (Node* p=head, *next_p = NULL; p!=nullptr; p=p->next)
        {
            next_p = p->next->next;
            if (next_p) p->next->next = next_p->next;
            p->next = next_p;
        }
        return newhead;
    }
};
```