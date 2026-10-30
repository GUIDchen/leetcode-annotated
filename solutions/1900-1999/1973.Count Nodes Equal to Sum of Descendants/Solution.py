# 题目：1973. 值等于子节点值之和的节点数量（Count Nodes Equal to Sum of Descendants）
# 思路：后序 DFS，函数返回整棵子树的节点值之和；回传前顺便判断左右子树之和是否等于当前节点值，相等就给计数器加一。
# 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(h)，递归栈深度等于树高。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def equalToDescendants(self, root: Optional[TreeNode]) -> int:  # root：根节点；返回满足条件的节点个数
        def dfs(root):  # 返回以 root 为根的子树中所有节点值之和
            if root is None:  # 空节点没有值
                return 0  # 空子树的节点值之和约定为 0
            l, r = dfs(root.left), dfs(root.right)  # 递归求左右子树的节点值之和
            if l + r == root.val:  # 左右子树之和就是全部后代之和，恰好等于当前节点值
                nonlocal ans  # 声明这里用的是外层函数的计数器，而不是新建局部变量
                ans += 1  # 满足条件，计数加一
            return root.val + l + r  # 向上回传整棵子树的节点值之和

        ans = 0  # 计数器：值恰好等于所有后代值之和的节点个数
        dfs(root)  # 从根开始遍历，计数在遍历过程中完成
        return ans  # 返回满足条件的节点个数
