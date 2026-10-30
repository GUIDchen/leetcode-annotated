# 题目：1373. 二叉搜索子树的最大键值和（Maximum Sum BST in Binary Tree）
# 思路：后序遍历，每个子树返回「是否 BST、最小值、最大值、键值和」，用子树的这四项自底向上判断当前子树是否为 BST 并统计最大和。
# 时间复杂度：O(n)，每个结点只被访问常数次；空间复杂度：O(h)，递归栈深度为树高 h。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def maxSumBST(self, root: Optional[TreeNode]) -> int:  # root 为树根，返回所有二叉搜索子树中键值和的最大值
        def dfs(root: Optional[TreeNode]) -> tuple:  # 内层 DFS 返回四元组 (是否 BST, 子树最小值, 子树最大值, 子树键值和)
            if root is None:  # 空结点视为合法 BST
                return 1, inf, -inf, 0  # 空子树：是 BST、最小值 +inf、最大值 -inf、和为 0
            lbst, lmi, lmx, ls = dfs(root.left)  # 左子树的四元信息
            rbst, rmi, rmx, rs = dfs(root.right)  # 右子树的四元信息
            if lbst and rbst and lmx < root.val < rmi:  # 左右都是 BST，且左子树最大值 < 当前值 < 右子树最小值，当前子树才是 BST
                nonlocal ans  # 声明 ans 来自外层函数作用域
                s = ls + rs + root.val  # 当前 BST 的键值和
                ans = max(ans, s)  # 用当前键值和更新全局最大值
                return 1, min(lmi, root.val), max(rmx, root.val), s  # 返回是 BST，最小值取 min(左最小, 当前值)，最大值取 max(右最大, 当前值)，以及键值和
            return 0, 0, 0, 0  # 不是 BST 时返回 (0,0,0,0)，父结点只看第 0 项

        ans = 0  # 答案初值 0（允许没有非空 BST 的情况）
        dfs(root)  # 从根开始后序遍历
        return ans  # 返回最大键值和
