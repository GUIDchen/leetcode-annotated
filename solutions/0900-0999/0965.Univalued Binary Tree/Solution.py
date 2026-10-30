# 题目：965. 单值二叉树（Univalued Binary Tree）
# 思路：先取出根节点的值存进 x，再深度优先遍历，判断每个节点的值是否都等于 x。
# 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(h)，递归栈深度等于树的高度。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def isUnivalTree(self, root: Optional[TreeNode]) -> bool:  # root 是二叉树根节点，返回整棵树的节点值是否全部相同
        def dfs(root: Optional[TreeNode]) -> bool:  # 内部 DFS：判断以 root 为根的子树中所有节点值是否都等于 x
            if root is None:  # 空节点不算反例，直接返回 True
                return True  # 空节点判断结束，返回 True
            return root.val == x and dfs(root.left) and dfs(root.right)  # 当前节点值等于 x，且左右子树都满足，才是单值树

        x = root.val  # 记录根节点的值作为全树的基准值（dfs 通过闭包读取它）
        return dfs(root)  # 从根节点开始 DFS 判断
