# 3831. 二叉搜索树某一层的中位数 / Median of a Binary Search Tree Level（中等）
# 核心思路：BST 的中序遍历结果递增，所以递归地把指定层的节点值按中序加入列表，取下标 len//2 的元素即为该层中位数。
# 复杂度：遍历整棵树，时间 O(n)，空间 O(h + k)，h 为树高、k 为目标层节点数。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # 设计一个求 BST 指定层中位数的算法
    def levelMedian(self, root: Optional[TreeNode], level: int) -> int:  # 返回第 level 层（根为第 0 层）的中位数，该层为空时返回 -1
        def dfs(root: Optional[TreeNode], i: int):  # 闭包递归函数：i 表示当前节点所在层号（根为 0）
            if root is None:  # 空节点直接返回
                return  # 结束当前递归分支
            dfs(root.left, i + 1)  # 先遍历左子树，层号加一
            if i == level:  # 当前节点恰好位于目标层
                nums.append(root.val)  # 追加节点值，中序顺序保证列表递增
            dfs(root.right, i + 1)  # 再遍历右子树，层号加一

        nums = []  # 收集结果的列表，定义在递归调用之前（闭包在调用时才解析该名字）
        dfs(root, 0)  # 从根节点第 0 层开始遍历
        return nums[len(nums) // 2] if nums else -1  # 该层为空返回 -1，否则取有序列表的中间下标即上中位数
