# 题目：285. 二叉搜索树中的中序后继（Inorder Successor in BST）🔒
# 思路：借助 BST 的有序性一次下行：root.val > p.val 时 root 可能是答案，记录后去左子树找更近的候选；否则答案在右子树。
# 时间复杂度：O(h)，h 是树高；空间复杂度：O(1)，只用了常数个指针。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None


class Solution:  # LeetCode 约定的题解类
    def inorderSuccessor(self, root: TreeNode, p: TreeNode) -> Optional[TreeNode]:  # root 是 BST 根节点，p 是目标节点，返回其中序后继
        ans = None  # ans 记录目前最接近的候选后继
        while root:  # 沿树向下搜索，直到空节点
            if root.val > p.val:  # 当前节点值大于 p，它可能是后继
                ans = root  # 先记录为当前最佳候选
                root = root.left  # 再进左子树寻找更小的候选
            else:  # 当前节点不大于 p，后继只能在右子树
                root = root.right  # 转向右子树继续找
        return ans  # 返回最后记录的候选，即中序后继
