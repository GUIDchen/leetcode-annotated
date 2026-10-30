# 题目：1485. 克隆含随机指针的二叉树（Clone Binary Tree With Random Pointer）
# 核心思路：用字典记录「原节点 → 副本」，先登记再递归，保证 random 指针成环时也能正确复制。
# 时间复杂度：O(n)，每个节点只克隆一次；空间复杂度：O(n)，字典与递归栈。
# Definition for Node.
# class Node:
#     def __init__(self, val=0, left=None, right=None, random=None):
#         self.val = val
#         self.left = left
#         self.right = right
#         self.random = random


class Solution:  # LeetCode 约定的题解类
    def copyRandomBinaryTree(self, root: "Optional[Node]") -> "Optional[NodeCopy]":  # root 为原树根，返回深拷贝后新树的根
        def dfs(root: Optional[Node]) -> Optional[NodeCopy]:  # 递归克隆：返回与 root 对应的新节点
            if root is None:  # 空节点直接返回空
                return None  # 保持空结构
            if root in seen:  # 该节点已克隆过（random 指针可能成环，必须判重）
                return seen[root]  # 复用已有副本，保证同一节点只有一份拷贝
            copy = NodeCopy(root.val)  # 先创建副本，稍后登记，环上的引用才能拿到地址
            seen[root] = copy  # 记录「原节点 → 副本」映射
            copy.left = dfs(root.left)  # 递归克隆左子树
            copy.right = dfs(root.right)  # 递归克隆右子树
            copy.random = dfs(root.random)  # 递归克隆 random 指向的节点
            return copy  # 返回当前副本

        seen = {}  # 哈希表：原节点 → 克隆节点（在内层函数之后创建，闭包中可见）
        return dfs(root)  # 从根开始克隆
