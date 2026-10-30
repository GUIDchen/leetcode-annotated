# 题目：83. 删除排序链表中的重复元素（Remove Duplicates from Sorted List）
# 思路：单指针扫描，发现 cur 与 cur.next 值相同就让 cur.next 跨过重复结点；否则 cur 前移，每个值保留第一次出现。
# 时间复杂度：O(n)，每个结点只被走一次；空间复杂度：O(1)，只用一个指针。

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # LeetCode 约定的题解类
    def deleteDuplicates(self, head: Optional[ListNode]) -> Optional[ListNode]:  # head：升序链表头结点
        cur = head  # 从链表头开始扫描
        while cur and cur.next:  # 当前结点和后继结点都存在时，才能比较两者的值
            if cur.val == cur.next.val:  # 相邻两个结点值相同
                cur.next = cur.next.next  # 跨过重复的后继结点；cur 不动，继续和新的后继比较
            else:  # 值不同，说明 cur 这个值已经只剩唯一一个
                cur = cur.next  # cur 安全地前进一位
        return head  # 头结点总是被保留的，直接返回原 head
