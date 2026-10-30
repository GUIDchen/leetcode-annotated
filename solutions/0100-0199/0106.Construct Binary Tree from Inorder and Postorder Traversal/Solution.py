# 题目：106. 从中序与后序遍历序列构造二叉树（Construct Binary Tree from Inorder and Postorder Traversal）
# 思路：后序序列的末尾元素一定是根，先用字典记下「值 → 中序下标」，再按根的下标把区间切成左右两段递归建树。
# 时间复杂度：O(n)，每个结点只创建一次；空间复杂度：O(n)，字典与递归栈。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def buildTree(self, inorder: List[int], postorder: List[int]) -> Optional[TreeNode]:  # inorder 是中序序列，postorder 是后序序列，返回建好的二叉树根节点
        def dfs(i: int, j: int, n: int) -> Optional[TreeNode]:  # 递归函数：i 是中序区间起点，j 是后序区间起点，n 是当前子树的结点个数
            if n <= 0:  # 没有结点，说明当前子树为空
                return None  # 空子树返回 None
            v = postorder[j + n - 1]  # 后序区间的最后一个元素就是当前子树的根值
            k = d[v]  # 根值在中序中的下标，用它划分左右子树
            l = dfs(i, j, k - i)  # 左子树：中序起点 i，后序起点 j，大小是 k - i
            r = dfs(k + 1, j + k - i, n - k + i - 1)  # 右子树：中序起点 k+1，后序起点 j + 左子树大小，大小是 n - 左子树大小 - 1
            return TreeNode(v, l, r)  # 用根值建结点，并把左右子树接上

        d = {v: i for i, v in enumerate(inorder)}  # 先建字典：值 → 它在 inorder 中的下标，供递归里 O(1) 定位根
        return dfs(0, 0, len(inorder))  # 从整棵树开始：中序起点 0，后序起点 0，大小是序列长度
