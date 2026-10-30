# 题目：144. 二叉树的前序遍历（Binary Tree Preorder Traversal）
# 思路：递归 DFS，按「根 → 左 → 右」的次序访问节点，把节点值依次追加到结果列表。
# 时间复杂度：O(n)，每个节点恰好访问一次；空间复杂度：O(h) 递归栈（h 为树高），结果列表另占 O(n)。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def preorderTraversal(self, root: Optional[TreeNode]) -> List[int]:  # root：树根；返回前序遍历得到的值列表
        def dfs(root):  # 内层递归函数，直接闭包引用外层的 ans
            if root is None:  # 空节点是递归终止条件
                return  # 直接返回上一层
            ans.append(root.val)  # 前序：先记录根节点的值
            dfs(root.left)  # 再遍历左子树
            dfs(root.right)  # 最后遍历右子树

        ans = []  # 结果列表在 dfs 定义之后再创建，闭包运行时仍能访问到它
        dfs(root)  # 从根节点开始遍历
        return ans  # 返回前序序列
