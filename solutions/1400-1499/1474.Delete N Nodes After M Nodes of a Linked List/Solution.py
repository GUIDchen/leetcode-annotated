# 题目：1474. 删除链表 M 个节点之后的 N 个节点（Delete N Nodes After M Nodes of a Linked List）
# 思路：指针 pre 先走 m-1 步停在保留段的最后一个节点，再用 cur 从它出发跳 n 步，把保留段末尾接到被删段之后的节点上，如此循环。
# 时间复杂度：O(L)，L 为链表长度，每个节点最多被访问一次；空间复杂度：O(1)，只用常数个指针。
# Definition for singly-linked list.  # LeetCode 题面给出的单链表节点定义
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # LeetCode 约定的题解类
    def deleteNodes(self, head: ListNode, m: int, n: int) -> ListNode:  # head：链表头；m：每段保留个数；n：每段删除个数
        pre = head  # pre 指向当前保留段的最后一个节点，初始为头节点
        while pre:  # 只要还没走到链表末尾就继续处理下一段
            for _ in range(m - 1):  # 先走 m-1 步，让 pre 停在要保留的 m 个节点的最后一个上
                if pre:  # 只有当前节点非空时才能继续后移
                    pre = pre.next  # 向后移动一步
            if pre is None:  # 剩余节点不足 m 个，后面没有需要删除的节点
                return head  # 直接返回原头节点
            cur = pre  # cur 从保留段末尾出发，用来跳过待删的 n 个节点
            for _ in range(n):  # 最多跳 n 步，跳过 n 个待删节点
                if cur:  # 只有当前节点非空时才能继续后移
                    cur = cur.next  # 向后移动一步
            pre.next = None if cur is None else cur.next  # 把保留段末尾接到被删段之后的节点（没有则为空）
            pre = pre.next  # pre 移到下一段的起点，准备处理下一轮
        return head  # 全部处理完毕，返回链表头
