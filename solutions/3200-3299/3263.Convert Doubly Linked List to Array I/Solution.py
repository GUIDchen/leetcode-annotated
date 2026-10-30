# 题目：3263. 将双链表转换为数组 I（Convert Doubly Linked List to Array I）🔒
# 思路：从双向链表的头结点出发，沿 next 指针顺序遍历，把每个结点的值依次追加进数组即可（prev 指针在这道题里无需用到）。
# 时间复杂度：O(n)，每个结点只访问一次；空间复杂度：O(n)，结果数组存放 n 个值（不计输出为 O(1)）。
"""
# Definition for a Node.
class Node:
    def __init__(self, val, prev=None, next=None):
        self.val = val
        self.prev = prev
        self.next = next
"""


class Solution:  # LeetCode 约定的题解类
    def toArray(self, root: "Optional[Node]") -> List[int]:  # root 为双向链表头结点；返回从它开始的正序数组
        ans = []  # ans 依次收集链表各结点的值
        while root:  # 只要当前结点非空就继续遍历
            ans.append(root.val)  # 把当前结点的值追加到结果数组
            root = root.next  # 沿 next 指针走到下一个结点
        return ans  # 返回转换得到的数组
