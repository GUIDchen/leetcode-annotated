# 题目：617. 合并二叉树（Merge Two Binary Trees）
# 思路：两棵树同步递归合并；任一侧为空就直接返回另一侧，否则把两节点值相加后递归合并左右子树。
# 时间复杂度：O(min(m, n))，只处理两棵树重叠的节点；空间复杂度：O(min(m, n))，递归栈深度不超过较矮的树。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def mergeTrees(  # 合并两棵二叉树的入口方法
        self, root1: Optional[TreeNode], root2: Optional[TreeNode]  # root1、root2 是两棵待合并树的根节点
    ) -> Optional[TreeNode]:  # 返回合并后新树的根节点
        if root1 is None:  # root1 为空：另一棵子树整体搬过来即可
            return root2  # 直接复用 root2，无需再合并
        if root2 is None:  # root2 为空：同理直接复用 root1 的子树
            return root1  # 直接返回 root1
        node = TreeNode(root1.val + root2.val)  # 两棵树都不空：新建节点存放两值之和，不改动原树
        node.left = self.mergeTrees(root1.left, root2.left)  # 左孩子由两棵树的左子树递归合并得到
        node.right = self.mergeTrees(root1.right, root2.right)  # 右孩子由两棵树的右子树递归合并得到
        return node  # 返回合并后的子树根，供上层挂接
