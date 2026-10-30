# 题目：1506. 找到 N 叉树的根节点（Find Root of N-Ary Tree）
# 思路：把所有结点值以及所有孩子值全部异或起来——非根结点被异或两次而抵消，最后剩下的就是根的值。
# 时间复杂度：O(N)，遍历结点与全部孩子；空间复杂度：O(1)，只用一个异或累加器。
"""
# Definition for a Node.
class Node:
    def __init__(self, val=None, children=None):
        self.val = val
        self.children = children if children is not None else []
"""


class Solution:  # LeetCode 约定的题解类
    def findRoot(self, tree: List['Node']) -> 'Node':  # tree：N 叉树的全部结点列表；返回根结点
        x = 0  # 异或累加器：根的值只出现一次，其余结点的值出现两次会互相抵消
        for node in tree:  # 遍历所有结点
            x ^= node.val  # 每个结点自身的值先异或一次
            for child in node.children:  # 再遍历它的全部孩子
                x ^= child.val  # 作为孩子被异或第二次，最后只剩根的值
        return next(node for node in tree if node.val == x)  # 生成器找出值等于 x 的结点，即根结点
