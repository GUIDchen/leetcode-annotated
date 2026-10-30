# 题目：86. 分隔链表（Partition List）
# 思路：建两条带头结点的临时链表，小于 x 的结点接到左链、其余接到右链，最后把右链拼到左链尾部。
# 时间复杂度：O(n)，原链表只遍历一次；空间复杂度：O(1)，只用了两个哑结点和几个指针。

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # LeetCode 约定的题解类
    def partition(self, head: Optional[ListNode], x: int) -> Optional[ListNode]:  # head：原链表头；x：分界值
        l = ListNode()  # 左链哑结点：存放所有 < x 的结点
        r = ListNode()  # 右链哑结点：存放所有 >= x 的结点
        tl, tr = l, r  # tl 是左链尾指针，tr 是右链尾指针，负责接新结点
        while head:  # 遍历原链表
            if head.val < x:  # 当前结点属于左链
                tl.next = head  # 挂到左链尾部
                tl = tl.next  # 左链尾指针前移
            else:  # 当前结点属于右链
                tr.next = head  # 挂到右链尾部
                tr = tr.next  # 右链尾指针前移
            head = head.next  # 原链表指针前进一位
        tr.next = None  # 右链尾部收口，防止尾部残留指针形成环
        tl.next = r.next  # 左链尾部接上右链的第一个真实结点
        return l.next  # 左链哑结点的下一个就是结果链表头
