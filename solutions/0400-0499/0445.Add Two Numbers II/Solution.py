# 题目：445. 两数相加 II（Add Two Numbers II）
# 思路：链表高位在前，先把两条链表的值分别压栈，再从低位到高位逐位相加；用头插法把每一位的结果挂到虚拟头结点之后，得到高位在前的和。
# 复杂度：时间复杂度 O(m + n)，两条链表各遍历一次；空间复杂度 O(m + n)，两个栈加上结果链表。
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # 题解类：两条链表表示的数相加（高位在前）
    def addTwoNumbers(  # l1、l2 是高位在前的数字链表，返回同样高位在前的和
        self, l1: Optional[ListNode], l2: Optional[ListNode]  # 参数列表续行：self 之后是两条链表
    ) -> Optional[ListNode]:  # 返回结果链表的头结点
        s1, s2 = [], []  # 用列表当栈，末尾即最低位
        while l1:  # 把 l1 的各位数字依次压栈
            s1.append(l1.val)  # 顺序入栈，末尾就是最低位
            l1 = l1.next  # 指针后移
        while l2:  # 同理把 l2 的各位压栈
            s2.append(l2.val)  # 入栈
            l2 = l2.next  # 指针后移
        dummy = ListNode()  # 虚拟头结点，用头插法按低位到高位收集结果
        carry = 0  # 进位，初始为 0
        while s1 or s2 or carry:  # 只要还有没加完的位或有进位就继续
            s = (0 if not s1 else s1.pop()) + (0 if not s2 else s2.pop()) + carry  # 本位和：两个栈顶相加（缺失按 0 计）再加上进位
            carry, val = divmod(s, 10)  # divmod 同时得到新的进位与本位数字
            # node = ListNode(val, dummy.next)  # 等价写法（分两步）：先建好新节点
            # dummy.next = node  # 第二步：把新节点挂到 dummy 之后，实现头插
            dummy.next = ListNode(val, dummy.next)  # 一行完成头插：本位数字插到已收集结果的最前面
        return dummy.next  # dummy 之后就是拼接好的结果链表
