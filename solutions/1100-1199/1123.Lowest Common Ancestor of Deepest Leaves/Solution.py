# 题目：1123. 最深叶节点的最近公共祖先（Lowest Common Ancestor of Deepest Leaves）
# 思路：后序 DFS 每层返回 (该子树最深叶子的公共祖先, 子树高度)；左右高度相等说明最深叶子在此分叉，当前节点就是答案。
# 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(n)，递归深度最坏为 n。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def lcaDeepestLeaves(self, root: Optional[TreeNode]) -> Optional[TreeNode]:  # 返回所有最深叶子节点的最近公共祖先
        def dfs(root):  # 后序递归：返回 (该子树最深叶子的公共祖先, 该子树高度)
            if root is None:  # 空节点
                return None, 0  # 递归出口：没有祖先，高度记为 0
            l, d1 = dfs(root.left)  # 先求左子树：l 是答案，d1 是左子树高度
            r, d2 = dfs(root.right)  # 再求右子树：r 是答案，d2 是右子树高度
            if d1 > d2:  # 左子树更高，最深叶子全在左边
                return l, d1 + 1  # 左子树的答案原样上移一层，高度加 1
            if d1 < d2:  # 右子树更高，最深叶子全在右边
                return r, d2 + 1  # 右子树的答案原样上移一层，高度加 1
            return root, d1 + 1  # 左右等高：最深叶子分布两侧，当前 root 就是公共祖先

        return dfs(root)[0]  # 只取祖先，丢弃高度信息
