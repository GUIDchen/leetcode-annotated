# 题目：234. 回文链表（Palindrome Linked List）
# 思路：快慢指针找到左半段末尾，把右半段原地反转，再让反转后的右半段与左半段逐值比较。
# 时间复杂度：O(n)，找中点、反转、比较各扫一遍；空间复杂度：O(1)，只用了几个指针。
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # LeetCode 约定的题解类
    def isPalindrome(self, head: Optional[ListNode]) -> bool:  # head 是链表头结点，返回整条链表是否是回文
        slow, fast = head, head.next  # 快慢指针初始化：fast 从第二个结点出发，让奇数长度时左半段更短、右半段更长，比较时刚好对齐
        while fast and fast.next:  # 快指针每次走两步，走到头时慢指针正好在中点
            slow, fast = slow.next, fast.next.next  # 慢指针走一步、快指针走两步
        pre, cur = None, slow.next  # pre 是反转后的头，cur 从 mid 的下一个结点开始
        while cur:  # 原地反转右半段
            t = cur.next  # 先记住后继，防止改指针后断链找不到
            cur.next = pre  # 当前结点反向指向 pre
            pre, cur = cur, t  # 两个指针一起前移
        while pre:  # 反转后的右半段从头开始，与左半段逐值比较
            if pre.val != head.val:  # 出现不同的值
                return False  # 不是回文，立即返回
            pre, head = pre.next, head.next  # 两个指针同步后移
        return True  # 全部相等，是回文链表
