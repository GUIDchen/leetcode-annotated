# 题目：865. 具有所有最深节点的最小子树（Smallest Subtree with all the Deepest Nodes）
# 思路：后序 DFS 返回「包含子树中所有最深结点的最小子树根, 该子树高度」。左右高度不同则答案在更深一侧，相同则答案就是当前结点。
# 时间复杂度：O(n)，每个结点只访问一次；空间复杂度：O(n)，递归栈最坏为链状树的深度。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def subtreeWithAllDeepest(self, root: Optional[TreeNode]) -> Optional[TreeNode]:  # root：二叉树根；返回包含所有最深结点的最小子树的根
        def dfs(root: Optional[TreeNode]) -> Tuple[Optional[TreeNode], int]:  # 后序 DFS：返回 (包含最深结点的子树根, 该子树高度)
            if root is None:  # 空结点没有最深结点
                return None, 0  # 空子树高度记为 0
            l, ld = dfs(root.left)  # 递归左子树，得到左边的候选根与高度
            r, rd = dfs(root.right)  # 递归右子树，得到右边的候选根与高度
            if ld > rd:  # 左子树更深
                return l, ld + 1  # 最深结点全在左边，答案继承左边，高度再加一
            if ld < rd:  # 右子树更深
                return r, rd + 1  # 最深结点全在右边，答案继承右边，高度再加一
            return root, ld + 1  # 两边一样深，当前结点才是包含全部最深结点的最小根

        return dfs(root)[0]  # 取第一个元素，即最小子树的根
