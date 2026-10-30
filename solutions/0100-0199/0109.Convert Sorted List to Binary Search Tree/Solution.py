# 题目：109. 有序链表转换二叉搜索树（Convert Sorted List to Binary Search Tree）
# 思路：先遍历链表把值存成有序数组 nums，再取区间中点作根、左右两半递归建子树得到平衡 BST。
# 时间复杂度：O(n)，链表遍历一次、每个元素建一个结点；空间复杂度：O(n)，数组与递归栈。
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def sortedListToBST(self, head: Optional[ListNode]) -> Optional[TreeNode]:  # head 是有序链表头，返回平衡 BST 的根
        def dfs(i: int, j: int) -> Optional[TreeNode]:  # 递归函数：在闭区间 [i, j] 上建子树（nums 在后面赋值，靠闭包在调用时才读取）
            if i > j:  # 区间为空，没有元素可建
                return None  # 空区间返回 None
            mid = (i + j) >> 1  # 取中点作根，左右两侧元素个数尽量相等
            l, r = dfs(i, mid - 1), dfs(mid + 1, j)  # 先递归建左子树，再递归建右子树
            return TreeNode(nums[mid], l, r)  # 用中点值建根结点并挂上左右子树

        nums = []  # 存放链表值的有序数组
        while head:  # 顺序遍历链表
            nums.append(head.val)  # 末尾追加当前结点的值
            head = head.next  # 指针后移
        return dfs(0, len(nums) - 1)  # 在数组的整个区间上递归建树
