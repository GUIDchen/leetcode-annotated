# 题目：1379. 找出克隆二叉树中的相同节点（Find a Corresponding Node of a Binary Tree in a Clone of That Tree）
# 思路：两棵结构相同的树同步 DFS 遍历，原树走到 target 时，克隆树上同一位置的结点就是要返回的答案。
# 时间复杂度：O(n)，最坏要访问全部结点；空间复杂度：O(h)，递归栈深度等于树高 h。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None


class Solution:  # LeetCode 约定的题解类
    def getTargetCopy(  # original 为原树根，cloned 为克隆树根，target 是原树中要找的结点
        self, original: TreeNode, cloned: TreeNode, target: TreeNode  # 参数换行书写，避免单行过长
    ) -> TreeNode:  # 返回克隆树中与 target 对应的结点
        def dfs(root1: TreeNode, root2: TreeNode) -> TreeNode:  # 内层 DFS：在两棵结构相同的树上同步下探
            if root1 is None:  # 原树走空说明该分支没有目标
                return None  # 返回空
            if root1 == target:  # 原树中遇到了目标结点
                return root2  # 克隆树上位置相同的结点即为答案
            return dfs(root1.left, root2.left) or dfs(root1.right, root2.right)  # 左子树找到就返回，否则继续在右子树找（or 会短路求值）

        return dfs(original, cloned)  # 从两棵树根开始同步遍历
