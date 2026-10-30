# 题目：23. 合并 K 个升序链表（Merge k Sorted Lists）
# 思路：小根堆保存每条链表的当前头结点，每次弹出全局最小值接到答案尾部，再把该结点的后继入堆。
# 时间复杂度：O(N log k)，N 为结点总数，每结点入堆/出堆各一次；空间复杂度：O(k)，堆中最多 k 个结点。
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # LeetCode 约定的题解类
    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:  # lists：k 条升序链表的头结点数组
        setattr(ListNode, "__lt__", lambda a, b: a.val < b.val)  # heapq 比较需要 __lt__，运行期给 ListNode 打上按 val 比较的方法
        pq = [head for head in lists if head]  # 只把非空链表的头结点放进堆，跳过 None
        heapify(pq)  # 原地把列表调整成小根堆（heapify 由 LeetCode 环境提供）
        dummy = cur = ListNode()  # 哑结点充当答案头，cur 指向答案链表尾部
        while pq:  # 只要堆非空就还没合并完
            node = heappop(pq)  # 弹出当前全局最小结点
            if node.next:  # 该结点所属链表还有后续结点
                heappush(pq, node.next)  # 后继入堆，参与后续比较
            cur.next = node  # 把最小值挂到答案尾部
            cur = cur.next  # 尾指针后移
        return dummy.next  # 返回真正的答案头结点
