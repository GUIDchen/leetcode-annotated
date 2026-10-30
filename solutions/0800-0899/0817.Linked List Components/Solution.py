# 题目：817. 链表组件（Linked List Components）
# 思路：先把 nums 转成集合，再顺链表扫描：跳过一段不在集合里的节点后，若紧接着还有属于集合的节点，就计为一个组件，如此反复。
# 时间复杂度：O(n + m)，n 为链表长度、m 为 nums 长度；空间复杂度：O(m)，集合最多存 m 个值。
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # LeetCode 约定的题解类
    def numComponents(self, head: Optional[ListNode], nums: List[int]) -> int:  # head：链表头；nums：能组成组件的取值集合
        ans = 0  # ans：组件个数
        s = set(nums)  # 用 nums 建哈希集合，做到 O(1) 成员判断
        while head:  # 外层循环：链表未走完就继续寻找下一段组件
            while head and head.val not in s:  # 先跳过所有不在集合里的节点
                head = head.next  # 指针后移一位
            ans += head is not None  # 停在集合内的节点上说明新组件从这里开始，计数加一
            while head and head.val in s:  # 再把这段连续属于集合的节点整体跳过
                head = head.next  # 指针后移一位
        return ans  # 返回组件总数
