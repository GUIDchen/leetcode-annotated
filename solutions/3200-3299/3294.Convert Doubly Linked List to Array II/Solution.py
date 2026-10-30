# 题目：3294. 将双链表转换为数组 II（Convert Doubly Linked List to Array II）
# 思路：先用 prev 指针从给定节点回溯到表头，再沿 next 指针正向遍历收集节点值。
# 时间复杂度：O(n)，两次线性遍历；空间复杂度：O(n)，结果数组保存 n 个元素。
"""
# Definition for a Node.
class Node:
    def __init__(self, val, prev=None, next=None):
        self.val = val
        self.prev = prev
        self.next = next
"""


class Solution:  # LeetCode 约定的题解类
    def toArray(self, node: "Optional[Node]") -> List[int]:  # node 是双向链表中的任意节点，返回从表头开始的整条链表的值
        while node.prev:  # 只要还有前驱节点，就说明当前不是表头
            node = node.prev  # 一路向前回溯到表头
        ans = []  # ans 存放结果数组
        while node:  # 从表头开始沿 next 遍历，直到 None
            ans.append(node.val)  # 收集当前节点的值
            node = node.next  # 移动到下一个节点
        return ans  # 返回按链表顺序排列的数组
