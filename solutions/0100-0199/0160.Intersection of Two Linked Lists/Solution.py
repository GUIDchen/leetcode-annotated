# 题目：160. 相交链表（Intersection of Two Linked Lists）
# 思路：双指针同步前进，走完自己那条链后跳到对方链头；两条指针走过的总长度相同，必然同时到达交点或同时到达 None。
# 时间复杂度：O(m+n)，每条链最多走两遍；空间复杂度：O(1)，只用两个指针。
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None


class Solution:  # LeetCode 约定的题解类
    def getIntersectionNode(self, headA: ListNode, headB: ListNode) -> ListNode:  # headA、headB：两条链表头节点；返回第一个相交节点，不相交时返回 None
        a, b = headA, headB  # 两个游标分别从各自链表头出发
        while a != b:  # 指针相同即相遇（交点或都为 None），此时结束循环
            a = a.next if a else headB  # a 走到自己链尾后换到 B 头，补齐两链长度差
            b = b.next if b else headA  # b 走到自己链尾后换到 A 头
        return a  # 返回相遇点：相交时是交点，不相交时是 None
