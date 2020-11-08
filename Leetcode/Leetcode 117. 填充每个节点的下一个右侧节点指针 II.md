[toc]


# Leetcode 117. 填充每个节点的下一个右侧节点指针 II

## 算法

### 解法1: 层次遍历

### 解法2: preorder 遍历

考虑使用 dfs 来解决问题。我们在链接 next 节点时，假设当前节点为 node，其父节点为 parent。

1. 如果 node 是 parnet 的左节点并且 parent 右节点不为空，那么 node.next = parent.right

2. 如果 node 是 parent 的左节点并且 parent 右节点为空，那么 node 需要链接到同一层级的下一个节点上去。这个节点该如何得到呢？我们可以利用 parent 节点。假设我们处理 node 节点时 parent 节点已经链接完毕了，那么 parent 节点实际上构成了一个链表。node 节点的下一个节点必然是 parent 节点形成的链表的节点的子节点。

这样，我们就可以写出链接下一个节点的代码。注意，如果 parent_next 没有左右节点，那么就需要检查链表的下一个元素。

```
parent_next = parent.next
while parent_next and not parent_next.left and not parent_next.right:
    parent_next = parent_next.next
if parent_next:
    node.next = parent_next.left if parent_next.left else parent_next.right
```

3. 如果 node 是 parent 节点的右节点，情况处理同 2。

整个过程需要先处理父节点，在处理子节点，因此采用前序遍历。

**但是，这里还有一个坑**，就是前序遍历在访问节点时需要先访问**右子节点**，再访问**左子节点**。

因为我们处理左节点是需要右节点已经将右侧链表链接完成。

```
class Solution:
    def connect(self, root: 'Node') -> 'Node':

        def preorder(parent, node): # 需要用到父节点的信息，因此将父节点也传入
            if not node: return
            if parent:
                if node == parent.left and parent.right:
                    node.next = parent.right
                else:
                    # 遍历链表
                    parent_next = parent.next
                    while parent_next and not parent_next.left and not parent_next.right:
                        parent_next = parent_next.next
                    if parent_next:
                        node.next = parent_next.left if parent_next.left else parent_next.right
            preorder(node, node.right)
            preorder(node, node.left)
        
        preorder(None, root)
        return root
```