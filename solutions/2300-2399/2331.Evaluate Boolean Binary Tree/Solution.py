# 题目：2331. 计算布尔二叉树的值（Evaluate Boolean Binary Tree）
# 思路：递归求解——叶子节点直接取其值，val 为 2 的节点对左右子树做「或」，val 为 3 的节点做「与」。
# 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(h)，递归栈深度等于树高 h（最坏 O(n)）。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def evaluateTree(self, root: Optional[TreeNode]) -> bool:  # root 是布尔表达式树的根，返回整棵树的值
        if root.left is None:  # 没有左孩子说明是叶子节点，直接返回它自己的值
            return bool(root.val)  # 把叶子的 0/1 转成 False/True 返回
        op = or_ if root.val == 2 else and_  # val 为 2 选 or_，否则选 and_，把「选哪个运算符」做成一次查表
        return op(self.evaluateTree(root.left), self.evaluateTree(root.right))  # 递归求左右子树，再用选中的运算符（or_/and_）合并
