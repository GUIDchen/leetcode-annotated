# 题目：206. 反转链表（Reverse Linked List）
# 思路：哑节点 + 头插法，遍历原链表逐个把节点插到 dummy 后面，最终 dummy.next 就是反转后的头。
# 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(1)，只额外创建了一个哑节点。
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # LeetCode 约定的题解类
    def reverseList(self, head: ListNode) -> ListNode:  # head 是原链表头节点，返回反转后的新头节点
        dummy = ListNode()  # 哑节点：用它的 next 挂住已经反转好的那部分链表
        curr = head  # curr 指向当前待处理的节点，从头节点开始
        while curr:  # 沿着原链表一直走到空
            next = curr.next  # 先保存后继节点（这里沿用了内置名 next 作变量名），否则改完 next 就找不回后面的链表
            curr.next = dummy.next  # 头插法：当前节点指向已反转部分的头
            dummy.next = curr  # 哑节点改指向当前节点，它成为新的反转链头
            curr = next  # 指针后移，继续处理原链表的下一个节点
        return dummy.next  # 哑节点的 next 就是反转后的头节点
