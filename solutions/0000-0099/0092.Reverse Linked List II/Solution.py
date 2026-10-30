# 题目：92. 反转链表 II（Reverse Linked List II）
# 思路：用哨兵结点统一边界，先走 left-1 步找到区间前驱，再用头插法把区间内 right-left+1 个结点原地反转。
# 时间复杂度：O(n)，最多遍历一遍链表；空间复杂度：O(1)，只用常数个指针。
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # LeetCode 约定的题解类
    def reverseBetween(  # 反转第 left 到第 right 个结点（下标从 1 开始）
        self, head: Optional[ListNode], left: int, right: int  # head 是链表头；left / right 是闭区间端点
    ) -> Optional[ListNode]:  # 返回反转后的链表头
        if head.next is None or left == right:  # 只有一个结点，或区间长度为 1，都不需要反转
            return head  # 直接返回原头结点
        dummy = ListNode(0, head)  # 哨兵结点指向原头，统一处理 left == 1 的情况
        pre = dummy  # pre 用来走向反转区间的前驱
        for _ in range(left - 1):  # 前进 left-1 步
            pre = pre.next  # 一步一步后移，最终停在区间前驱上
        p, q = pre, pre.next  # p 记住前驱；q 记住区间第一个结点（反转后会变成区间尾）
        cur = q  # cur 是当前正在被反转的结点
        for _ in range(right - left + 1):  # 只反转区间内的这些结点
            t = cur.next  # 先保存后继，避免断链后丢失
            cur.next = pre  # 反转指针：当前结点指向前驱
            pre, cur = cur, t  # 元组赋值同时前移：pre 变成当前结点，cur 变成原来的后继
        p.next = pre  # 区间前驱接到反转后的区间头
        q.next = cur  # 原区间头（现区间尾）接到区间后面的第一个结点
        return dummy.next  # 哨兵的后继就是真正的头结点
