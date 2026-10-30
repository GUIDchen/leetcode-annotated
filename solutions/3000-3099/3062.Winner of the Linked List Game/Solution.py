# 题目：3062. 链表游戏的获胜者（Winner of the Linked List Game）
# 思路：链表每两个节点为一组，比较组内两个值的大小累计双方得分，最后按总分判定胜者。
# 时间复杂度：O(n)，只遍历一遍链表；空间复杂度：O(1)，仅用两个计数变量。
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # LeetCode 约定的题解类
    def gameResult(self, head: Optional[ListNode]) -> str:  # head 是链表头节点，返回胜者名字："Odd"、"Even" 或 "Tie"
        odd = even = 0  # odd 与 even 分别记录奇数下标、偶数下标节点赢下的组数
        while head:  # 只要当前节点非空就继续处理一组
            a = head.val  # 组内前一个节点（偶数下标）的值
            b = head.next.val  # 组内后一个节点（奇数下标）的值
            odd += a < b  # 前一个更小则奇数下标赢一局：布尔值参与加法会自动变成 0/1
            even += a > b  # 前一个更大则偶数下标赢一局；相等时双方都不加分
            head = head.next.next  # 跨过这两个节点，移动到下一组的首节点
        if odd > even:  # 奇数下标总分更高，奇数方获胜
            return "Odd"  # 返回奇数方获胜
        if odd < even:  # 奇数不占优，继续判断偶数方
            return "Even"  # 偶数下标总分更高，偶数方获胜
        return "Tie"  # 两边都不占优即为平局
