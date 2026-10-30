# 题目：1669. 合并两个链表（Merge In Between Linked Lists）
# 思路：双指针分别停在第 a-1 个节点 p 与第 b 个节点 q，把 list2 接到 p 之后，再把 list2 的尾巴接到 q.next。
# 时间复杂度：O(n + m)，n 为 list1 长度、m 为 list2 长度；空间复杂度：O(1)，只用了常数个指针。
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # LeetCode 约定的题解类
    def mergeInBetween(  # 删掉 list1 中下标 [a, b] 的节点并把 list2 接进去
        self, list1: ListNode, a: int, b: int, list2: ListNode  # 参数：list1 与 list2 两个链表头，以及要删除的区间 [a, b]
    ) -> ListNode:  # 返回合并后的链表头
        p = q = list1  # p 用于定位第 a-1 个节点，q 用于定位第 b 个节点
        for _ in range(a - 1):  # p 前移 a-1 步
            p = p.next  # 指针前移
        for _ in range(b):  # q 前移 b 步
            q = q.next  # 指针前移
        p.next = list2  # 把 list2 的头接到 p 后面
        while p.next:  # 一路走到 list2 的尾节点
            p = p.next  # 指针前移
        p.next = q.next  # 把 list2 的尾巴接到 b 号节点之后的那段链表
        q.next = None  # 断开 q 之后原来的链接，避免残留多余节点
        return list1  # 返回合并后的链表头
