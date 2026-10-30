# 题目：124. 二叉树中的最大路径和（Binary Tree Maximum Path Sum）
# 思路：后序 DFS 返回「从当前节点向下延伸的最大单边贡献」，同时用左右贡献之和更新全局答案（路径可在任意节点拐弯）。
# 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(h)，递归栈深度等于树高。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def maxPathSum(self, root: Optional[TreeNode]) -> int:  # root 是二叉树根节点，返回最大路径和
        def dfs(root: Optional[TreeNode]) -> int:  # 后序递归：返回从 root 向下走的最大单边和
            if root is None:  # 空节点
                return 0  # 空子树贡献为 0
            left = max(0, dfs(root.left))  # 左子树贡献，负数直接舍弃
            right = max(0, dfs(root.right))  # 右子树贡献，负数直接舍弃
            nonlocal ans  # 声明 ans 来自外层函数，递归中才能修改它
            ans = max(ans, root.val + left + right)  # 路径在 root 处拐弯，左 + root + 右，用它更新答案
            return root.val + max(left, right)  # 向上返回时只能沿一条边，取较大的子树

        ans = -inf  # 全局答案设为负无穷，保证任何节点值都能覆盖它（dfs 调用时才读它，所以放在这里也没问题）
        dfs(root)  # 从根节点开始 DFS
        return ans  # 返回最大路径和
