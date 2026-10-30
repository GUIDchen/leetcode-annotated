# 题目：1676. 二叉树的最近公共祖先 IV（Lowest Common Ancestor of a Binary Tree IV）
# 思路：把目标节点的值放入集合，自底向上 DFS：空或命中集合则返回自身，左右都非空则当前节点为最近公共祖先。
# 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(n)，集合与递归深度最坏均为 n。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None


class Solution:  # LeetCode 约定的题解类
    def lowestCommonAncestor(  # root：二叉树根节点；nodes：目标节点列表
        self, root: 'TreeNode', nodes: 'List[TreeNode]'  # 换行书写参数，root 是根、nodes 是要求公共祖先的节点
    ) -> 'TreeNode':  # 返回值为 TreeNode，即最近公共祖先
        def dfs(root):  # 内层递归函数，定义在方法里以便直接使用外层变量 s
            if root is None or root.val in s:  # 空节点或命中目标节点时返回当前节点
                return root  # 先递归左右子树，再根据结果判断
            left, right = dfs(root.left), dfs(root.right)  # 左右都找到目标节点，当前节点就是最近公共祖先
            if left and right:  # 返回当前节点
                return root  # 只在一侧找到时，返回那一侧的结果
            return left or right  # 空行：递归函数定义结束
  # 空行：准备集合 s，供上面 dfs 通过闭包访问
        s = {node.val for node in nodes}  # 把所有目标节点的值放进集合，保证 O(1) 判断
        return dfs(root)  # 从根节点开始搜索并返回结果
