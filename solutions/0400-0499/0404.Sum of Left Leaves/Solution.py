# 题目：404. 左叶子之和（Sum of Left Leaves）
# 思路：后序递归。右子树的左叶子递归统计；左孩子单独判断，若左右孩子同时为空即为叶子，直接取值，否则继续递归。
# 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，递归栈深度为树高 h。
# TreeNode 的定义由判题器提供，这里用注释形式列出（Optional 同样由判题环境隐式导入）
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def sumOfLeftLeaves(self, root: Optional[TreeNode]) -> int:  # 求二叉树中所有「左叶子」节点值之和
        if root is None:  # 空节点没有贡献
            return 0  # 返回 0
        ans = self.sumOfLeftLeaves(root.right)  # 先递归统计右子树里的左叶子（右孩子本身不算左叶子）
        if root.left:  # 存在左孩子时，判断它是不是叶子
            if root.left.left == root.left.right:  # 左右孩子同时为 None 说明左孩子是叶子，这里用两者相等来做判断
                ans += root.left.val  # 是左叶子，把它的值累加进答案
            else:  # 否则左孩子不是叶子
                ans += self.sumOfLeftLeaves(root.left)  # 继续递归到左子树里找左叶子
        return ans  # 返回总和
