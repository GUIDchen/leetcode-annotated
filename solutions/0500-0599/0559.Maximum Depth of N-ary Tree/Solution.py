# 题目：559. N 叉树的最大深度（Maximum Depth of N-ary Tree）
# 核心思路：递归求每个孩子子树的最大深度，取最大值再加一表示当前层。
# 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，递归栈深度为树高。
"""
# Definition for a Node.
class Node:
    def __init__(self, val: Optional[int] = None, children: Optional[List['Node']] = None):
        self.val = val
        self.children = children
"""


class Solution:  # LeetCode 约定的题解类
    def maxDepth(self, root: "Node") -> int:  # root 为 N 叉树根，返回树的最大深度
        if root is None:  # 空树深度为 0，作为递归出口
            return 0  # 直接返回 0
        mx = 0  # 记录孩子子树中的最大深度
        for child in root.children:  # 逐个孩子递归计算深度
            mx = max(mx, self.maxDepth(child))  # 取较大者，得到最深的子树
        return 1 + mx  # 子树最大深度加一即包含当前层的总深度
