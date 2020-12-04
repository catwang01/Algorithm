[toc]

# Leetcode 138. 复制带随机指针的链表

## 问题描述

[138. 复制带随机指针的链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/copy-list-with-random-pointer/)

## 算法

### 解法1：hashtab

#### 解法1: 实现

##### 解法1: 实现：c++

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

##### 解法1: 实现：python

```
class Solution:
    def copyRandomList(self, head: 'Node') -> 'Node':
        hashtab = {None: None} # old2new
        node = head
        while node:
            hashtab[node] = Node(node.val)
            node = node.next
        node = head
        while node:
            hashtab[node].next = hashtab[node.next]
            hashtab[node].random = hashtab[node.random]
            node = node.next
        return hashtab[head]
```


### 解法2: 利用next 关系来表示 hash

#### 解法2: 实现
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

##### 解法2: 实现： python

```
class Solution:
    def copyRandomList(self, head: 'Node') -> 'Node':
        node = head
        while node:
            nextNode = node.next
            newNode = Node(node.val)
            node.next = newNode
            newNode.next = nextNode
            node = nextNode
        
        node = head
        while node:
            if node.random: 
                node.next.random = node.random.next
            node = node.next.next
        
        virtualhead = Node(-1)
        cur = virtualhead
        node = head
        while node:
            cur.next = node.next
            node.next = node.next.next
            node = node.next
            cur = cur.next
        
        return virtualhead.next

```