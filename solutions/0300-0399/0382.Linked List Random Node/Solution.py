# 题目：382. 链表随机节点（Linked List Random Node）
# 思路：蓄水池抽样，遍历到第 n 个节点时以 1/n 的概率把它换成答案，最终每个节点被返回的概率都相同。
# 时间复杂度：getRandom 为 O(n)，n 是链表长度；空间复杂度：O(1)，只用了几个计数变量。
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # 题解类：保存链表头，getRandom 会被判题器反复调用
    def __init__(self, head: Optional[ListNode]):  # 构造函数：head 是待抽样的链表头节点
        self.head = head  # 记住头节点，保证每次调用都能从头开始遍历

    def getRandom(self) -> int:  # 等概率返回链表中某个节点的 val
        n = ans = 0  # n 统计已遍历的节点数，ans 保存当前抽中的值
        head = self.head  # 用局部变量遍历，避免改动 self.head
        while head:  # 单次遍历，边数边做蓄水池抽样
            n += 1  # 当前访问的是第 n 个节点
            x = random.randint(1, n)  # 在 [1, n] 上等概率取整数
            if n == x:  # 取到 n 的概率是 1/n，即以该概率替换答案
                ans = head.val  # 更新当前抽中的节点值
            head = head.next  # 指针后移，继续处理下一个节点
        return ans  # 每个节点被返回的概率都是 1/链表长度


# Your Solution object will be instantiated and called as such:
# obj = Solution(head)
# param_1 = obj.getRandom()
