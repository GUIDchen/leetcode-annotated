# 题目：104. 二叉树的最大深度（Maximum Depth of Binary Tree）
# 思路：递归：一棵树的最大深度等于左右子树最大深度的较大值再加 1；空节点深度为 0。
# 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，h 为树高，递归栈的开销。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def maxDepth(self, root: TreeNode) -> int:  # root：树根，返回整棵树的最大深度
        if root is None:  # 空树
            return 0  # 深度为 0，作为递归的终止条件
        l, r = self.maxDepth(root.left), self.maxDepth(root.right)  # 同时递归求出左右子树的最大深度
        return 1 + max(l, r)  # 算上当前层，加上左右两边较深的那一支
