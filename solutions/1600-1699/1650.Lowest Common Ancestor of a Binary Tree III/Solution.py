# 题目：1650. 二叉树的最近公共祖先 III（Lowest Common Ancestor of a Binary Tree III）
# 思路：从 p 沿 parent 向上把整条祖先链放进集合，再从 q 沿 parent 向上，第一个落在集合里的节点就是最近公共祖先。
# 时间复杂度：O(h)，h 为树高；空间复杂度：O(h)，集合存放 p 的祖先链。
# 下面的 """ """ 是题目自带的 Node 定义说明，保持原样
"""
# Definition for a Node.
class Node:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None
        self.parent = None
"""


class Solution:  # LeetCode 约定的题解类
    def lowestCommonAncestor(self, p: "Node", q: "Node") -> "Node":  # p、q 为两个节点，返回它们的最近公共祖先
        vis = set()  # 记录 p 到根路径上的节点
        node = p  # 从 p 开始向上走
        while node:  # node 非空时继续（根的 parent 为 None）
            vis.add(node)  # 把当前节点加入集合
            node = node.parent  # 上移到父节点
        node = q  # 换到 q，开始向上找第一个重复节点
        while node not in vis:  # 直到遇到 p 的祖先（根必然在集合中，循环必停）
            node = node.parent  # 继续上移一层
        return node  # 该节点即最近公共祖先
