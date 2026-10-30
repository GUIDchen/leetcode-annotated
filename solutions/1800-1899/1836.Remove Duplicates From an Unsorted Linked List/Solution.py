# 题目：1836. 从未排序的链表中移除重复元素（Remove Duplicates From an Unsorted Linked List）
# 思路：先用 Counter 统计每个值出现次数，再用哑结点加前驱指针第二遍扫描，删除计数大于 1 的结点。
# 时间复杂度：O(n)，两次线性扫描；空间复杂度：O(n)，计数器存放不同取值的出现次数。
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # LeetCode 约定的题解类
    def deleteDuplicatesUnsorted(self, head: ListNode) -> ListNode:  # head 为链表头结点，返回删除全部重复值结点后的新头结点
        cnt = Counter()  # 计数器：记录每个结点值出现的次数（Counter 来自 collections）
        cur = head  # 从头结点开始第一遍遍历
        while cur:  # 一直遍历到链表末尾
            cnt[cur.val] += 1  # 当前结点值的计数加一
            cur = cur.next  # 游标后移
        dummy = ListNode(0, head)  # 哑结点指向原头结点，便于处理“头结点被删除”的情况
        pre, cur = dummy, head  # pre 是 cur 的前驱，用于原地摘除结点
        while cur:  # 第二遍遍历：逐个检查结点是否为重复值
            if cnt[cur.val] > 1:  # 出现次数大于 1，说明该值重复，当前结点必须删除
                pre.next = cur.next  # 让前驱跳过 cur，把 cur 摘出链表；pre 不动
            else:  # 否则该值唯一，保留当前结点
                pre = cur  # 前驱前移到当前结点
            cur = cur.next  # 游标后移，继续检查下一个结点
        return dummy.next  # 哑结点的后继即新的头结点
