# 题目：2074. 反转偶数长度组的节点（Reverse Nodes in Even Length Groups）
# 思路：先求链表总长，再按组长度 1、2、3……切分，组长为偶数就原地反转该组；最后剩余不足一组的节点单独判断是否反转。
# 时间复杂度：O(n)，每个节点被常数次遍历；空间复杂度：O(1)，只用到若干指针变量。
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # LeetCode 约定的题解类
    def reverseEvenLengthGroups(self, head: Optional[ListNode]) -> Optional[ListNode]:  # head 是链表头，返回按「组长为偶数则反转」规则处理后的头节点
        def reverse(head, l):  # 辅助函数：反转以 head 开头的前 l 个节点，返回反转后的新头
            prev, cur, tail = None, head, head  # prev 是已反转部分的头，cur 是当前待处理节点，tail 是反转前的首节点（会变成尾）
            i = 0  # 已反转的节点计数
            while cur and i < l:  # 未到链尾且还没反转够 l 个就继续
                t = cur.next  # 先保存后继，避免反转后断链丢失
                cur.next = prev  # 把当前节点指向前一个节点，完成一次反转
                prev = cur  # 反转后的新头前移
                cur = t  # 继续处理原来的后继
                i += 1  # 计数加一
            tail.next = cur  # 反转后的尾节点接上剩余部分（不足 l 个时 cur 可能为 None）
            return prev  # 返回反转后的新头（l 为 0 时返回 None）

        n = 0  # 先统计链表总长度 n
        t = head  # 用临时指针遍历链表
        while t:  # 走到链表末尾
            t = t.next  # 前进一个节点
            n += 1  # 长度加一
        dummy = ListNode(0, head)  # 哑节点，便于统一处理第一组
        prev = dummy  # prev 始终指向「当前组的前一个节点」
        l = 1  # 当前组的期望长度，从 1 开始
        while (1 + l) * l // 2 <= n and prev:  # 前 l 组总长 l(l+1)/2，不超过 n 说明这一组完整存在
            if l % 2 == 0:  # 组长为偶数时才需要反转
                prev.next = reverse(prev.next, l)  # 反转本组的 l 个节点，并让前一节点指向新的组头
            i = 0  # 统计本组已走过的节点数
            while i < l and prev:  # 把 prev 移到本组最后一个节点上
                prev = prev.next  # 向后移动一格
                i += 1  # 计数加一
            l += 1  # 组长递增，准备处理下一组
        left = n - l * (l - 1) // 2  # 剩余节点数，构成最后一组（长度可能不足 l）
        if left > 0 and left % 2 == 0:  # 剩余组非空且长度为偶数才反转
            prev.next = reverse(prev.next, left)  # 反转最后一组
        return dummy.next  # 返回真正的头节点
