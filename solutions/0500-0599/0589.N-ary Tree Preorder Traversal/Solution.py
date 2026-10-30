# 题目：589. N 叉树的前序遍历（N-ary Tree Preorder Traversal）
# 思路：递归 DFS，先记录根节点的值，再按顺序对每个孩子递归（前序 = 根 → 各子树）。
# 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(n)，答案列表与递归栈（最坏 n 层）。
"""
# Definition for a Node.
class Node:
    def __init__(self, val=None, children=None):
        self.val = val
        self.children = children
"""


class Solution:  # LeetCode 约定的题解类
    def preorder(self, root: "Node") -> List[int]:  # root 是 N 叉树的根节点，返回前序遍历的节点值列表
        def dfs(root):  # 内部递归函数：处理以 root 为根的子树
            if root is None:  # 空节点直接返回
                return  # 递归出口
            ans.append(root.val)  # 前序：先记录根节点的值
            for child in root.children:  # 再依次遍历每个孩子
                dfs(child)  # 对孩子递归，保持「根先于子树」的访问顺序

        ans = []  # 结果列表，定义在递归函数之后，靠闭包被引用
        dfs(root)  # 从根节点开始执行递归
        return ans  # 返回遍历结果
