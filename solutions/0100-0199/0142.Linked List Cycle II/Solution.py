# 题目：142. 环形链表 II（Linked List Cycle II）
# 思路：快慢指针判环，相遇后把一个指针放回头部，两者同速前进，再次相遇处就是环的入口。
# 时间复杂度：O(n)，每个节点访问常数次；空间复杂度：O(1)，只用两个指针。
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None


class Solution:  # LeetCode 约定的题解类
    def detectCycle(self, head: Optional[ListNode]) -> Optional[ListNode]:  # head：链表头；返回入环节点，无环时函数隐式返回 None
        fast = slow = head  # 快慢指针同时从头部出发
        while fast and fast.next:  # 快指针还能走满两步，才有追上的可能
            slow = slow.next  # 慢指针走一步
            fast = fast.next.next  # 快指针走两步
            if slow == fast:  # 两指针相遇即证明有环
                ans = head  # ans 回到头部，准备定位入口
                while ans != slow:  # 两指针同速前进，直到相遇
                    ans = ans.next  # ans 前进一步
                    slow = slow.next  # slow 前进一步
                return ans  # 相遇点就是环的入口，直接返回（无环时不进入这里）
