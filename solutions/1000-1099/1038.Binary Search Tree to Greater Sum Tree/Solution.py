# 题目：1038. 从二叉搜索树到更大和树（Binary Search Tree to Greater Sum Tree）
# 思路：按「右 → 根 → 左」的反中序遍历，用外层变量 s 累加已访问节点值，把每个节点的值改写为累加和。
# 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(h)，递归栈深度等于树高 h。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def bstToGst(self, root: Optional[TreeNode]) -> Optional[TreeNode]:  # 方法：root 是 BST 根节点，返回转换后的根（结构不变，值被改写）
        def dfs(root: Optional[TreeNode]):  # 内层 DFS：对以 root 为根的子树做反中序遍历
            if root is None:  # 空节点直接返回，递归终止条件
                return  # 空节点无需处理
            dfs(root.right)  # 先走右子树，保证按节点值从大到小访问
            nonlocal s  # 声明 s 引用的是外层函数的变量，便于在闭包里累加
            s += root.val  # 把当前节点值累加进总和
            root.val = s  # 当前节点新值 = 所有不小于它的节点值之和
            dfs(root.left)  # 最后走左子树，处理更小的节点

        s = 0  # 累加器初值：还没有访问任何节点
        dfs(root)  # 从根节点启动遍历，整棵树的值被就地改写
        return root  # 返回根节点
