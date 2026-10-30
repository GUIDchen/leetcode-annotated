# 题目：257. 二叉树的所有路径（Binary Tree Paths）
# 思路：DFS 回溯。列表 t 维护根到当前节点的路径，遇到叶子时用 "->" 拼接成字符串存入 ans，返回上一层前弹出当前节点。
# 时间复杂度：O(n^2)，每条路径的拼接代价与其长度成正比；空间复杂度：O(n)，递归栈与路径列表。

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def binaryTreePaths(self, root: Optional[TreeNode]) -> List[str]:  # root：二叉树根节点
        def dfs(root: Optional[TreeNode]):  # 内层递归：深度优先遍历以 root 为根的子树
            if root is None:  # 空节点直接返回，作为递归边界
                return  # 不做任何处理
            t.append(str(root.val))  # 当前节点值转成字符串后压入路径
            if root.left is None and root.right is None:  # 左右孩子都为空，说明当前节点是叶子
                ans.append("->".join(t))  # 用 "->" 把整条路径拼起来放入结果集
            else:  # 否则继续递归左右子树
                dfs(root.left)  # 遍历左子树
                dfs(root.right)  # 遍历右子树
            t.pop()  # 回溯：离开当前节点时把它从路径中弹出

        ans = []  # 结果集：所有根到叶子的路径
        t = []  # 回溯路径：当前路径上的节点值
        dfs(root)  # 从根节点开始遍历
        return ans  # 返回所有路径
