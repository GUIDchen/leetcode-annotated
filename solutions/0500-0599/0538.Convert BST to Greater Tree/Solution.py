# 题目：538. 把二叉搜索树转换为累加树（Convert BST to Greater Tree）
# 思路：反向中序遍历（右-根-左）恰好按节点值从大到小访问，用累加和 s 边遍历边把节点值改为「大于等于它的所有值之和」。
# 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，递归栈深度等于树高 h。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def convertBST(self, root: TreeNode) -> TreeNode:  # 入口：原地修改整棵树并返回根节点
        def dfs(root):  # 内层递归函数：按 右子树 → 根 → 左子树 的顺序访问
            nonlocal s  # 声明 s 来自外层函数，这里修改的是同一个变量而不是新建局部变量
            if root is None:  # 空节点直接返回，作为递归边界
                return  # 递归终止：什么都不做
            dfs(root.right)  # 先处理右子树：右子树的值都大于当前节点，必须先把它们累加进 s
            s += root.val  # 把当前节点值加入累加和，得到「大于等于当前值的所有节点值之和」
            root.val = s  # 用累加和覆盖原值，完成本题要求的转换
            dfs(root.left)  # 再处理左子树：此时 s 已包含所有比它大的值

        s = 0  # 累加和的初值为 0
        dfs(root)  # 从根节点开始反向中序遍历
        return root  # 返回被原地修改后的根节点
