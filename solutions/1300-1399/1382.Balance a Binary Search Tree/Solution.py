# 题目：1382. 将二叉搜索树变平衡（Balance a Binary Search Tree）
# 思路：中序遍历得到升序数组，再以「每次取中点作根」的方式递归重建平衡 BST。
# 时间复杂度：O(n)，中序与建树各遍历一次；空间复杂度：O(n)，存放中序数组并占用递归栈。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def balanceBST(self, root: TreeNode) -> TreeNode:  # root：原二叉搜索树的根节点
        def dfs(root: TreeNode):  # 中序遍历，把键值按升序追加到外层 nums
            if root is None:  # 空节点是递归出口
                return  # 直接返回，什么都不做
            dfs(root.left)  # 先递归处理左子树（值更小）
            nums.append(root.val)  # 再访问根节点，记录键值
            dfs(root.right)  # 最后递归处理右子树（值更大）

        def build(i: int, j: int) -> TreeNode:  # 把 nums[i..j] 构造成平衡 BST
            if i > j:  # 区间为空
                return None  # 返回 None 作为空子树
            mid = (i + j) >> 1  # 取中点作根，保证左右子树高度接近
            left = build(i, mid - 1)  # 递归构造左子树
            right = build(mid + 1, j)  # 递归构造右子树
            return TreeNode(nums[mid], left, right)  # 以中点为根拼装新节点

        nums = []  # 存放中序遍历得到的升序键值
        dfs(root)  # 执行中序遍历填充 nums
        return build(0, len(nums) - 1)  # 用整个数组重建平衡 BST 并返回新根
