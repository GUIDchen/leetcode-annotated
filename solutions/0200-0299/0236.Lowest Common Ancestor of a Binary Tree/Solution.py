# 题目：236. 二叉树的最近公共祖先（Lowest Common Ancestor of a Binary Tree）
# 思路：后序递归，返回「子树中找到的 p 或 q」；左右子树各返回一个非空时，当前结点就是最近公共祖先，否则把非空的一侧往上传递。
# 时间复杂度：O(n)，每个结点访问一次；空间复杂度：O(H)，H 为树高，即递归栈深度。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None


class Solution:  # LeetCode 约定的题解类
    def lowestCommonAncestor(  # 返回 p、q 的最近公共祖先结点
        self, root: "TreeNode", p: "TreeNode", q: "TreeNode"  # root 是树根，p、q 是待求祖先的两个结点
    ) -> "TreeNode":  # 返回值就是祖先结点本身
        if root in (None, p, q):  # 空树，或当前结点就是 p / q 时直接返回它自己（它可能就是答案）
            return root  # 返回 None，或 p / q 本身
        left = self.lowestCommonAncestor(root.left, p, q)  # 在左子树中查找，看能否找到 p 或 q
        right = self.lowestCommonAncestor(root.right, p, q)  # 在右子树中查找，看能否找到 p 或 q
        return root if left and right else (left or right)  # 左右都有结果说明 p、q 分居两侧，当前结点就是答案；否则把非空的一侧往上传递
