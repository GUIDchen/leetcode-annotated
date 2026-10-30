# 题目：654. 最大二叉树（Maximum Binary Tree）
# 核心思路：用 max 取区间最大值作根，再对左右切片递归建树。
# 时间复杂度：O(n^2)（每次 max/index 都要遍历切片）或 O(n log n) 平均；空间复杂度：O(n)。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def constructMaximumBinaryTree(self, nums: List[int]) -> Optional[TreeNode]:  # nums 是输入数组，返回按规则构建的二叉树根节点
        def dfs(nums):  # 内层递归：为数组切片 nums 建树并返回根节点
            if not nums:  # 切片为空说明没有节点可建
                return None  # 空切片返回 None，作为递归出口
            val = max(nums)  # 当前子树的根值就是切片中的最大值
            i = nums.index(val)  # 定位最大值下标，用来切分左右子切片
            root = TreeNode(val)  # 以最大值创建根节点
            root.left = dfs(nums[:i])  # 左子树由最大值左侧切片 nums[:i] 递归构建
            root.right = dfs(nums[i + 1 :])  # 右子树由最大值右侧切片 nums[i+1:] 递归构建
            return root  # 返回拼好的当前子树根

        return dfs(nums)  # 从整个数组开始递归
