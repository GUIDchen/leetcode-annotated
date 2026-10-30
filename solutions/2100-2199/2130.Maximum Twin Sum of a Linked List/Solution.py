# 题目：2130. 链表最大孪生和（Maximum Twin Sum of a Linked List）
# 核心思路：链表值按顺序转成列表，再用下标 i 与 -(i+1) 配对（孪生对），取最大和。
# 时间复杂度：O(n)，遍历链表一遍；空间复杂度：O(n)，列表保存所有节点值。
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # LeetCode 约定的题解类
    def pairSum(self, head: Optional[ListNode]) -> int:  # head 是链表头节点；返回所有孪生和中的最大值
        s = []  # 用列表按顺序保存链表所有节点的值
        while head:  # 遍历链表直到末尾（空节点视为假）
            s.append(head.val)  # 把当前节点的值追加进列表
            head = head.next  # 移动到下一个节点
        n = len(s)  # 节点总数，题目保证为偶数
        return max(s[i] + s[-(i + 1)] for i in range(n >> 1))  # 只枚举前半段：第 i 个与倒数第 i+1 个配对，取所有孪生和的最大值
