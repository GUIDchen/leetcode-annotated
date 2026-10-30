# 题目：543. 二叉树的直径（Diameter of Binary Tree）
# 思路：树形 DP。递归求每个节点的左右子树高度，路径经过该节点时的长度为 l+r，用 nonlocal 变量 ans 记录全局最大值，向上返回 1+max(l,r)。
# 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，递归栈深度等于树高 h。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def diameterOfBinaryTree(self, root: Optional[TreeNode]) -> int:  # 入口：返回二叉树的直径（任意两节点间最长路径的边数）
        def dfs(root: Optional[TreeNode]) -> int:  # 内层递归函数：返回以 root 为根的子树高度，并顺带更新最大直径
            if root is None:  # 空节点高度为 0，作为递归边界
                return 0  # 空树贡献的高度是 0
            l, r = dfs(root.left), dfs(root.right)  # 分别求出左、右子树的高度
            nonlocal ans  # 声明 ans 来自外层函数，这里要修改的是同一个变量
            ans = max(ans, l + r)  # 经过当前节点的路径长度就是左右子树高度之和，取较大值更新答案
            return 1 + max(l, r)  # 向上返回子树高度：较高的一棵子树再加 1（算上自己）

        ans = 0  # 全局答案初始为 0
        dfs(root)  # 从根节点开始一次后序遍历即可算出答案
        return ans  # 返回最长路径长度
