# 题目：1265. 逆序打印不可变链表（Print Immutable Linked List in Reverse）
# 思路：递归到链尾再在回溯时调用 printValue，借助调用栈把输出顺序倒过来；只能使用 getNext 与 printValue 两个接口。
# 时间复杂度：O(n)，每个节点打印一次；空间复杂度：O(n)，递归栈深度等于链表长度。
# """
# This is the ImmutableListNode's API interface.
# You should not implement it, or speculate about its implementation.
# """
# class ImmutableListNode:
#     def printValue(self) -> None: # print the value of this node.
#     def getNext(self) -> 'ImmutableListNode': # return the next node.


class Solution:  # 题解类
    def printLinkedListInReverse(self, head: 'ImmutableListNode') -> None:  # head 是不可变链表头节点，不能改动其结构；返回 None 表示只做打印
        if head:  # 空节点直接返回，作为递归终止条件
            self.printLinkedListInReverse(head.getNext())  # 先递归到后继节点，让更靠后的值先被输出
            head.printValue()  # 回溯时打印当前节点值，形成逆序结果
