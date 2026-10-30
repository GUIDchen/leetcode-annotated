# 题目：1457. 二叉树中的伪回文路径（Pseudo-Palindromic Paths in a Binary Tree）
# 思路：从根做一次 DFS，用整数的二进制位记录路径上各数字出现次数的奇偶；到叶子时 mask 中若至多一位为 1，该路径就能重排成回文。
# 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，h 为树高（递归栈深度），mask 只占常数空间。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def pseudoPalindromicPaths(self, root: Optional[TreeNode]) -> int:  # root：二叉树根节点；返回伪回文路径的条数
        def dfs(root: Optional[TreeNode], mask: int):  # 递归函数：root 是当前节点，mask 记录路径上各数字出现次数的奇偶
            if root is None:  # 空节点没有完整路径
                return 0  # 贡献为 0，直接返回
            mask ^= 1 << root.val  # 异或第 val 位，翻转该数字出现次数的奇偶性
            if root.left is None and root.right is None:  # 左右子节点都为空，说明是叶子，路径完整
                return int((mask & (mask - 1)) == 0)  # mask 至多一位为 1 才能重排成回文，转成 1/0 返回
            return dfs(root.left, mask) + dfs(root.right, mask)  # 累加左右子树中各自的合法路径数

        return dfs(root, 0)  # 从根节点、空 mask 开始统计总路径数
