# 题目：876. 链表的中间结点（Middle of the Linked List）
# 核心思路：快慢指针，快指针每次走两步、慢指针每次走一步，快指针到尾时慢指针正好在中间结点上。
# 时间复杂度：O(n)，只遍历一次链表；空间复杂度：O(1)，只用了两个指针。
# 下面 5 行是 LeetCode 题面给出的单链表定义（以注释形式给出），不是可执行代码
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # LeetCode 约定的题解类
    def middleNode(self, head: ListNode) -> ListNode:  # head：链表头节点；返回中间结点（偶数个结点时返回后一个）
        slow = fast = head  # 慢、快两个指针同时从头节点出发
        while fast and fast.next:  # 快指针还能走两步时继续，避免对 None 取 .next 报错
            slow, fast = slow.next, fast.next.next  # 先同时算出两个新位置再赋值，慢指针走一步、快指针走两步
        return slow  # 返回中间结点
