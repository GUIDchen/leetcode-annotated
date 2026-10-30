# 题目：1721. 交换链表中的节点（Swapping Nodes in a Linked List）难度：中等
# 思路：快指针先走 k-1 步停在正数第 k 个节点 p 上；随后快慢指针同步后移，快指针到末尾时慢指针正好落在倒数第 k 个节点 q 上，
# 最后交换 p、q 两个节点的值即可（题目允许只交换 val，不必改动指针连接）。
# 时间复杂度：O(n)，链表最多遍历两趟；空间复杂度：O(1)，只用了几个指针变量。
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # LeetCode 约定的题解类
    def swapNodes(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:  # head：链表头；k：要交换的节点序号
        fast = slow = head  # 两个指针都从头开始
        for _ in range(k - 1):  # 快指针先走 k-1 步
            fast = fast.next  # 快指针后移一步
        p = fast  # p 记录正数第 k 个节点
        while fast.next:  # 快指针走到尾节点就停下
            fast, slow = fast.next, slow.next  # 快慢指针同步后移，二者间距恒为 k-1
        q = slow  # 快指针到尾部时，慢指针正好是倒数第 k 个节点
        p.val, q.val = q.val, p.val  # 只交换两个节点的值，避免修改链表结构
        return head  # 链表头不变，直接返回
