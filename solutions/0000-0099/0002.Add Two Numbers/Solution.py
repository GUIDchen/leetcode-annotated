# 题目：2. 两数相加（Add Two Numbers）
# 思路：哑结点串起结果链表，两个链表指针同步前进逐位相加，carry 保存进位，缺位时按 0 处理。
# 时间复杂度：O(max(m, n))，m、n 为两链表长度；空间复杂度：O(max(m, n))，为结果链表新建的结点。
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # LeetCode 约定的题解类
    def addTwoNumbers(  # 方法签名第一行：参数因太长而换行书写
        self, l1: Optional[ListNode], l2: Optional[ListNode]  # self 为实例；l1、l2 是逆序存数的链表，Optional 表示可能为空
    ) -> Optional[ListNode]:  # 返回相加后的链表头，类型注解不额外 import（LeetCode 环境已提供）
        dummy = ListNode()  # 哑结点：让尾插法不必特判结果链表的第一个结点
        carry, curr = 0, dummy  # carry 为进位；curr 是结果链表的尾指针
        while l1 or l2 or carry:  # 任一链表还有结点或仍有进位时继续
            s = (l1.val if l1 else 0) + (l2.val if l2 else 0) + carry  # 本位和：缺失的位按 0 处理，再加上进位
            carry, val = divmod(s, 10)  # divmod 一次拿到商（进位）和余数（本位数字）
            curr.next = ListNode(val)  # 本位数字建成结点接到尾部
            curr = curr.next  # 尾指针后移
            l1 = l1.next if l1 else None  # l1 后移；已走完则保持 None
            l2 = l2.next if l2 else None  # l2 后移；已走完则保持 None
        return dummy.next  # 哑结点的后继就是结果的头结点
