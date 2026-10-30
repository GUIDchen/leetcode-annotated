# 题目：725. 分隔链表（Split Linked List in Parts）
# 思路：先求链表长度 n，则前 n%k 段各长 n//k+1，其余各长 n//k；再按段长边走边断开，空段保留 None。
# 时间复杂度：O(n + k)，需先遍历一次求长度；空间复杂度：O(k)，保存 k 个段头指针。
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # LeetCode 约定的题解类
    def splitListToParts(  # head：链表头；k：段数
        self, head: Optional[ListNode], k: int
    ) -> List[Optional[ListNode]]:  # 返回值是各段的头节点，空段为 None
        n = 0  # 链表长度
        cur = head  # 遍历指针
        while cur:  # 统计节点总数
            n += 1  # 长度加一
            cur = cur.next  # 指针后移
        cnt, mod = divmod(n, k)  # 同时得到「每段至少 cnt 个」和「前 mod 段各多 1 个」
        ans = [None] * k  # 结果列表长度固定为 k，空段保持 None
        cur = head  # 当前待分配的节点
        for i in range(k):  # 逐段切分
            if cur is None:  # 节点已经用完
                break  # 后面的段都是空链表，直接结束
            ans[i] = cur  # 本段的头节点
            m = cnt + int(i < mod)  # 本段长度：布尔值 i < mod 转成 0 或 1
            for _ in range(1, m):  # 走 m-1 步，停在本段最后一个节点上
                cur = cur.next  # 前进一步
            nxt = cur.next  # 记下下一段的起点
            cur.next = None  # 断开本段尾部，使其成为独立链表
            cur = nxt  # 转到下一段
        return ans  # 返回各段的头节点
