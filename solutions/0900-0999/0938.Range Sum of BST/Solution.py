# 题目：938. 二叉搜索树的范围和（Range Sum of BST）
# 思路：借助二叉搜索树的有序性递归剪枝：当前值大于下界才往左走，小于上界才往右走。
# 时间复杂度：O(n)，最坏情况遍历所有节点；空间复杂度：O(h)，h 为树高，即递归调用栈深度。
# 下面这段注释是 LeetCode 题面给出的二叉树节点定义，判题器已内置，此处仅作说明。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def rangeSumBST(self, root: Optional[TreeNode], low: int, high: int) -> int:  # root 是 BST 根节点，low/high 是闭区间上下界，返回区间内节点值之和
        def dfs(root: Optional[TreeNode]) -> int:  # 内层递归函数：求以 root 为根的子树中落在区间内的节点值之和
            if root is None:  # 空节点说明递归到底了
                return 0  # 空子树对和的贡献为 0
            x = root.val  # 当前节点的值
            ans = x if low <= x <= high else 0  # 当前值在区间内才累加自身，否则记 0
            if x > low:  # x 大于下界，左子树里才可能有 >= low 的值
                ans += dfs(root.left)  # 累加左子树的区间和
            if x < high:  # x 小于上界，右子树里才可能有 <= high 的值
                ans += dfs(root.right)  # 累加右子树的区间和
            return ans  # 返回本子树的区间和

        return dfs(root)  # 从根开始 DFS，得到整棵 BST 的区间和
