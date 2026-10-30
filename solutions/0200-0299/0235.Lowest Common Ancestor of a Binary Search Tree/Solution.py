# 题目：235. 二叉搜索树的最近公共祖先（Lowest Common Ancestor of a Binary Search Tree）
# 思路：利用 BST 的大小关系从根往下走；当前值比两个目标都小就去右子树，都比它大就去左子树，介于两者之间时当前结点就是分叉点。
# 时间复杂度：O(H)，H 为树高（最坏 O(n)）；空间复杂度：O(1)，只用了几个指针。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None


class Solution:  # LeetCode 约定的题解类
    def lowestCommonAncestor(  # 返回 p、q 的最近公共祖先结点
        self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode'  # root 是 BST 根结点，p、q 是待求祖先的两个结点
    ) -> 'TreeNode':  # 返回值就是祖先结点本身
        while 1:  # 一直向下走，直到找到分叉点
            if root.val < min(p.val, q.val):  # 当前值比两个目标都小，说明祖先在右子树（右子树的值更大）
                root = root.right  # 向右子树走
            elif root.val > max(p.val, q.val):  # 当前值比两个目标都大，说明祖先在左子树
                root = root.left  # 向左子树走
            else:  # 当前值介于两者之间（或等于其中之一），它就是分叉点
                return root  # 当前结点即最近公共祖先
