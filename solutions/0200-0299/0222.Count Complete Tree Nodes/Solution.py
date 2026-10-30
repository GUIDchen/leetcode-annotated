# 题目：222. 完全二叉树的节点个数（Count Complete Tree Nodes）
# 思路：后序递归统计。空节点返回 0，其余节点返回 1 + 左子树节点数 + 右子树节点数。
# 时间复杂度：O(n)，每个节点恰好访问一次；空间复杂度：O(h)，递归栈深度为树高，最坏 O(n)。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def countNodes(self, root: Optional[TreeNode]) -> int:  # root 是子树根节点；返回该子树的节点总数
        if root is None:  # 空节点代表越过叶子，递归到此结束
            return 0  # 空子树贡献 0 个节点
        return 1 + self.countNodes(root.left) + self.countNodes(root.right)  # 根节点 1 个 + 左右子树节点数之和
