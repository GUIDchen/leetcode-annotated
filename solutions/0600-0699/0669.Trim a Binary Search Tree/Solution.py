# 题目：669. 修剪二叉搜索树（Trim a Binary Search Tree）
# 思路：BST 有序性递归：节点值 > high 时右子树全部不合法，直接返回左子树的修剪结果；< low 时反之；区间内则保留并修剪两个孩子。
# 时间复杂度：O(n)，每个节点最多访问一次；空间复杂度：O(h)，递归深度为树高 h。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def trimBST(  # 返回只保留 [low, high] 区间内节点后的 BST 根节点
        self, root: Optional[TreeNode], low: int, high: int  # root 是树根，low/high 是保留区间 [low, high] 的左右端点
    ) -> Optional[TreeNode]:  # 返回类型是可空节点（可能整棵都被剪掉）
        def dfs(root):  # 内部递归函数
            if root is None:  # 空树直接返回
                return root  # 返回 None
            if root.val > high:  # 判断是否超过上界，右子树可整棵剪掉
                return dfs(root.left)  # 超过上界：节点与右子树都不合法，改到左子树里找
            if root.val < low:  # 判断是否小于下界，左子树可整棵剪掉
                return dfs(root.right)  # 小于下界：节点与左子树都不合法，改到右子树里找
            root.left = dfs(root.left)  # 节点合法，保留并继续修剪左子树
            root.right = dfs(root.right)  # 继续修剪右子树
            return root  # 返回修剪后的当前节点

        return dfs(root)  # 从根开始修剪
