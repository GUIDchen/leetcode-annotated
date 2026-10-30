# 题目：1120. 子树的最大平均值（Maximum Average Subtree）
# 思路：后序 DFS 让每个节点返回 (子树和, 节点数)，遍历途中顺便用 sum/count 更新答案，避免每个子树重复统计。
# 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(n)，递归深度最坏为 n。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def maximumAverageSubtree(self, root: Optional[TreeNode]) -> float:  # root：二叉树根节点；返回所有子树平均值中的最大值
        def dfs(root):  # 后序递归：返回 (子树和, 节点数)
            if root is None:  # 空节点没有和也没有节点数
                return 0, 0  # 递归出口：返回零和与零个节点
            ls, ln = dfs(root.left)  # 先递归左子树，拿到左子树的和与节点数
            rs, rn = dfs(root.right)  # 再递归右子树，拿到右子树的和与节点数
            s = root.val + ls + rs  # 以 root 为根的子树元素和
            n = 1 + ln + rn  # 以 root 为根的子树节点数（含 root 自己）
            nonlocal ans  # 声明 ans 来自外层函数，闭包里才能修改它
            ans = max(ans, s / n)  # Python 3 的 / 天然是浮点除法，用当前子树平均值更新答案
            return s, n  # 把和与节点数返回给父节点复用

        ans = 0  # 记录当前最大平均值；节点值非负，0 是安全初值
        dfs(root)  # 从根节点开始遍历所有子树
        return ans  # 返回遍历中记录到的最大平均值
