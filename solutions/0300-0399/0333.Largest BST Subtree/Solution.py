# 题目：333. 最大二叉搜索子树（Largest BST Subtree）
# 思路：后序 DFS，返回 (子树最小值, 子树最大值, 节点数)；若左子树最大值 < 根 < 右子树最小值，则整棵子树是 BST，用它的节点数更新答案。
# 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(h)，递归栈深度（h 为树高）。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
# 上面是 LeetCode 题面给出的二叉树节点定义，判题器已提供，此处仅作说明
class Solution:    # LeetCode 约定的题解类
    def largestBSTSubtree(self, root: Optional[TreeNode]) -> int:    # root：二叉树根节点，返回其中最大的二叉搜索子树（BST）的节点数
        def dfs(root):    # 后序 DFS，返回三元组 (子树最小值, 子树最大值, 子树节点数)
            if root is None:    # 空节点直接返回哨兵三元组，节点数为 0，不会虚增答案
                return inf, -inf, 0    # 最小值取 +inf、最大值取 -inf，任何父节点与它比较都能通过
            lmi, lmx, ln = dfs(root.left)    # 递归左子树，拿到左子树的 (最小值, 最大值, 节点数)
            rmi, rmx, rn = dfs(root.right)    # 递归右子树，拿到右子树的 (最小值, 最大值, 节点数)
            nonlocal ans    # 声明要修改外层函数里的 ans（非局部变量）
            if lmx < root.val < rmi:    # 左子树最大值 < 根值 < 右子树最小值，说明以 root 为根的整棵子树是 BST
                ans = max(ans, ln + rn + 1)    # 用它整棵的节点数更新全局最大 BST 大小
                return min(lmi, root.val), max(rmx, root.val), ln + rn + 1    # 返回合并后的最小/最大值与节点总数，供父节点判断
            return -inf, inf, 0    # 不是 BST：返回 -inf/inf 哨兵，保证父节点判定必然失败，节点数记 0

        ans = 0    # 全局答案：最大 BST 子树的节点数
        dfs(root)    # 从根开始后序遍历
        return ans    # 返回答案
