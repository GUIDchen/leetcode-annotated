# 题目：100. 相同的树（Same Tree）
# 思路：两棵树同时递归，先比较节点值，再依次比较左子树与左子树、右子树与右子树。
# 时间复杂度：O(min(m, n))，遇到不同即剪枝；空间复杂度：O(min(h1, h2))，取决于递归栈较浅的一方。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def isSameTree(self, p: Optional[TreeNode], q: Optional[TreeNode]) -> bool:  # p、q 是两棵树根，返回是否相同
        if p == q:  # 同一个对象（包含同时为 None）说明完全一致
            return True  # 结构与值都相同
        if p is None or q is None or p.val != q.val:  # 只有一方为空，或两节点值不等
            return False  # 一旦出现差异立即判定不同
        return self.isSameTree(p.left, q.left) and self.isSameTree(p.right, q.right)  # 左右子树都要分别相同
