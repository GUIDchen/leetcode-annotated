# 题目：108. 将有序数组转换为二叉搜索树（Convert Sorted Array to Binary Search Tree）
# 思路：每次取区间中点作为根结点，左右两半区间递归建左右子树，得到的树高度差不超过 1，必然平衡。
# 时间复杂度：O(n)，每个元素建一个结点；空间复杂度：O(log n)，递归栈深度等于树高。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def sortedArrayToBST(self, nums: List[int]) -> Optional[TreeNode]:  # nums 是升序数组，返回一棵平衡二叉搜索树的根
        def dfs(l: int, r: int) -> Optional[TreeNode]:  # 递归函数：在闭区间 [l, r] 上建子树
            if l > r:  # 区间为空，没有元素可建
                return None  # 空区间返回 None
            mid = (l + r) >> 1  # 取中点（向下取整）作根，左右两侧元素个数尽量相等
            return TreeNode(nums[mid], dfs(l, mid - 1), dfs(mid + 1, r))  # 中点值作根，左右两半递归建子树

        return dfs(0, len(nums) - 1)  # 从整个数组区间开始建树
