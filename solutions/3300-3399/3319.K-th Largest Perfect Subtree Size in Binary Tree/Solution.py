# 题目：3319. 第 K 大的完美二叉子树的大小（K-th Largest Perfect Subtree Size in Binary Tree）
# 思路：后序 DFS 返回「以当前节点为根的子树大小」，非完美二叉树返回 -1；把所有完美子树的大小收集后降序排序，取第 k 个。
# 时间复杂度：O(n log n)，n 为节点数（DFS 一次遍历 + 排序）；空间复杂度：O(n)，递归栈与存放子树大小的列表。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def kthLargestPerfectSubtree(self, root: Optional[TreeNode], k: int) -> int:  # root：二叉树根节点；k：要求的第 k 大
        def dfs(root: Optional[TreeNode]) -> int:  # 内部递归函数：返回子树大小，不完美则返回 -1
            if root is None:  # 空节点：空树视为完美
                return 0  # 用 0 表示空子树是完美的
            l, r = dfs(root.left), dfs(root.right)  # 先递归左右子树，得到各自的大小或 -1
            if l < 0 or l != r:  # 左右有不完美的，或左右大小不等，当前树不完美
                return -1  # -1 作为不完美的哨兵值向上传递
            cnt = l + r + 1  # 完美时加上根节点得到当前完美子树大小
            nums.append(cnt)  # 记录这个完美子树的大小
            return cnt  # 返回大小供父节点判断

        nums = []  # 存放所有完美二叉子树的大小；因为闭包在调用时才查名字，定义在 dfs 之后也可用
        dfs(root)  # 从根开始 DFS，顺便填满 nums
        if len(nums) < k:  # 完美子树不足 k 个
            return -1  # 按题意返回 -1
        nums.sort(reverse=True)  # 降序排序
        return nums[k - 1]  # 下标 k-1 就是第 k 大的大小
