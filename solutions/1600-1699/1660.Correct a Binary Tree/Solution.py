# 题目：1660. 纠正二叉树（Correct a Binary Tree）
# 思路：错误的那条边指向的是已经访问过的节点，DFS 时右孩子若已在 visited 中就直接剪断。
# 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(n)，集合与递归栈。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def correctBinaryTree(self, root: TreeNode) -> TreeNode:  # root：被篡改的二叉树根；返回纠正后的根节点
        def dfs(root):  # 内层递归函数：修正以 root 为根的子树并返回新的根
            if root is None or root.right in vis:  # 空节点返回 None；右孩子已访问过则说明右指针非法
                return None  # 返回 None，把这条非法边剪掉
            vis.add(root)  # 把当前节点加入集合，供后代检测
            root.right = dfs(root.right)  # 递归修正右子树，非法边会被置为 None
            root.left = dfs(root.left)  # 递归修正左子树
            return root  # 当前节点合法，返回它
        # 闭包会在调用时才求值，所以 vis 可以写在 dfs 定义之后
        vis = set()  # 集合记录已访问节点（dfs 闭包引用它）
        return dfs(root)  # 从根节点开始 DFS 修正
