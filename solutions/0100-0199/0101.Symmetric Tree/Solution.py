# 题目：101. 对称二叉树（Symmetric Tree）
# 思路：把对称性转化为两棵子树互为镜像：节点值相等，并且左的左与右的右、左的右与右的左继续互为镜像。
# 时间复杂度：O(n)，每个节点最多参与一次比较；空间复杂度：O(h)，h 为树高，即递归栈深度。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def isSymmetric(self, root: Optional[TreeNode]) -> bool:  # root：待判定的树根，返回是否左右对称
        def dfs(root1: Optional[TreeNode], root2: Optional[TreeNode]) -> bool:  # 判断以 root1、root2 为根的两棵子树是否互为镜像
            if root1 == root2:  # 引用相同（含同时为 None），说明这一对位置一致
                return True  # 视为镜像匹配
            if root1 is None or root2 is None or root1.val != root2.val:  # 一方为空或值不同
                return False  # 镜像关系不成立
            return dfs(root1.left, root2.right) and dfs(root1.right, root2.left)  # 交叉比较：外侧对外侧、内侧对内侧

        return dfs(root.left, root.right)  # 从根的两个孩子开始比较左右两棵子树
