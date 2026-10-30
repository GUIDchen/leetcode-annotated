# 题目：113. 路径总和 II（Path Sum II）
# 思路：DFS 回溯，用 t 维护当前路径；到叶子且累计和等于 targetSum 时把 t 的副本存进答案，回溯时弹出当前结点。
# 时间复杂度：O(n^2)，最坏情况每条路径都要复制一份；空间复杂度：O(h)，h 为树高，结果列表另算。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def pathSum(self, root: Optional[TreeNode], targetSum: int) -> List[List[int]]:  # root 是树根，targetSum 是目标和，返回所有满足条件的路径
        def dfs(root, s):  # 递归函数：root 是当前结点，s 是到它为止累计的路径和
            if root is None:  # 空结点直接返回
                return  # 什么都不做（叶子判断在上一层完成）
            s += root.val  # 把当前结点值累加进路径和
            t.append(root.val)  # 当前结点值压入路径栈
            if root.left is None and root.right is None and s == targetSum:  # 叶子结点且累计和等于目标
                ans.append(t[:])  # 用 t[:] 复制一份再存，否则后续回溯会把已存的路径改掉
            dfs(root.left, s)  # 递归搜索左子树
            dfs(root.right, s)  # 递归搜索右子树
            t.pop()  # 回溯：弹出当前结点，恢复路径供兄弟分支使用

        ans = []  # 收集所有答案，每个元素是一条完整路径
        t = []  # 当前路径栈
        dfs(root, 0)  # 从根开始搜索，初始累计和为 0
        return ans  # 返回所有满足条件的路径
