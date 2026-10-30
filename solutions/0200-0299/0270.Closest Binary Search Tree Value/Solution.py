# 题目：270. 最接近的二叉搜索树值（Closest Binary Search Tree Value）
# 思路：利用 BST 有序性，从根开始按 target 与当前值的大小比较只走一条路径，途中记录差距最小（等距取较小值）的结点值。
# 时间复杂度：O(h)，h 为树高，只沿一条链下降；空间复杂度：O(h)，递归调用栈深度为树高。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def closestValue(self, root: Optional[TreeNode], target: float) -> int:  # root：BST 根；target：目标浮点值
        def dfs(node: Optional[TreeNode]):  # 内层递归函数：沿一条路径寻找最接近 target 的值
            if node is None:  # 空结点是递归边界
                return  # 直接返回上一层，避免访问 None 的属性
            nxt = abs(target - node.val)  # 当前结点值与 target 的差距
            nonlocal ans, diff  # 声明下面要修改外层函数的 ans 与 diff
            if nxt < diff or (nxt == diff and node.val < ans):  # 更近，或同样近但值更小（等距取小）
                diff = nxt  # 更新最小差距
                ans = node.val  # 更新最优答案
            node = node.left if target < node.val else node.right  # 目标更小走左子树，否则走右子树（只走一条路径）
            dfs(node)  # 继续沿这条路径深入

        ans = 0  # 保存当前最优答案，初值会被第一次比较覆盖
        diff = inf  # 当前最小差距，初始为正无穷
        dfs(root)  # 从根开始搜索
        return ans  # 返回离 target 最近的结点值
