# 题目：1372. 二叉树中的最长交错路径（Longest ZigZag Path in a Binary Tree）
# 思路：DFS 同时携带「上一步向左」和「上一步向右」两种当前长度，向左走时用右长度加一，向右走时用左长度加一，边走边更新答案。
# 时间复杂度：O(n)，每个结点访问一次；空间复杂度：O(h)，递归栈深度等于树高 h。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def longestZigZag(self, root: TreeNode) -> int:  # root 为树根，返回最长交错路径经过的边数
        def dfs(root, l, r):  # 内层 DFS：l 是上一步向左走的当前长度，r 是上一步向右走的当前长度
            if root is None:  # 空结点没有可延伸的路径，直接回溯
                return  # 结束当前分支
            nonlocal ans  # 声明 ans 来自外层函数作用域，内层函数要修改它
            ans = max(ans, l, r)  # 用两个方向的当前长度更新全局答案
            dfs(root.left, r + 1, 0)  # 向左走：只有上一步向右才连续，长度取 r+1，右方向累计清零
            dfs(root.right, 0, l + 1)  # 向右走：只有上一步向左才连续，长度取 l+1，左方向累计清零

        ans = 0  # 答案初始为 0（空树或只有根结点时都是 0）
        dfs(root, 0, 0)  # 从根节点开始，两个方向长度都为 0
        return ans  # 返回 DFS 过程中记录到的最长交错路径
