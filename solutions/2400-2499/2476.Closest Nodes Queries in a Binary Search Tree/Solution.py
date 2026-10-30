# 题目：2476. 二叉搜索树最近节点查询（Closest Nodes Queries in a Binary Search Tree）
# 思路：中序遍历 BST 得到升序数组 nums，再对每个查询 x 二分出「小于 x 的最大值」和「大于等于 x 的最小值」，不存在则填 -1。
# 时间复杂度：O(n + q log n)，一次遍历加每个查询两次二分；空间复杂度：O(n)，存中序数组与答案。
# 下面是题目给定的二叉树结点定义（判题器会提供），保持原样不作改动
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def closestNodes(  # root 是 BST 根；queries 是查询数组；返回每个查询的两个候选值
        self, root: Optional[TreeNode], queries: List[int]  # 续行写参数：self 是实例，root 是 BST 根，queries 是查询数组
    ) -> List[List[int]]:  # 返回每个查询的 [小于 x 的最大值, 大于等于 x 的最小值]
        def dfs(root: Optional[TreeNode]):  # 中序遍历：左 → 根 → 右，保证访问顺序升序
            if root is None:  # 空结点直接返回，作为递归出口
                return  # 递归出口，什么都不做
            dfs(root.left)  # 先遍历左子树，得到所有更小的值
            nums.append(root.val)  # 再访问根结点，保证升序排列
            dfs(root.right)  # 最后遍历右子树，得到所有更大的值

        nums = []  # 存放中序结果，BST 的中序序列天然升序
        dfs(root)  # 从根开始做一次完整的中序遍历
        ans = []  # 每个查询对应一个长度为 2 的答案列表
        for x in queries:  # 逐个处理查询
            i = bisect_left(nums, x + 1) - 1  # 第一个 ≥ x+1 的位置减一即「小于 x 的最大值」
            j = bisect_left(nums, x)  # 第一个 ≥ x 的位置即「大于等于 x 的最小值」
            mi = nums[i] if 0 <= i < len(nums) else -1  # 下标越界说明不存在小于 x 的值，填 -1
            mx = nums[j] if 0 <= j < len(nums) else -1  # 下标越界说明不存在大于等于 x 的值，填 -1
            ans.append([mi, mx])  # 按题目顺序收集 [最小值, 最大值]
        return ans  # 返回全部查询的答案
