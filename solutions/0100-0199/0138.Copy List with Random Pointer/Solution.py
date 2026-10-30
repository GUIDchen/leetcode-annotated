# 题目：138. 随机链表的复制（Copy List with Random Pointer）
# 思路：用字典记录「原节点 → 新节点」，先顺着 next 复制出整条新链，再按映射补齐每个节点的 random 指针。
# 时间复杂度：O(n)，两趟遍历；空间复杂度：O(n)，字典与新建的链表各占 O(n)。
"""
# Definition for a Node.
class Node:
    def __init__(self, x: int, next: 'Node' = None, random: 'Node' = None):
        self.val = int(x)
        self.next = next
        self.random = random
"""  # 以上是 LeetCode 题面给出的 Node 定义（三引号字符串，仅作文档说明）


class Solution:  # LeetCode 约定的题解类
    def copyRandomList(self, head: "Optional[Node]") -> "Optional[Node]":  # head：原链表头节点；返回深拷贝出的新链表头节点
        d = {}  # 字典：键是原节点对象，值是对应的新节点对象
        dummy = tail = Node(0)  # 哨兵节点：dummy 固定不动，tail 负责往后追加，省去首节点特判
        cur = head  # 遍历指针从原链表头开始
        while cur:  # 第一趟：逐个复制节点，先把 next 方向的新链搭好
            node = Node(cur.val)  # 由原节点的值造出新节点，random 先留空
            tail.next = node  # 把新节点挂到新链尾部
            tail = tail.next  # 尾指针后移一位
            d[cur] = node  # 记下映射关系，第二趟查 random 时要用
            cur = cur.next  # 原链表指针后移
        cur = head  # 指针重置回原链表头部，开始第二趟
        while cur:  # 第二趟：复制 random 指针
            d[cur].random = d[cur.random] if cur.random else None  # 原节点 random 非空就映射成新节点，为空则新节点也置 None
            cur = cur.next  # 继续处理下一个原节点
        return dummy.next  # 跳过哨兵，返回新链表真正的头节点
