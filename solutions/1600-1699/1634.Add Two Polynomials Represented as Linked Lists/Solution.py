# 题目：1634. 求两个多项式链表的和（Add Two Polynomials Represented as Linked Lists）
# 思路：按幂次从高到低归并两条有序链表，幂次相同时把系数相加，系数为 0 的项丢弃。
# 时间复杂度：O(m + n)，两条链表各遍历一次；空间复杂度：O(1) 额外空间（结果复用原结点，仅在系数非零时新建结点）。
# Definition for polynomial singly-linked list.
# class PolyNode:
#     def __init__(self, x=0, y=0, next=None):
#         self.coefficient = x
#         self.power = y
#         self.next = next


class Solution:  # LeetCode 约定的题解类
    def addPoly(self, poly1: "PolyNode", poly2: "PolyNode") -> "PolyNode":  # poly1、poly2 是两条按幂次递减排列的多项式链表，返回合并后的新链表
        dummy = curr = PolyNode()  # 哨兵结点 dummy 简化头结点处理，curr 是结果链表尾指针
        while poly1 and poly2:  # 两条链表都还有结点时归并
            if poly1.power > poly2.power:  # 情况一：poly1 的幂次更大，它的这一项应排在前面
                curr.next = poly1  # 把 poly1 当前结点直接接到结果尾部（原地复用结点）
                poly1 = poly1.next  # poly1 指针后移
                curr = curr.next  # 结果尾指针后移到刚接入的结点
            elif poly1.power < poly2.power:  # 情况二：poly2 的幂次更大
                curr.next = poly2  # 把 poly2 当前结点直接接到结果尾部
                poly2 = poly2.next  # poly2 指针后移
                curr = curr.next  # 结果尾指针后移到刚接入的结点
            else:  # 情况三：两者幂次相同，需要合并同类项
                if c := poly1.coefficient + poly2.coefficient:  # 海象运算符：算出合并后的系数 c，只有非 0 才进入分支（系数为 0 的项丢弃）
                    curr.next = PolyNode(c, poly1.power)  # 新建结点（系数, 幂次）接到结果尾部
                    curr = curr.next  # 结果尾指针后移
                poly1 = poly1.next  # poly1 指针后移，这一项已处理完
                poly2 = poly2.next  # poly2 指针后移，这一项已处理完
        curr.next = poly1 or poly2  # 循环结束后把非空的那条链表剩余部分整体接上（都为空时接 None）
        return dummy.next  # 跳过哨兵，返回真正的结果头结点
