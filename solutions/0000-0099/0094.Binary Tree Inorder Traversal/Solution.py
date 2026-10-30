# 题目：94. 二叉树的中序遍历（Binary Tree Inorder Traversal）
# 思路：递归实现中序遍历，按「左子树 → 根 → 右子树」的顺序把结点值追加到结果列表。
# 时间复杂度：O(n)，每个结点恰好访问一次；空间复杂度：O(n)，最坏情况递归栈深度为 n。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def inorderTraversal(self, root: Optional[TreeNode]) -> List[int]:  # root 是二叉树根结点，返回中序序列
        def dfs(root):  # 内部递归函数：对以 root 为根的子树做中序遍历
            if root is None:  # 空结点没有可遍历的内容
                return  # 递归出口：直接返回上一层
            dfs(root.left)  # 中序第一步：先完整遍历左子树
            ans.append(root.val)  # 左子树处理完，再记录根结点的值
            dfs(root.right)  # 最后遍历右子树

        ans = []  # 结果列表：按中序存放结点值
        dfs(root)  # 从根结点开始遍历
        return ans  # 返回中序遍历结果
