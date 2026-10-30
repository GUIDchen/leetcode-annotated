# 题目：687. 最长同值路径（Longest Univalue Path）
# 思路：后序 DFS，返回「以当前节点为端点向下延伸的同值路径长度」，再用左右两臂之和更新全局最大边数。
# 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(h)，递归深度等于树高 h。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def longestUnivaluePath(self, root: Optional[TreeNode]) -> int:  # root 为树根，返回最长同值路径经过的边数
        def dfs(root: Optional[TreeNode]) -> int:  # 内层 dfs：返回以 root 向下延伸的最长同值路径长度
            if root is None:  # 空节点：没有可延伸的路径
                return 0  # 空子树贡献长度为 0
            l, r = dfs(root.left), dfs(root.right)  # 同时递归求出左右子树能向下延伸的同值长度
            l = l + 1 if root.left and root.left.val == root.val else 0  # 只有左孩子与当前节点值相同才能接上（长度 +1），否则同值路径在此断开，记 0
            r = r + 1 if root.right and root.right.val == root.val else 0  # 右孩子同理：值相同才 +1，否则断开记 0
            nonlocal ans  # 声明 ans 来自外层函数作用域，dfs 里要就地修改它
            ans = max(ans, l + r)  # 以当前节点为拐点，左右两臂拼成一条路径，边数为 l + r，更新全局最大值
            return max(l, r)  # 向上返回时只能选一条臂（路径不能分叉），取较长者

        ans = 0  # 全局答案：最长同值路径的边数，单节点树返回 0
        dfs(root)  # 从根节点开始后序遍历
        return ans  # 返回统计到的最大边数
