# 题目：1290. 二进制链表转整数（Convert Binary Number in a Linked List to Integer）
# 核心思路：遍历链表，每读一位先把结果左移一位，再把该位或进去，等价于按二进制位从高位到低位累积。
# 时间复杂度：O(n)，遍历链表一趟；空间复杂度：O(1)，只用到常数个变量。
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
# 上面是判题器提供的单链表结点定义；本题的链表头结点即二进制最高位
class Solution:  # LeetCode 约定的题解类
    def getDecimalValue(self, head: ListNode) -> int:  # head 是二进制链表头结点，返回它表示的十进制整数
        ans = 0  # ans 存放累加结果，初值为 0
        while head:  # 链表不为空就继续读下一位
            ans = ans << 1 | head.val  # 结果左移一位腾出最低位，再把当前结点的 0/1 或进去
            head = head.next  # 指针后移，处理下一位
        return ans  # 返回算出的十进制值
