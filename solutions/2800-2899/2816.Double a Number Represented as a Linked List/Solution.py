# 题目：2816. 翻倍以链表形式表示的数字（Double a Number Represented as a Linked List）
# 思路：链表高位在前，先反转成低位在前，从个位开始逐位乘 2 并传递进位，结果用尾插法建立，最后再反转回高位在前。
# 时间复杂度：O(n)，共三次线性遍历；空间复杂度：O(n)，结果链表需要 n 到 n+1 个新节点。
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next  # 以上是判题器提供的单链表节点定义
class Solution:  # LeetCode 约定的题解类
    def doubleIt(self, head: Optional[ListNode]) -> Optional[ListNode]:  # head：高位在前的数字链表；返回翻倍后的链表头
        def reverse(head):  # 内部辅助函数：用头插法就地反转链表
            dummy = ListNode()  # 虚拟头结点，统一处理插到头部的情况
            cur = head  # 从原链表头开始遍历
            while cur:  # 逐个摘下节点
                next = cur.next  # 先存下后继节点，改指针后就找不回来了
                cur.next = dummy.next  # 头插：把当前节点接到虚拟头结点之后
                dummy.next = cur  # 虚拟头结点指向新的链表头
                cur = next  # 继续处理原来的下一个节点
            return dummy.next  # 虚拟头结点的后继就是反转后的新头

        head = reverse(head)  # 先反转成低位在前，从个位开始乘 2
        dummy = cur = ListNode()  # 结果链表的虚拟头结点，同时用 cur 记录尾指针
        mul, carry = 2, 0  # mul 为乘数（翻倍是 2），carry 为进位
        while head:  # 遍历每一位（从个位到最高位）
            x = head.val * mul + carry  # 当前位结果 = 数字位 × 2 + 进位
            carry = x // 10  # 整除 10 得到向高位的进位
            cur.next = ListNode(x % 10)  # 当前位保留个位数字，尾插到结果链表
            cur = cur.next  # 尾指针后移
            head = head.next  # 处理下一位
        if carry:  # 最高位还有进位就再补一个节点（如 99 × 2 = 198）
            cur.next = ListNode(carry)  # 补上最高位的进位
        return reverse(dummy.next)  # 结果低位在前，再反转一次恢复成高位在前
