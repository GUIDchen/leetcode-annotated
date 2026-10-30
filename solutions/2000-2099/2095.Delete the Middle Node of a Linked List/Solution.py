# 题目：2095. 删除链表的中间节点（Delete the Middle Node of a Linked List）
# 思路：在 head 前加哑节点，快慢指针同向走；快指针到尾时慢指针正好停在待删节点的前一个，直接跳过它。
# 时间复杂度：O(n)，快指针只扫一遍；空间复杂度：O(1)，只用了 dummy、slow、fast 三个指针。
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # LeetCode 约定的题解类
    def deleteMiddle(self, head: Optional[ListNode]) -> Optional[ListNode]:  # head：链表头节点；返回删除中间节点后的新头节点
        dummy = ListNode(next=head)  # 哑节点指向 head，这样删掉头节点时也能统一处理
        slow, fast = dummy, head  # 慢指针从哑节点出发，快指针从真正的头节点出发
        while fast and fast.next:  # 快指针还能走两步时继续前进
            slow = slow.next  # 慢指针走一步
            fast = fast.next.next  # 快指针走两步
        slow.next = slow.next.next  # slow 停在中间节点的前一个，跳过中间节点即完成删除
        return dummy.next  # 返回（可能已换过头节点后的）新链表头
