# 题目：82. 删除排序链表中的重复元素 II（Remove Duplicates from Sorted List II）
# 思路：哑结点 + 双指针，先让 cur 走完当前重复段，再用 pre.next == cur 判断该段是「唯一」还是「重复」，重复就把整段摘除。
# 时间复杂度：O(n)，每个结点最多被访问两次；空间复杂度：O(1)，只用了常数个指针（哑结点计为常数）。

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # LeetCode 约定的题解类
    def deleteDuplicates(self, head: Optional[ListNode]) -> Optional[ListNode]:  # head：升序链表头结点
        dummy = pre = ListNode(next=head)  # dummy 是哑结点；pre 指向最后一个确定保留的结点（初始为哑结点）
        cur = head  # cur 向右探测，最终停在当前重复段的最后一个结点
        while cur:  # 外层循环：一段一段地处理整条链表
            while cur.next and cur.next.val == cur.val:  # 后一个值相同就一路右移，走完整段重复值
                cur = cur.next  # 跳到下一个重复值
            if pre.next == cur:  # pre 的下一个仍是 cur，说明这一段只有 cur 自己
                pre = cur  # 该值唯一，保留下来，pre 前移到 cur
            else:  # 否则 cur 这一段出现了至少两次
                pre.next = cur.next  # 把整段重复值从链表上摘掉，pre 保持不动
            cur = cur.next  # cur 移到下一段的起点
        return dummy.next  # 哑结点的下一个就是结果链表真正的头
