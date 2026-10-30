# 题目：369. 给单链表加一（Plus One Linked List）
# 思路：加哑结点后一趟扫描找到「最右侧不等于 9 的结点」作为加一位置，该位置加一、其后的 9 全部置 0；哑结点被加一则说明最高位进位，返回 dummy。
# 时间复杂度：O(n)，两趟线性扫描；空间复杂度：O(1)，只用几个指针。
# 下列注释是 LeetCode 题面自带的单链表结点定义，原样保留
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # LeetCode 约定的题解类
    def plusOne(self, head: Optional[ListNode]) -> Optional[ListNode]:  # head 是非空单链表，按高位到低位表示一个非负整数
        dummy = ListNode(0, head)  # 哑结点值为 0，用来统一处理整条链全是 9 的进位情况
        target = dummy  # target 指向稍后要加一的位置，先指向哑结点
        while head:  # 用 head 当游标遍历整条链
            if head.val != 9:  # 值不是 9，加一后不会向它产生进位
                target = head  # 记住最右侧的这个非 9 结点
            head = head.next  # 游标后移
        target.val += 1  # 找到位置后把它加一
        target = target.next  # 从 target 的下一个结点开始处理
        while target:  # 它后面原来的 9 都要变成 0
            target.val = 0  # 原地清零
            target = target.next  # 游标后移
        return dummy if dummy.val else dummy.next  # 哑结点被加一说明最高位进位、长度加一，否则跳过哑结点
