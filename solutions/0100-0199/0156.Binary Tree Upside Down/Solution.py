# 题目：156. 上下翻转二叉树（Binary Tree Upside Down）
# 思路：递归深入最左节点作为新根，回溯时把左孩子升为父节点：原左孩子的 right 指向父、left 指向父的原右孩子，再断开父的左右指针。
# 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(h)，递归深度等于树高（最坏 O(n)）。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def upsideDownBinaryTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:  # root：原树根节点；返回翻转后新树的根（原树最左下的节点）
        if root is None or root.left is None:  # 递归出口：空树或已到最左节点，此时它就是新根，直接返回
            return root  # 返回当前节点作为新根
        new_root = self.upsideDownBinaryTree(root.left)  # 先递归翻转左子树，拿到整棵新树的根
        root.left.right = root  # 原左孩子的 right 改指向当前节点，完成「父变子」
        root.left.left = root.right  # 原左孩子的 left 改指向当前节点的原右孩子
        root.left = None  # 断开当前节点的左指针，防止成环
        root.right = None  # 断开当前节点的右指针，它已被上一层接管
        return new_root  # 返回自始至终保存的新根
