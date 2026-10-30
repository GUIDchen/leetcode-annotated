# 题目：2313. 二叉树中得到结果所需的最少翻转次数（Minimum Flips in Binary Tree to Get Result）
# 思路：树上 DP。dfs 返回 (该子树得到 0 的最少翻转次数, 得到 1 的最少翻转次数)；叶子直接是 (x, x^1)，内部节点按 OR/AND/XOR/NOT 的真值表组合左右子树代价并取最小。
# 时间复杂度：O(n)，每个节点只算一次；空间复杂度：O(h)，递归栈深度（h 为树高）。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def minimumFlips(self, root: Optional[TreeNode], result: bool) -> int:  # root：表达式二叉树；result：希望整棵树最终得到的结果
        def dfs(root: Optional[TreeNode]) -> (int, int):  # 返回 (子树得到 0 的最少翻转次数, 得到 1 的最少翻转次数)
            if root is None:  # 空节点不会真正出现，用 inf 表示「不可达」
                return inf, inf  # 返回两个无穷大，保证之后取 min 时不会被选中
            x = root.val  # 节点值：0/1 为叶子，2=OR，3=AND，4=XOR，5=NOT
            if x in (0, 1):  # 叶子节点：值已经固定
                return x, x ^ 1  # 得到 x 不需翻转，得到 x^1 需要翻转 1 次
            l, r = dfs(root.left), dfs(root.right)  # 先递归求出左右子树各自得到 0 / 1 的最小代价
            if x == 2:  # 或运算：只要有一边为 1，结果就是 1
                return l[0] + r[0], min(l[0] + r[1], l[1] + r[0], l[1] + r[1])  # 得 0 需两边都为 0；得 1 取「至少一边为 1」的三种组合最小
            if x == 3:  # 与运算：只有两边都为 1，结果才是 1
                return min(l[0] + r[0], l[0] + r[1], l[1] + r[0]), l[1] + r[1]  # 得 0 取「至少一边为 0」的三种组合最小；得 1 需两边都为 1
            if x == 4:  # 异或运算：两边不同得 1，相同得 0
                return min(l[0] + r[0], l[1] + r[1]), min(l[0] + r[1], l[1] + r[0])  # 得 0：同为 0 或同为 1；得 1：一 0 一 1
            return min(l[1], r[1]), min(l[0], r[0])  # 非运算：得 0 需孩子为 1，得 1 需孩子为 0

        return dfs(root)[int(result)]  # int(result) 把 False/True 映射成下标 0/1，取出对应的最少翻转次数
