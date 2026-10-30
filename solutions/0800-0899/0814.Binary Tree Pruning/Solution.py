# 题目：814. 二叉树剪枝（Binary Tree Pruning）
# 思路：后序递归，先剪干净左右子树，再判断当前结点值是否为 0 且无子结点，是则返回 None 删除。
# 时间复杂度：O(n)，每个结点访问一次；空间复杂度：O(h)，递归深度为树高。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def pruneTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:  # root 为原树根结点，返回剪枝后的根结点
        if root is None:  # 空结点不需要处理
            return root  # 原样返回 None
        root.left = self.pruneTree(root.left)  # 先递归剪左子树并接回
        root.right = self.pruneTree(root.right)  # 再递归剪右子树并接回
        if root.val == 0 and root.left == root.right:  # 值为 0 且左右子结点都为空，说明整棵子树全为 0
            return None  # 返回 None 表示删除该子树
        return root  # 否则保留当前结点
