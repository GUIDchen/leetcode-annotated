# 题目：2236. 判断根结点是否等于子结点之和（Root Equals Sum of Children）
# 思路：题目保证只有三个结点，直接比较根结点值与左右孩子值之和。
# 时间复杂度：O(1)；空间复杂度：O(1)。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def checkTree(self, root: Optional[TreeNode]) -> bool:  # root 为根结点，返回根值是否等于左右孩子值之和
        return root.val == root.left.val + root.right.val  # 比较根结点值与两个子结点值之和
