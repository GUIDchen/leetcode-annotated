# 题目：117. 填充每个节点的下一个右侧节点指针 II（Populating Next Right Pointers in Each Node II）
# 思路：层序遍历（BFS），p 记住本层上一个节点，新节点到来时令 p.next 指向它；按层推进所以不要求完全二叉树，孩子缺失也不影响。
# 时间复杂度：O(n)，每个节点只入队出队一次；空间复杂度：O(n)，队列最坏保存一整层节点。
"""
# Definition for a Node.
class Node:
    def __init__(self, val: int = 0, left: 'Node' = None, right: 'Node' = None, next: 'Node' = None):
        self.val = val
        self.left = left
        self.right = right
        self.next = next
"""


class Solution:  # LeetCode 约定的题解类
    def connect(self, root: "Node") -> "Node":  # 入参和返回值都是根节点，指针在树上原地修改
        if root is None:  # 空树直接返回
            return root  # 返回 None
        q = deque([root])  # 双端队列做 BFS，初始只有根节点
        while q:  # 队列非空即还有层待处理
            p = None  # p 记录本层上一个处理过的节点
            for _ in range(len(q)):  # 先取当前层节点个数，保证这次 for 只处理一层
                node = q.popleft()  # 从队头取出一个节点
                if p:  # 不是本层第一个节点时，把上一个节点接到它上面
                    p.next = node  # 赋值 next 指针
                p = node  # 更新本层末尾节点
                if node.left:  # 左孩子存在则入队（可能只有左孩子，这是 II 相对 I 的难点）
                    q.append(node.left)  # 左孩子入队
                if node.right:  # 右孩子存在则入队
                    q.append(node.right)  # 右孩子入队
        return root  # 返回根节点，next 指针已在原地填好
