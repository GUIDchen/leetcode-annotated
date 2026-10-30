# 题目：19. 删除链表的倒数第 N 个结点（Remove Nth Node From End of List）
# 思路：加哑结点后，快指针先走 n 步，再与慢指针同步前进；快指针到尾时慢指针正好停在待删结点的前驱。
# 时间复杂度：O(L)，L 为链表长度，只遍历一遍；空间复杂度：O(1)，只用了几个指针。
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # LeetCode 约定的题解类
    def removeNthFromEnd(self, head: Optional[ListNode], n: int) -> Optional[ListNode]:  # head：链表头；n：要删除的倒数第 n 个结点
        dummy = ListNode(next=head)  # 哑结点指向 head，删除头结点时也有前驱可用
        fast = slow = dummy  # 快慢指针都从哑结点出发
        for _ in range(n):  # 快指针先走 n 步，与慢指针拉开 n 个位置
            fast = fast.next  # 快指针前进一步
        while fast.next:  # 快指针还没到尾结点时继续同步前进
            slow, fast = slow.next, fast.next  # 两个指针各前进一步，间距始终保持 n
        slow.next = slow.next.next  # 此时 slow 是待删结点的前驱，跳过它就是删除
        return dummy.next  # 返回可能已被更新的真正头结点
