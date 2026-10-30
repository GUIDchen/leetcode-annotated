# 题目：1430. 判断给定的序列是否是二叉树从根到叶的路径（Check If a String Is a Valid Sequence from Root to Leaves Path in a Binary Tree）
# 思路：从根开始按 arr 逐层匹配，值不等立即剪枝；匹配完最后一个元素时必须正好是叶子节点。
# 时间复杂度：O(n)，最坏访问每个节点一次；空间复杂度：O(h)，递归栈深度为树高。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def isValidSequence(self, root: TreeNode, arr: List[int]) -> bool:  # 判断是否存在一条根到叶路径，其节点值序列恰好等于 arr
        def dfs(root, u):  # 内部递归：root 为当前节点，u 为 arr 中待匹配的下标
            if root is None or root.val != arr[u]:  # 节点为空或值不同，这条路径失败
                return False  # 返回失败，交给上层的 or 继续尝试
            if u == len(arr) - 1:  # 已经匹配到 arr 的最后一个值
                return root.left is None and root.right is None  # 必须同时是叶子节点，才算一条完整的根到叶路径
            return dfs(root.left, u + 1) or dfs(root.right, u + 1)  # 否则递归尝试左右子节点匹配下一个值，任一成立即可

        return dfs(root, 0)  # 从根节点与 arr 下标 0 开始匹配
