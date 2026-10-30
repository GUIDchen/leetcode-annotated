# 题目：430. 扁平化多级双向链表（Flatten a Multilevel Doubly Linked List）
# 思路：按前序顺序深度优先遍历，遇到 child 就递归展平子链表并把它插到当前节点与 next 之间，返回展平后的尾节点供上一层继续拼接。
# 时间复杂度：O(n)，n 为全部节点数；空间复杂度：O(层级深度)，来自递归栈。
# 说明：下面是题目自带的 Node 定义（注释块，由判题器提供），仅作参考。
"""
# Definition for a Node.
class Node:
    def __init__(self, val, prev, next, child):
        self.val = val
        self.prev = prev
        self.next = next
        self.child = child
"""


class Solution:  # LeetCode 题解类
    def flatten(self, head: 'Node') -> 'Node':  # head：多级双向链表头节点；返回展平后的头节点
        def preorder(pre, cur):  # pre：已展平部分当前的尾节点；cur：待接入的节点
            if cur is None:  # 没有更多节点可接
                return pre  # 返回已展平部分的尾节点
            cur.prev = pre  # 当前节点的 prev 指向已展平部分的尾节点
            pre.next = cur  # 尾节点的 next 指向当前节点

            t = cur.next  # 先保存原 next，因为递归处理 child 时会改写链接
            tail = preorder(cur, cur.child)  # 递归展平 child 子链表，cur 作为它的前驱
            cur.child = None  # 题目要求展平后 child 必须置为 None
            return preorder(tail, t)  # 接着把原 next 及其后续接到子链表尾部

        if head is None:  # 空链表
            return None  # 直接返回 None
        dummy = Node(0, None, head, None)  # 哑节点：next 指向链表头，充当第一个节点的 prev
        preorder(dummy, head)  # 从哑节点和头节点开始递归展平
        dummy.next.prev = None  # 展平后头节点的 prev 仍指向哑节点，需要改回 None
        return dummy.next  # 返回真正的头节点
