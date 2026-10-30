# 题目：298. 二叉树最长连续序列（Binary Tree Longest Consecutive Sequence）🔒
# 思路：后序 DFS，返回以当前结点为起点的向下连续递增长度；孩子值不等于父值 +1 时该侧链断开、重置为 1。
# 时间复杂度：O(n)，每个结点访问一次；空间复杂度：O(h)，递归栈深度为树高。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def longestConsecutive(self, root: Optional[TreeNode]) -> int:  # root：树根；返回整棵树中最长的连续递增路径长度
        def dfs(root: Optional[TreeNode]) -> int:  # 递归函数：返回以 root 为起点的向下连续长度
            if root is None:  # 空结点
                return 0  # 空路径长度为 0
            l = dfs(root.left) + 1  # 左子树递归结果再接上自己，所以 +1
            r = dfs(root.right) + 1  # 右子树递归结果再接上自己，所以 +1
            if root.left and root.left.val - root.val != 1:  # 左孩子存在但值不是父值 +1，说明左链断开
                l = 1  # 只能从自己重新开始计数
            if root.right and root.right.val - root.val != 1:  # 右孩子存在但值不是父值 +1，说明右链断开
                r = 1  # 同样从自己重新开始计数
            t = max(l, r)  # 当前结点往下左右两条路中较长的那条
            nonlocal ans  # 声明要修改外层函数的 ans，避免被当成新的局部变量
            ans = max(ans, t)  # 用它更新全局最大值
            return t  # 把以当前结点为起点的长度返回给上一层

        ans = 0  # 全局答案初始为 0
        dfs(root)  # 从根开始遍历，答案记录在闭包变量 ans 里
        return ans  # 返回最长连续序列长度
