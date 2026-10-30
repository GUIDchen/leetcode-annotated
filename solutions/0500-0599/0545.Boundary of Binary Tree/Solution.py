# 题目：545. 二叉树的边界（Boundary of Binary Tree）🔒
# 思路：答案由四段拼成——根、左边界（自顶向下、不含叶子）、全部叶子、右边界（逆序），用一个内部 DFS 按 i=0/1/2 三种模式收集。
# 时间复杂度：O(n)，每个节点只被一种模式访问一次；空间复杂度：O(h)，递归深度等于树高（不含答案列表）。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def boundaryOfBinaryTree(self, root: Optional[TreeNode]) -> List[int]:  # root 是根节点，返回逆时针排列的边界节点值列表
        def dfs(nums: List[int], root: Optional[TreeNode], i: int):  # 内部 DFS：nums 收集结果，i=0 取左边界 / i=1 取叶子 / i=2 取右边界
            if root is None:  # 递归出口：空节点直接返回
                return  # 什么都不需要做
            if i == 0:  # 模式 0：自顶向下收集左边界
                if root.left != root.right:  # 左右孩子不同则说明不是叶子（叶子的左右都为空）
                    nums.append(root.val)  # 记录这个左边界节点
                    if root.left:  # 有左孩子就优先往左走
                        dfs(nums, root.left, i)  # 继续沿左子树收集左边界
                    else:  # 没有左孩子就只能往右走
                        dfs(nums, root.right, i)  # 沿右孩子继续收集左边界
            elif i == 1:  # 模式 1：收集全部叶子
                if root.left == root.right:  # 左右都为空，说明是叶子
                    nums.append(root.val)  # 记录叶子节点的值
                else:  # 不是叶子就继续往下找
                    dfs(nums, root.left, i)  # 左子树里找叶子
                    dfs(nums, root.right, i)  # 右子树里找叶子
            else:  # 模式 2：自顶向下收集右边界（最后整体逆序）
                if root.left != root.right:  # 同样要求当前节点不是叶子
                    nums.append(root.val)  # 记录这个右边界节点
                    if root.right:  # 有右孩子就优先往右走
                        dfs(nums, root.right, i)  # 继续沿右子树收集右边界
                    else:  # 没有右孩子就只能往左走
                        dfs(nums, root.left, i)  # 沿左孩子继续收集右边界

        ans = [root.val]  # 根节点必然在边界上，先放进答案
        if root.left == root.right:  # 根同时也是叶子时，边界只有根自己
            return ans  # 直接返回单元素答案
        left, leaves, right = [], [], []  # 三段边界分别收集：left 左边界、leaves 叶子、right 右边界
        dfs(left, root.left, 0)  # 从根的左孩子开始收集左边界
        dfs(leaves, root, 1)  # 从根开始收集全部叶子
        dfs(right, root.right, 2)  # 从根的右孩子开始收集右边界
        ans += left + leaves + right[::-1]  # 右边界用切片 [::-1] 逆序后再拼接，符合逆时针方向
        return ans  # 返回完整边界序列
