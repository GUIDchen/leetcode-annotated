# 题目：1367. 二叉树中的链表（Linked List in Binary Tree）
# 思路：外层枚举树中每个节点作为起点，内层 DFS 同时沿链表 next 与树的左右孩子向下匹配。
# 时间复杂度：O(N·L)，N 为树节点数、L 为链表长度；空间复杂度：O(H + L)，递归栈深度。
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
    def isSubPath(self, head: Optional[ListNode], root: Optional[TreeNode]) -> bool:  # head：链表头；root：二叉树根；判断链表是否对应树中某条向下的路径
        def dfs(head, root):  # 内部 DFS：从 root 开始能否依次匹配完链表剩余部分
            if head is None:  # 链表已经走完，说明匹配成功
                return True  # 返回 True
            if root is None or root.val != head.val:  # 树节点为空或当前值不等，匹配失败
                return False  # 返回 False
            return dfs(head.next, root.left) or dfs(head.next, root.right)  # 链表指针后移，左右子树任一成功即可

        if root is None:  # 整棵树为空，不可能包含该链表
            return False  # 返回 False
        return (  # 以 root 为起点匹配，或分别到左右子树里找新的起点
            dfs(head, root)  # 尝试以 root 为起点
            or self.isSubPath(head, root.left)  # 到左子树里找匹配起点
            or self.isSubPath(head, root.right)  # 到右子树里找匹配起点
        )  # 三种情况任一成立即可，括号表达式结束
