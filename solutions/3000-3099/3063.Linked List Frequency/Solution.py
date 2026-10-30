# 题目：3063. 链表频率（Linked List Frequency）
# 思路：用 Counter 统计每个值出现的次数，再用头插法把各次数串成一条新链表返回。
# 时间复杂度：O(n)，两次线性遍历；空间复杂度：O(n)，计数器与新链表各占 O(n)。
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # LeetCode 约定的题解类
    def frequenciesOfElements(self, head: Optional[ListNode]) -> Optional[ListNode]:  # head 是原链表头，返回只含各值出现次数的新链表
        cnt = Counter()  # Counter 计数器：键是链表中的值，值是出现次数
        while head:  # 顺序遍历原链表，直到为空
            cnt[head.val] += 1  # 当前值计数加一
            head = head.next  # 指针后移
        dummy = ListNode()  # 哑节点，其 next 作为结果链表的入口，省去空指针判断
        for val in cnt.values():  # 只关心出现次数，遍历计数器的所有值
            dummy.next = ListNode(val, dummy.next)  # 头插法把次数做成新节点，接到结果链表最前面
        return dummy.next  # 返回哑节点的下一个节点，即结果链表头
