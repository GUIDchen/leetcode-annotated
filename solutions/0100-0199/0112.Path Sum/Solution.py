# 题目：112. 路径总和（Path Sum）
# 思路：DFS 自根向下累加路径和，遇到叶子时判断是否等于 targetSum，任一条满足即返回 True。
# 时间复杂度：O(n)，最坏访问每个结点一次；空间复杂度：O(h)，h 为树高，也就是递归栈深度。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def hasPathSum(self, root: Optional[TreeNode], targetSum: int) -> bool:  # root 是树根，targetSum 是目标和，返回是否存在根到叶子的路径和等于它
        def dfs(root, s):  # 递归函数：root 是当前结点，s 是到达它之前已经累计的路径和
            if root is None:  # 空结点不可能构成路径
                return False  # 返回 False
            s += root.val  # 把当前结点值累加进路径和（s 是局部变量，不影响兄弟分支）
            if root.left is None and root.right is None and s == targetSum:  # 当前是叶子结点，且累计和正好等于目标
                return True  # 找到一条满足条件的路径
            return dfs(root.left, s) or dfs(root.right, s)  # 否则在左右子树中继续找，任一侧成功即可

        return dfs(root, 0)  # 从根开始搜索，初始累计和为 0
