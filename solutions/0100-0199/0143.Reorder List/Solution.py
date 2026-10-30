# 题目：143. 重排链表（Reorder List）
# 思路：快慢指针找中点并断开，反转后半段，再把两段交替合并，原地完成重排。
# 时间复杂度：O(n)，找中点、反转、合并各一趟；空间复杂度：O(1)，只用了若干指针变量。
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # LeetCode 约定的题解类
    def reorderList(self, head: Optional[ListNode]) -> None:  # head：链表头；原地重排所以返回 None
        fast = slow = head  # 快慢指针同时从头部出发
        while fast.next and fast.next.next:  # 快指针还能跳两格就继续，slow 最终指向前半段末尾
            slow = slow.next  # 慢指针走一步
            fast = fast.next.next  # 快指针走两步

        cur = slow.next  # cur 指向后半段的第一个节点
        slow.next = None  # 断开前后两段，反转时不会串到前半段

        pre = None  # pre 是反转后链表的头，初始为空
        while cur:  # 逐个反转后半段的节点
            t = cur.next  # 暂存后继节点，防止断链
            cur.next = pre  # 当前节点反向指向前一个节点
            pre, cur = cur, t  # 元组赋值：pre 前进到当前节点，cur 前进到后继
        cur = head  # cur 回到链表头，准备合并两段

        while pre:  # 后半段还有节点就继续交替插入
            t = pre.next  # 暂存后半段的下一个节点
            pre.next = cur.next  # pre 先接上 cur 原本的后继，保证不断链
            cur.next = pre  # cur 后面接上 pre，完成一次插入
            cur, pre = pre.next, t  # 元组赋值：cur 前进一步，pre 推进到后半段下一个节点
