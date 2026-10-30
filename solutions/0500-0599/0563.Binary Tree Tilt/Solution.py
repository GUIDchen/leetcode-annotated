# 题目：563. 二叉树的坡度（Binary Tree Tilt）
# 思路：后序遍历求子树节点和，同时把 |左子树和 - 右子树和| 累加到外层 ans，返回子树节点和供父节点继续计算。
# 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，递归栈深度为树高。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def findTilt(self, root: Optional[TreeNode]) -> int:  # root 是二叉树根节点，返回所有节点坡度之和
        def dfs(root: Optional[TreeNode]) -> int:  # 递归返回以 root 为根的子树节点和，同时把坡度累加进外层 ans
            if root is None:  # 空节点既无节点和也无坡度
                return 0  # 空子树节点和为 0
            l, r = dfs(root.left), dfs(root.right)  # 先递归得到左右子树的节点和
            nonlocal ans  # 声明要改写外层函数的 ans，Python 必须显式 nonlocal
            ans += abs(l - r)  # 当前节点坡度 = |左子树和 - 右子树和|，累加进答案
            return l + r + root.val  # 把整棵子树的节点和返回给父节点

        ans = 0  # ans 在调用 dfs 之前定义，nonlocal 才能正确绑定到它
        dfs(root)  # 从根节点开始后序遍历
        return ans  # 返回所有节点坡度之和
