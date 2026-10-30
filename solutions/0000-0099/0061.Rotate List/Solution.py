# 题目：61. 旋转链表（Rotate List）
# 思路：先统计链长 n 并把 k 对 n 取模；再用快慢指针（间距 k）找到倒数第 k 个结点的前一位，断开后把后段接到头部之前。
# 时间复杂度：O(n)，遍历链表两次；空间复杂度：O(1)，只用了常数个指针。
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # LeetCode 约定的题解类
    def rotateRight(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:  # head：链头；k：向右旋转的步数
        if head is None or head.next is None:  # 空链表或只有一个结点，旋转前后完全相同
            return head  # 直接返回原链表
        cur, n = head, 0  # cur 用来遍历，n 记录链长
        while cur:  # 走完整条链表
            n += 1  # 每过一个结点长度加一
            cur = cur.next  # 指针后移
        k %= n  # 旋转 n 次会回到原样，所以真正需要转的步数是 k % n
        if k == 0:  # 取模为 0 表示不需要旋转
            return head  # 原样返回
        fast = slow = head  # 快慢指针都从头出发，快指针先走 k 步，两者便相距 k 个结点
        for _ in range(k):  # 快指针先前进 k 步
            fast = fast.next  # 前进一个结点
        while fast.next:  # 快指针走到尾结点时停下
            fast, slow = fast.next, slow.next  # 快慢指针一起前移，保持间距 k；slow 最终停在断点前一位

        ans = slow.next  # 断点后的第一个结点将成为新的头结点
        slow.next = None  # 在此处断开，原前半段变成尾段
        fast.next = head  # 把原前半段接到尾结点之后，完成旋转
        return ans  # 返回新的头结点
