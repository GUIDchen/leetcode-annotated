# 题目：147. 对链表进行插入排序（Insertion Sort List）
# 思路：带哑节点的插入排序——前面保持已排序段，每次把当前节点摘下，从哑节点后找到第一个比它大的位置插入。
# 时间复杂度：O(n^2)，最坏每个节点都要从头扫描有序段；空间复杂度：O(1)，只用若干指针变量。
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # 题目要求的题解类
    def insertionSortList(self, head: ListNode) -> ListNode:  # 对链表做插入排序，返回排序后的头节点
        if head is None or head.next is None:  # 空链表或只有一个节点：天然有序
            return head  # 直接返回，无需排序
        dummy = ListNode(head.val, head)  # 哑节点以首节点值初始化并挂在原链表之前，省去“插到头部”的特判
        pre, cur = dummy, head  # pre 是 cur 的前驱，cur 是当前待插入的节点
        while cur:  # 逐个把节点插入前面已排好序的部分
            if pre.val <= cur.val:  # 前驱不大于当前值，说明它已经在该在的位置
                pre, cur = cur, cur.next  # 两个指针一起后移
                continue  # 无需搬动，直接处理下一个节点
            p = dummy  # 否则从有序段头部开始找插入位置
            while p.next.val <= cur.val:  # 一直走到 p.next 比 cur 大为止，此时 p 就是插入点前驱
                p = p.next  # 继续往后找
            t = cur.next  # 先保存 cur 的后继，摘下 cur 后还要把它接回去
            cur.next = p.next  # cur 指向插入位置原来的节点
            p.next = cur  # 前驱 p 指向 cur，完成插入有序段
            pre.next = t  # 原位置的前驱跳过 cur，链表重新连上
            cur = t  # 接着处理原来的下一个节点
        return dummy.next  # 哑节点的下一个就是排序后的真实头节点
