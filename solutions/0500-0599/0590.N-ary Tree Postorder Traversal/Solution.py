# 题目：590. N 叉树的后序遍历（N-ary Tree Postorder Traversal）
# 思路：递归 DFS，先按顺序对每个孩子递归，最后才记录根节点的值（后序 = 各子树 → 根）。
# 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(n)，答案列表与递归栈（最坏 n 层）。
"""
# Definition for a Node.
class Node:
    def __init__(self, val=None, children=None):
        self.val = val
        self.children = children
"""


class Solution:  # LeetCode 约定的题解类
    def postorder(self, root: 'Node') -> List[int]:  # root 是 N 叉树的根节点，返回后序遍历的节点值列表
        def dfs(root):  # 内部递归函数：处理以 root 为根的子树
            if root is None:  # 空节点直接返回
                return  # 递归出口
            for child in root.children:  # 后序：先把所有孩子都处理完
                dfs(child)  # 对孩子递归，保证子树结果先于根节点写入
            ans.append(root.val)  # 最后才记录根节点的值

        ans = []  # 结果列表，定义在递归函数之后，靠闭包被引用
        dfs(root)  # 从根节点开始执行递归
        return ans  # 返回遍历结果
