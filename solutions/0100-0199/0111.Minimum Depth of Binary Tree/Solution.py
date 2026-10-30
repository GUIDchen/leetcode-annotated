# 题目：111. 二叉树的最小深度（Minimum Depth of Binary Tree）
# 思路：递归。空结点为 0；只有单个孩子时必须沿该孩子走（最小深度必须以叶子结尾）；两侧都有才取较小值加一。
# 时间复杂度：O(n)，最坏访问每个结点一次；空间复杂度：O(h)，h 为树高，也就是递归栈深度。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def minDepth(self, root: Optional[TreeNode]) -> int:  # root 是树根，返回根到最近叶子的结点数
        if root is None:  # 空结点没有深度
            return 0  # 空子树深度为 0
        if root.left is None:  # 没有左孩子，只能沿右子树继续找叶子
            return 1 + self.minDepth(root.right)  # 深度等于右子树最小深度加一（用 self. 递归调用本方法）
        if root.right is None:  # 没有右孩子，只能沿左子树继续找叶子
            return 1 + self.minDepth(root.left)  # 深度等于左子树最小深度加一
        return 1 + min(self.minDepth(root.left), self.minDepth(root.right))  # 左右孩子都在：取两侧较小值，再加当前这一层
