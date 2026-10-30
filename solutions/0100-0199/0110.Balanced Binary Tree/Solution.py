# 题目：110. 平衡二叉树（Balanced Binary Tree）
# 思路：后序递归求高度，一旦某结点左右高度差超过 1 就返回 -1 作为「已不平衡」标记向上传递，避免重复求高度。
# 时间复杂度：O(n)，每个结点只访问一次；空间复杂度：O(h)，h 为树高，也就是递归栈深度。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def isBalanced(self, root: Optional[TreeNode]) -> bool:  # root 是树根，返回整棵树是否平衡
        def height(root):  # 递归函数：返回子树高度，-1 表示这棵子树已经不平衡
            if root is None:  # 空结点高度记为 0
                return 0  # 空树高度为 0
            l, r = height(root.left), height(root.right)  # 分别求左右子树高度（可能是 -1 这个不平衡标记）
            if l == -1 or r == -1 or abs(l - r) > 1:  # 任一子树不平衡，或高度差超过 1，就判为不平衡
                return -1  # 返回 -1 把不平衡状态往上传递
            return 1 + max(l, r)  # 平衡时高度为左右较大者加一

        return height(root) >= 0  # 高度非负说明整棵树平衡
