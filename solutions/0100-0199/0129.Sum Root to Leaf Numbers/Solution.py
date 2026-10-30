# 题目：129. 求根节点到叶节点数字之和（Sum Root to Leaf Numbers）
# 思路：DFS 向下传递「已拼接的数字」s = s * 10 + root.val，到叶子时返回该数字，其余节点返回左右子树结果之和。
# 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，递归栈深度等于树高。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def sumNumbers(self, root: Optional[TreeNode]) -> int:  # root 是二叉树根节点，返回所有根到叶路径数字之和
        def dfs(root, s):  # root 是当前节点，s 是从根拼到父节点的数字
            if root is None:  # 空节点不贡献任何数字
                return 0  # 返回 0 表示没有路径数字
            s = s * 10 + root.val  # 把当前节点的值接到已拼数字的末尾
            if root.left is None and root.right is None:  # 左右子树都为空，说明是叶子节点
                return s  # 叶子处返回完整的路径数字
            return dfs(root.left, s) + dfs(root.right, s)  # 非叶子：左右子树结果之和

        return dfs(root, 0)  # 从根开始，初始数字为 0
