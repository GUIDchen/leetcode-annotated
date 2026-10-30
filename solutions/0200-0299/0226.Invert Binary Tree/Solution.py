# 题目：226. 翻转二叉树（Invert Binary Tree）
# 思路：递归先翻转左右子树，再把根节点的左右孩子互换，等于对整棵树做一次后序遍历。
# 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，递归栈深度为树高，最坏 O(n)。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def invertTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:  # root 是子树根节点；返回翻转后的同一棵树的根
        if root is None:  # 空节点没有孩子可换，是递归的终止条件
            return None  # 空输入返回 None，父节点对应孩子位置保持为空
        l, r = self.invertTree(root.left), self.invertTree(root.right)  # 分别递归翻转左右子树，得到两颗已完成翻转的新子树
        root.left, root.right = r, l  # 同时赋值交换：原右子树接到左边，原左子树接到右边
        return root  # 把翻转好的根节点返回给上一层
