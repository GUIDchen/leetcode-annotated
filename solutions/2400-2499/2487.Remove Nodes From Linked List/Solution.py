# 题目：2487. 从链表中移除节点（Remove Nodes From Linked List）
# 思路：保留的结点序列必然单调不增；用单调栈从左往右淘汰「右侧存在更大值」的结点，再按栈内顺序重建链表。
# 时间复杂度：O(n)，每个结点最多入栈出栈一次；空间复杂度：O(n)，数组与栈各存 n 个值。
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # LeetCode 约定的题解类
    def removeNodes(self, head: Optional[ListNode]) -> Optional[ListNode]:  # head：链表头结点；返回删除所有「右侧存在更大值」的结点之后的新头结点
        nums = []  # 先按原顺序把所有结点值收集到列表，方便用下标做单调栈
        while head:  # 遍历链表直到空
            nums.append(head.val)  # 记录当前结点的值
            head = head.next  # 移动到下一个结点
        stk = []  # 单调栈：从底到顶单调不增，栈里的值就是最终保留的结点
        for v in nums:  # 从左到右扫描每个值
            while stk and stk[-1] < v:  # 栈顶比 v 小，说明它右侧存在更大的 v，应当被删除
                stk.pop()  # 弹出被删除的结点值
            stk.append(v)  # v 暂时保留，等待右侧更大的值来淘汰它
        dummy = ListNode()  # 哑结点，简化尾插时对空链表的判断
        head = dummy  # head 复用为尾指针，指向当前链表末尾
        for v in stk:  # 按栈内顺序（即答案顺序）重建链表
            head.next = ListNode(v)  # 新建结点挂到尾部
            head = head.next  # 尾指针后移
        return dummy.next  # 跳过哑结点，返回真正的头结点
