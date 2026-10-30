# 题目：1339. 分裂二叉树的最大乘积（Maximum Product of Splitted Binary Tree）
# 思路：先求整棵树总和 s，再后序遍历求每棵子树和 t；在每个真子树处切断，两部分乘积为 t * (s - t)，取全局最大值后对 1e9+7 取模。
# 时间复杂度：O(n)，两次遍历每个节点一次；空间复杂度：O(h)，递归栈深度（h 为树高）。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def maxProduct(self, root: Optional[TreeNode]) -> int:  # root 为二叉树根节点，返回分裂后乘积最大值对 1e9+7 取模的结果
        def sum(root: Optional[TreeNode]) -> int:  # 内部函数：递归求以 root 为根的子树和
            if root is None:  # 空节点没有贡献
                return 0  # 空子树和为 0
            return root.val + sum(root.left) + sum(root.right)  # 子树和 = 根值 + 左子树和 + 右子树和

        def dfs(root: Optional[TreeNode]) -> int:  # 内部函数：后序遍历求子树和，并在每个真子树处尝试切断
            if root is None:  # 空节点没有贡献
                return 0  # 空子树和为 0
            t = root.val + dfs(root.left) + dfs(root.right)  # 当前子树的和（递归中顺便得到左右子树和）
            nonlocal ans, s  # 声明这里要修改外层函数的 ans 与 s，否则会被当成新的局部变量
            if t < s:  # t < s 才是真子树，t == s 相当于没切断，乘积为 0
                ans = max(ans, t * (s - t))  # 切成 t 与 s - t 两块，更新最大乘积
            return t  # 返回当前子树和给父节点用

        mod = 10**9 + 7  # 题目要求的取模数
        s = sum(root)  # 整棵二叉树的总和
        ans = 0  # 记录最大乘积
        dfs(root)  # 跑完所有子树
        return ans % mod  # 按题目要求取模后返回
