# 题目：1740. 找到二叉树中的距离（Find Distance in a Binary Tree）
# 思路：先用递归求出 p、q 的最近公共祖先 g，再从 g 出发分别 DFS 求到 p、q 的边数，两者相加就是两点间的距离。
# 时间复杂度：O(n)，求 LCA 和两次 DFS 各自最多遍历一遍节点；空间复杂度：O(h)，递归栈深度为树高 h。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def findDistance(self, root: Optional[TreeNode], p: int, q: int) -> int:  # root：二叉树根；p、q：要求距离的两个节点值
        def lca(root, p, q):  # 求最近公共祖先：返回 p、q 的 LCA 节点
            if root is None or root.val in [p, q]:  # 走到空节点，或当前节点就是 p/q，就直接返回它
                return root  # 返回当前节点作为这一支找到的结果
            left = lca(root.left, p, q)  # 在左子树里递归寻找
            right = lca(root.right, p, q)  # 在右子树里递归寻找
            if left is None:  # 左子树里一个都没找到
                return right  # 答案只能落在右子树
            if right is None:  # 右子树里一个都没找到
                return left  # 答案只能落在左子树
            return root  # 左右各找到一个，当前节点就是最近公共祖先

        def dfs(root, v):  # 从 root 出发走到值为 v 的节点，返回经过的边数
            if root is None:  # 走到空节点说明这条路上没有 v
                return -1  # 用 -1 表示这一支找不到
            if root.val == v:  # 正好是目标节点
                return 0  # 距离为 0
            left, right = dfs(root.left, v), dfs(root.right, v)  # 一次性拿到左右子树各自的结果
            if left == right == -1:  # 链式比较：两边都是 -1，说明都没找到
                return -1  # 向上继续报告失败
            return 1 + max(left, right)  # 找到的那一侧距离加一，就是当前节点到 v 的边数

        g = lca(root, p, q)  # 先拿到 p、q 的最近公共祖先，两点路径必经此处
        return dfs(g, p) + dfs(g, q)  # 距离 = g 到 p 的边数 + g 到 q 的边数
