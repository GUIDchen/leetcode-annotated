# 题目：549. 二叉树最长连续序列 II（Binary Tree Longest Consecutive Sequence II）🔒
# 思路：后序遍历，dfs 返回「以当前节点结尾的最长递增连续长度」和「最长递减连续长度」；以当前节点为拐点的路径 = 递增段 + 递减段 - 1，用闭包变量 ans 记录全局最大值。
# 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(h)，递归深度等于树高。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def longestConsecutive(self, root: TreeNode) -> int:  # 返回树中最长的连续路径（相邻节点值相差 1）长度
        def dfs(root):  # 返回 [以 root 结尾的最长递增连续长度, 以 root 结尾的最长递减连续长度]
            if root is None:  # 空节点
                return [0, 0]  # 两种长度都为 0，作为递归出口
            nonlocal ans  # 声明要修改外层函数里的 ans
            incr = decr = 1  # 只考虑 root 自己时，递增/递减长度都是 1
            i1, d1 = dfs(root.left)  # 递归左子树，拿到它的两种长度
            i2, d2 = dfs(root.right)  # 递归右子树，拿到它的两种长度
            if root.left:  # 左孩子存在才可能接续
                if root.left.val + 1 == root.val:  # 左孩子比根小 1，递增链能接上
                    incr = i1 + 1  # 递增长度加一
                if root.left.val - 1 == root.val:  # 左孩子比根大 1，递减链能接上
                    decr = d1 + 1  # 递减长度加一
            if root.right:  # 右孩子同理
                if root.right.val + 1 == root.val:  # 右孩子比根小 1
                    incr = max(incr, i2 + 1)  # 取左右两条递增链中更长的一条
                if root.right.val - 1 == root.val:  # 右孩子比根大 1
                    decr = max(decr, d2 + 1)  # 取左右两条递减链中更长的一条
            ans = max(ans, incr + decr - 1)  # 以 root 为拐点的路径 = 递增段 + 递减段 - 1（root 被重复计算一次）
            return [incr, decr]  # 把两种长度返回给父节点使用

        ans = 0  # 全局最优长度
        dfs(root)  # 后序遍历求答案
        return ans  # 返回结果
