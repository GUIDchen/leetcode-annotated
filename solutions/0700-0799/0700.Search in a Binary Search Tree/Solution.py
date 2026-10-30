# 题目：700. 二叉搜索树中的搜索（Search in a Binary Search Tree）
# 思路：借助二叉搜索树的有序性，目标值比当前结点小就往左走、大就往右走，相等即命中，路径长度不超过树高。
# 时间复杂度：O(h)，h 为树高，平均 O(log n)、最坏 O(n)；空间复杂度：O(h)，递归调用栈的深度。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def searchBST(self, root: Optional[TreeNode], val: int) -> Optional[TreeNode]:  # root 是二叉搜索树根，返回值为 val 的结点（不存在则返回 None）
        if root is None or root.val == val:  # 空树说明没找到；结点值等于目标说明命中
            return root  # 两种情况都直接返回当前结点（None 或目标结点）
        return (  # 用条件表达式在左右子树之间二选一
            self.searchBST(root.left, val)  # 当前值更大，目标只可能在左子树
            if root.val > val  # 判断目标值是否小于当前结点值
            else self.searchBST(root.right, val)  # 否则目标更大，只可能在右子树
        )  # 条件表达式结束，整个 return 语句到此完成
