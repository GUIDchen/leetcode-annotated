# 题目：21. 合并两个有序链表（Merge Two Sorted Lists）
# 思路：递归——两个链表头里较小的那个当新头，它的 next 继续与另一个链表递归合并。
# 时间复杂度：O(m+n)，每个结点只被访问一次；空间复杂度：O(m+n)，递归栈的深度。
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # LeetCode 约定的题解类
    def mergeTwoLists(  # list1、list2：两个升序链表的头结点（类型注解 Optional 由 LeetCode 环境提供）
        self, list1: Optional[ListNode], list2: Optional[ListNode]
    ) -> Optional[ListNode]:  # 返回合并后的升序链表头
        if list1 is None or list2 is None:  # 至少一个链表为空，无需比较
            return list1 or list2  # 返回非空的那一个（两个都空时返回 None）
        if list1.val <= list2.val:  # list1 的头更小，它应当成为合并后的头
            list1.next = self.mergeTwoLists(list1.next, list2)  # 递归合并 list1 的剩余部分与 list2
            return list1  # 返回以 list1 为头的结果
        else:  # list2 的头更小，它应当成为合并后的头
            list2.next = self.mergeTwoLists(list1, list2.next)  # 递归合并 list2 的剩余部分与 list1
            return list2  # 返回以 list2 为头的结果
