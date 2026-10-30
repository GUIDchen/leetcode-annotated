# 题目：2046. 给按照绝对值排序的链表排序（Sort Linked List Already Sorted Using Absolute Values）
# 思路：链表按绝对值升序，负数都在前半段且逆序；顺序扫描，遇到负节点就从原位置摘下并头插到链表头部，结束后链表即为升序。
# 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(1)，只用了常数个指针。
# 下面是题目给定的单链表节点定义（原题面注释，保持原样）
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # LeetCode 约定的题解类
    def sortLinkedList(self, head: Optional[ListNode]) -> Optional[ListNode]:  # head 是已按绝对值升序的链表头，返回按值升序的链表头
        prev, curr = head, head.next  # prev 是 curr 的前驱，curr 从第二个节点开始扫描
        while curr:  # 一直遍历到链表末尾
            if curr.val < 0:  # 负数的绝对值最小，应该排在最前面，需要移到头部
                t = curr.next  # 先保存后继节点，摘下 curr 后从这里继续
                prev.next = t  # 前驱跳过 curr，完成摘除
                curr.next = head  # 把 curr 接到链表最前面
                head = curr  # 头指针指向 curr
                curr = t  # 继续处理原来的后继
            else:  # 非负数位置已经正确，保持不动
                prev, curr = curr, curr.next  # 两个指针一起后移
        return head  # 返回排好序的链表头
