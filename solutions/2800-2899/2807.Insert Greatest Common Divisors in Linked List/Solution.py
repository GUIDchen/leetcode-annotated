# 题目：2807. 在链表中插入最大公约数（Insert Greatest Common Divisors in Linked List）
# 思路：双指针一次遍历，用相邻两个节点值的最大公约数新建节点，插到 pre 与 cur 之间。
# 时间复杂度：O(n log V)，n 为节点数、V 为节点值，每次求 gcd 为对数级；空间复杂度：O(1) 额外指针（新节点属于答案所需）。
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # LeetCode 约定的题解类
    def insertGreatestCommonDivisors(
        self, head: Optional[ListNode]
    ) -> Optional[ListNode]:  # 方法签名分三行书写，避免过长；返回插入完成后的链表头节点
        pre, cur = head, head.next  # pre：前一个节点；cur：当前节点，从第二个节点开始
        while cur:  # 当前节点还存在，就继续向后处理
            x = gcd(pre.val, cur.val)  # x：相邻两个节点值的最大公约数（math.gcd）
            pre.next = ListNode(x, cur)  # 新建值为 x 的节点，插在 pre 与 cur 之间
            pre, cur = cur, cur.next  # 两个指针同时后移：pre 移到 cur，cur 移到下一个节点
        return head  # 头节点没有变化，直接返回 head
