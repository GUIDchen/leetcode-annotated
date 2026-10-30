# 题目：337. 打家劫舍 III（House Robber III）
# 核心思路：树形 DP，后序遍历每个节点，同时返回「选当前节点」与「不选当前节点」两种状态的最大收益，父子不能同时被选。
# 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(n)，递归栈深度最坏为 n。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def rob(self, root: Optional[TreeNode]) -> int:  # root 为二叉树根节点，返回能偷到的最大金额
        def dfs(root: Optional[TreeNode]) -> (int, int):  # 后序 DFS：返回 (选当前节点, 不选当前节点) 两种状态下的最大收益
            if root is None:  # 空树没有收益
                return 0, 0  # 两种状态都返回 0
            la, lb = dfs(root.left)  # 左子树的两种状态：la 选左孩子，lb 不选左孩子
            ra, rb = dfs(root.right)  # 右子树的两种状态：ra 选右孩子，rb 不选右孩子
            return root.val + lb + rb, max(la, lb) + max(ra, rb)  # 选当前节点则孩子都不能选；不选当前节点则孩子各自取较优值

        return max(dfs(root))  # 根节点的两种状态取最大值即为答案
