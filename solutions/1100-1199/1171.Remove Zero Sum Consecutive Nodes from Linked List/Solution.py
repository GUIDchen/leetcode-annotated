# 题目：1171. 从链表中删去总和值为零的连续节点（Remove Zero Sum Consecutive Nodes from Linked List）
# 思路：两遍扫描。第一遍用哈希表记录每个前缀和最后一次出现的节点；第二遍重扫，把相同前缀和之间的节点段（和为零）整段跳过。
# 时间复杂度：O(n)，两次线性扫描加哈希查询；空间复杂度：O(n)，哈希表最多保存 n 个前缀和。
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # 题解类
    def removeZeroSumSublists(self, head: Optional[ListNode]) -> Optional[ListNode]:  # 删除链表中所有和为零的连续节点段，返回新的头节点
        dummy = ListNode(next=head)  # 哨兵节点，next 指向真实头节点，统一处理逻辑
        last = {}  # 哈希表：前缀和 → 最后一次出现该前缀和的节点
        s, cur = 0, dummy  # 前缀和 s，遍历指针 cur 从哨兵开始
        while cur:  # 第一遍：走到链表末尾
            s += cur.val  # 累加当前节点的值，得到当前位置的前缀和
            last[s] = cur  # 记录/覆盖该前缀和最后出现的节点
            cur = cur.next  # 指针后移
        s, cur = 0, dummy  # 第二遍：前缀和归零，指针重新回到哨兵
        while cur:  # 再次遍历链表
            s += cur.val  # 累加当前节点的值，得到前缀和
            cur.next = last[s].next  # 相同前缀和之间的节点段和为零，直接跳过
            cur = cur.next  # 移动到下一个待处理的节点
        return dummy.next  # 返回哨兵的下一个节点，即新的头节点
