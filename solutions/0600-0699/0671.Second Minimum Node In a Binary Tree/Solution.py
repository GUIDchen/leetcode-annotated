# 题目：671. 二叉树中第二小的节点（Second Minimum Node In a Binary Tree）
# 思路：根节点即全树最小值，DFS 收集所有严格大于根值的节点值，其中最小的那个就是第二小；不存在则返回 -1。
# 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，递归栈深度为树高（最坏 O(n)）。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def findSecondMinimumValue(self, root: Optional[TreeNode]) -> int:  # root：二叉树根节点
        def dfs(root):  # 内层递归函数，负责遍历子树
            if root:  # 只有非空节点才继续，兼作递归出口
                dfs(root.left)  # 递归处理左子树
                dfs(root.right)  # 递归处理右子树
                nonlocal ans, v  # 声明下面读写的是外层变量，而不是新建局部变量
                if root.val > v:  # 只关心严格大于基准最小值的节点
                    ans = root.val if ans == -1 else min(ans, root.val)  # 首次命中直接记录，之后取更小者

        ans, v = -1, root.val  # ans 记录第二小值（-1 表示未找到），v 是根值即全树最小值
        dfs(root)  # 从根开始遍历整棵树
        return ans  # 返回第二小的值，找不到时是 -1
