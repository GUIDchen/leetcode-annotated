# 题目：1490. 克隆 N 叉树（Clone N-ary Tree）
# 核心思路：递归深拷贝，先递归克隆全部子节点，再用原值与新子节点列表构造当前节点的副本。
# 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(n)，新树与递归栈。
"""
# Definition for a Node.
class Node:
    def __init__(self, val=None, children=None):
        self.val = val
        self.children = children if children is not None else []
"""


class Solution:  # LeetCode 约定的题解类
    def cloneTree(self, root: 'Node') -> 'Node':  # 返回 root 的深拷贝，原树与新树不共享节点
        if root is None:  # 空节点
            return None  # 直接返回 None
        children = [self.cloneTree(child) for child in root.children]  # 递归克隆每个子节点，得到新的子节点列表
        return Node(root.val, children)  # 用原值与新子节点列表构造当前节点的副本
