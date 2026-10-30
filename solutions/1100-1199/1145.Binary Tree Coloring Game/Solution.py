# 题目：1145. 二叉树着色游戏（Binary Tree Coloring Game）
# 思路：先找到玩家 1 选中的节点 x，分别统计 x 左子树、右子树和其余部分三个连通块的大小，玩家 2 选最大的一块，能占据超过 n/2 个节点即获胜。
# 时间复杂度：O(n)，每个节点只被访问常数次；空间复杂度：O(h)，h 为树高（最坏 O(n) 递归栈）。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def btreeGameWinningMove(self, root: Optional[TreeNode], n: int, x: int) -> bool:  # root 为整棵树；n 为节点总数；x 为玩家 1 选中的节点值
        def dfs(root):  # 深度优先搜索：找到值为 x 的节点
            if root is None or root.val == x:  # 空节点或命中目标值就停止
                return root  # 返回命中的节点（可能是 None）
            return dfs(root.left) or dfs(root.right)  # 左子树没找到再找右子树（or 返回第一个真值）

        def count(root):  # 统计以 root 为根的子树节点个数
            if root is None:  # 空树大小为 0
                return 0  # 返回 0
            return 1 + count(root.left) + count(root.right)  # 自己 1 个 加上 左子树 与 右子树的节点数

        node = dfs(root)  # 定位玩家 1 选中的节点 x
        l, r = count(node.left), count(node.right)  # 统计 x 左、右两棵子树的大小
        return max(l, r, n - l - r - 1) > n // 2  # 玩家 2 在左子树 / 右子树 / 其余部分中选最大的一块，超过一半就能赢
