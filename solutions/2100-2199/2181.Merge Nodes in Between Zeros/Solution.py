# 题目：2181. 合并零之间的节点（Merge Nodes in Between Zeros）
# 思路：从第二个节点开始遍历，累加非零值；遇到 0 就把累加和接成新节点挂到结果链表尾部，最后返回哨兵的后继。
# 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(1)，额外只用了哨兵与尾指针（新节点即返回结果）。
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # LeetCode 约定的题解类
    def mergeNodes(self, head: Optional[ListNode]) -> Optional[ListNode]:  # head：原链表头（其值为 0）；返回合并后的链表头
        dummy = tail = ListNode()  # 哨兵节点同时作为结果链表初始尾指针，dummy.next 指向结果第一个节点
        s = 0  # 累加器：当前段（两个 0 之间）的节点值之和
        cur = head.next  # 跳过开头那个 0，从首段内部开始遍历
        while cur:  # 遍历到链表末尾时结束
            if cur.val:  # 当前值非零，属于某一段内部
                s += cur.val  # 累加进当前段的和
            else:  # 当前值为 0，说明前面一段结束
                tail.next = ListNode(s)  # 用该段的和新建节点并接到结果链表尾部
                tail = tail.next  # 尾指针后移到新节点
                s = 0  # 清零累加器，准备统计下一段
            cur = cur.next  # 指针后移，处理下一个节点
        return dummy.next  # 返回哨兵后面的结果链表
