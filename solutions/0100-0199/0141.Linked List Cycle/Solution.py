# 题目：141. 环形链表（Linked List Cycle）
# 思路：遍历时把访问过的节点对象存入集合，只要某个节点第二次出现，就说明链表有环。
# 时间复杂度：O(n)，每个节点最多访问一次；空间复杂度：O(n)，集合最多保存 n 个节点。
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None


class Solution:  # LeetCode 约定的题解类
    def hasCycle(self, head: Optional[ListNode]) -> bool:  # head：链表头节点；返回链表中是否存在环
        s = set()  # 集合保存已经访问过的节点对象，靠哈希区分身份
        while head:  # 指针为空说明到表尾，退出循环
            if head in s:  # 这个节点之前已经走过
                return True  # 指针绕回来了，存在环
            s.add(head)  # 首次访问的节点加入集合
            head = head.next  # 指针沿 next 后移
        return False  # 走完仍未重复，说明无环
