# 题目：1666. 改变二叉树的根节点（Change the Root of a Binary Tree）
# 思路：从 leaf 沿 parent 指针一路翻转到 root，边翻转边把原父节点中指向自己的孩子指针置空，最后把 leaf 的 parent 置 None。
# 时间复杂度：O(h)，h 为 leaf 到 root 的路径长度；空间复杂度：O(1)，只用了常数个指针。
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
    def flipBinaryTree(self, root: "Node", leaf: "Node") -> "Node":  # root：原根节点；leaf：即将成为新根的节点，返回新的根
        cur = leaf  # cur：当前要向上翻转的节点，从新根 leaf 出发
        p = cur.parent  # p：cur 的原父节点，翻转后会成为 cur 的左孩子
        while cur != root:  # 沿 parent 链一路翻转，直到处理完原根为止
            gp = p.parent  # 先记下祖父节点，它是下一轮的父节点
            if cur.left:  # cur 原本有左孩子
                cur.right = cur.left  # 把原左孩子挪到右孩子位置，左侧要留给原父节点
            cur.left = p  # 原父节点变成 cur 的左孩子
            p.parent = cur  # 同步维护方向相反的 parent 指针
            if p.left == cur:  # 原树中 cur 曾是 p 的左孩子
                p.left = None  # 断开 p 指向 cur 的旧左指针，避免残留环
            elif p.right == cur:  # 否则再判断 cur 是否曾是 p 的右孩子
                p.right = None  # 断开 p 指向 cur 的旧右指针
            cur = p  # 向上推进到原父节点
            p = gp  # p 也随之向上移动一层
        leaf.parent = None  # 新根节点没有父节点
        return leaf  # 返回翻转后的新根
