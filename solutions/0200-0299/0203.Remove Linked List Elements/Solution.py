# 题目：203. 移除链表元素（Remove Linked List Elements）
# 思路：构造值为 -1 的哑节点指向原头节点，用 pre 指向「已确认保留」的最后一个节点，逐一跳过值等于 val 的节点。
# 时间复杂度：O(n)，每个节点最多检查一次；空间复杂度：O(1)，只用哑节点和一个指针。
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def removeElements(self, head: ListNode, val: int) -> ListNode:  # head：链表头节点；val：要删除的值；返回删除后的新头节点
        dummy = ListNode(-1, head)  # 哑节点指向原头节点，统一处理「删除头节点」与「删除中间节点」两种情况
        pre = dummy  # pre 始终指向已确认保留部分的最后一个节点
        while pre.next:  # 后面还有节点待检查
            if pre.next.val != val:  # 下一个节点要保留
                pre = pre.next  # pre 后移，把它并入已确认部分
            else:  # 下一个节点要删除
                pre.next = pre.next.next  # 让 pre 直接连到被删节点的后继，pre 不动以便继续跳过后续相同值的节点
        return dummy.next  # 哑节点的 next 就是新头节点（原头节点可能已被删除）
