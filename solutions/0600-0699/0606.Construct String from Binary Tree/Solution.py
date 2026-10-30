# 题目：606. 根据二叉树创建字符串（Construct String from Binary Tree）
# 思路：对子树递归地做前序遍历拼接，叶节点只写值；只有左孩子时省略右括号但对，右孩子存在时左右都要括号。
# 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(n)，递归深度与结果字符串。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类（上方是题目自带的 TreeNode 定义注释）
    def tree2str(self, root: Optional[TreeNode]) -> str:  # 把以 root 为根的子树转换成形如 1(2)(3) 的字符串
        def dfs(root):  # 辅助递归函数，负责把单个子树序列化
            if root is None:  # 空节点不产生任何字符
                return ''  # 返回空串，调用方自然不会拼出括号
            if root.left is None and root.right is None:  # 叶子节点是最简单的情况
                return str(root.val)  # 叶节点只输出自身的值，不加括号
            if root.right is None:  # 只有左孩子，右孩子为空
                return f'{root.val}({dfs(root.left)})'  # 只写左子树的括号，右子树的空括号按题意省略
            return f'{root.val}({dfs(root.left)})({dfs(root.right)})'  # 右孩子存在时必须先写左子树的括号（哪怕是空括号），再写右子树

        return dfs(root)  # 从整棵树的根节点开始递归，返回最终字符串
