# 题目：2674. 拆分循环链表（Split a Circular Linked List）
# 思路：快慢指针找中点：慢指针停在第一段末尾，快指针停在第二段末尾；再把两个 next 接回各自头，得到两个循环链表。
# 时间复杂度：O(n)，只遍历一遍链表；空间复杂度：O(1)，只用两个指针和常数个中间变量。
# 以下 ListNode 定义由 LeetCode 判题器提供，原样保留，不属于题解代码
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # 快慢指针拆分循环链表
    def splitCircularLinkedList(  # list 是循环链表的任意入口结点，返回两个新循环链表的头结点
        self, list: Optional[ListNode]  # self 是方法自身，list 是要拆分的循环链表入口
    ) -> List[Optional[ListNode]]:  # 返回长度为 2 的列表：两个元素分别是两段链表的头结点
        a = b = list  # a 是慢指针（一步一停），b 是快指针（一步两跳）
        while b.next != list and b.next.next != list:  # 快指针再走两步就会回到起点时停下，避免绕完整圈
            a = a.next  # 慢指针走一步
            b = b.next.next  # 快指针走两步
        if b.next != list:  # 结点个数为偶数时快指针还差一步才到第二段末尾
            b = b.next  # 把快指针补到第二段末尾
        list2 = a.next  # 第二段的头结点就是第一段末尾的下一个结点
        b.next = list2  # 让第二段首尾相接，得到第二个循环链表
        a.next = list  # 让第一段首尾相接，得到第一个循环链表
        return [list, list2]  # 返回两个循环链表的头结点
