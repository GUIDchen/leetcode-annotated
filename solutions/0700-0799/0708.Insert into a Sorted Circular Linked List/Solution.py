# 题目：708. 循环有序列表的插入（Insert into a Sorted Circular Linked List）
# 思路：从 head 出发绕环一圈，在「值落在 prev 与 curr 之间」或「跨过最大值到最小值的断点」处插入；空表则让新结点自成一环。
# 时间复杂度：O(n)，最坏绕环一整圈；空间复杂度：O(1)，只新建一个结点。
"""
# Definition for a Node.
class Node:
    def __init__(self, val=None, next=None):
        self.val = val
        self.next = next
"""


class Solution:  # LeetCode 约定的题解类
    def insert(self, head: 'Optional[Node]', insertVal: int) -> 'Node':  # head 是循环有序链表头，insertVal 是待插入值，返回链表头
        node = Node(insertVal)  # 先创建待插入的新结点
        if head is None:  # 空链表：新结点自己组成一个环
            node.next = node  # 指向自己，形成自环
            return node  # 返回新结点作为链表头
        prev, curr = head, head.next  # 相邻游标 prev 与 curr，curr 从 head.next 开始，便于判断一段区间
        while curr != head:  # 绕环扫描，curr 回到 head 说明转满一圈
            if prev.val <= insertVal <= curr.val or (  # 两个可插入条件：普通升序区间内，或跨过最大值到最小值的断点处
                prev.val > curr.val and (insertVal >= prev.val or insertVal <= curr.val)
            ):
                break  # 找到插入位置，跳出循环
            prev, curr = curr, curr.next  # prev 与 curr 一起前移一个结点，保持相邻
        prev.next = node  # 把新结点接到 prev 之后
        node.next = curr  # 新结点指向 curr，保持环的完整
        return head  # 头结点不变，返回原 head
