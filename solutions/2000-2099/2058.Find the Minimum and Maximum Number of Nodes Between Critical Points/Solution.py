# 题目：2058. 找出临界点之间的最小和最大距离（Find the Minimum and Maximum Number of Nodes Between Critical Points）
# 思路：一次遍历链表，用下标 i 标记当前中间节点；遇到波峰/波谷就更新第一个临界点位置以及最小、最大间距。
# 时间复杂度：O(n)，链表只走一遍；空间复杂度：O(1)，只用了常数个变量。
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # LeetCode 约定的题解类
    def nodesBetweenCriticalPoints(self, head: Optional[ListNode]) -> List[int]:  # head：链表头结点；返回 [最小距离, 最大距离]
        ans = [inf, -inf]  # ans[0] 存最小间距（先置正无穷），ans[1] 存最大间距（先置负无穷）
        first = last = -1  # 第一个、上一个临界点的下标；-1 表示还没遇到过临界点
        i = 0  # 当前中间节点的下标
        while head.next.next:  # 后面还剩两个节点时，head 才能充当「中间节点」
            a, b, c = head.val, head.next.val, head.next.next.val  # a、b、c 是相邻三个节点的值
            if a > b < c or a < b > c:  # 链式比较：b 是波谷或波峰，即为临界点
                if last == -1:  # 这是遇到的第一个临界点
                    first = last = i  # 同时记录第一个和「上一个」临界点的下标
                else:  # 之后遇到的临界点
                    ans[0] = min(ans[0], i - last)  # 与上一个临界点的距离用来更新最小间距
                    last = i  # 当前点成为新的「上一个」临界点
                    ans[1] = max(ans[1], last - first)  # 当前点到第一个临界点的距离即新的最大间距
            i += 1  # 中间节点右移一位，下标随之加一
            head = head.next  # 指针后移一个节点，进入下一组三元组
        return [-1, -1] if first == last else ans  # 临界点不足两个时按题意返回 [-1,-1]
