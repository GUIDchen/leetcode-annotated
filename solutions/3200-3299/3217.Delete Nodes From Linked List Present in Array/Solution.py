# 题目：3217. 从链表中移除在数组中存在的节点（Delete Nodes From Linked List Present in Array）
# 思路：nums 转成哈希集合，用哑结点从头遍历链表，后继命中集合就跳过它，否则前驱后移。
# 时间复杂度：O(n + m)，n 为数组长度、m 为链表长度；空间复杂度：O(n)，哈希集合存放数组中的全部值。
# 下面是 LeetCode 判题器预置的单链表节点定义，以注释形式给出，不属于本题代码
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # LeetCode 约定的题解类
    def modifiedList(  # nums 是待删除的值列表，head 是原链表头结点
        self, nums: List[int], head: Optional[ListNode]  # 参数换行是 black 的格式化结果，三个参数的含义不变
    ) -> Optional[ListNode]:  # 返回删除后的新头结点，链表可能为空
        s = set(nums)  # 哈希集合：O(1) 判断某个值是否需要删除
        pre = dummy = ListNode(next=head)  # dummy 是哑结点；pre 是当前检查节点的前驱，初始时两者指向同一节点
        while pre.next:  # 只要后面还有节点就继续检查
            if pre.next.val in s:  # 后继节点的值需要被删除
                pre.next = pre.next.next  # 让前驱跳过该节点完成删除，pre 不动以便继续检查新的后继
            else:  # 后继节点需要保留
                pre = pre.next  # 前驱后移一位
        return dummy.next  # 哑结点的后继就是删除后的新头结点
