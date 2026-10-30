# 题目：655. 输出二叉树（Print Binary Tree）
# 核心思路：先求树高，按满二叉树尺寸建矩阵，再递归按行与居中偏移填值。
# 时间复杂度：O(h * 2^h)（矩阵规模）；空间复杂度：O(h * 2^h)。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def printTree(self, root: Optional[TreeNode]) -> List[List[str]]:  # root 是树根，返回按层展开的字符串矩阵
        def height(root):  # 内层函数：求以 root 为根的子树高度
            if root is None:  # 空节点高度记为 -1
                return -1  # 返回 -1，这样行数可以写成 h + 1
            return 1 + max(height(root.left), height(root.right))  # 非空节点高度 = 两棵子树较大高度 + 1

        def dfs(root, r, c):  # 内层函数：把节点值写到矩阵第 r 行第 c 列
            if root is None:  # 空节点不占格子，无需填写
                return  # 直接返回，作为递归出口
            ans[r][c] = str(root.val)  # 节点值转成字符串后放入对应格子
            dfs(root.left, r + 1, c - 2 ** (h - r - 1))  # 左孩子下移一行，列向左偏移 2^(h-r-1)
            dfs(root.right, r + 1, c + 2 ** (h - r - 1))  # 右孩子下移一行，列向右偏移 2^(h-r-1)

        h = height(root)  # 求出整棵树的高度
        m, n = h + 1, 2 ** (h + 1) - 1  # 行数 h+1；列数 2^(h+1)-1（满二叉树的格子总数）
        ans = [[""] * n for _ in range(m)]  # 构造 m 行 n 列、初值为空串的矩阵
        dfs(root, 0, (n - 1) // 2)  # 根放在第 0 行第 (n-1)//2 列（正中间）
        return ans  # 返回填好的矩阵
