# 题目：426. 将二叉搜索树转化为排序的双向链表（Convert Binary Search Tree to Sorted Doubly Linked List）
# 思路：BST 的中序遍历天然升序，用非局部变量 prev 记住前驱，遍历时把当前节点接在前驱之后，最后把首尾相连成循环双向链表。
# 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(h)，h 为树高，来自递归调用栈。
# 说明：下面是题目自带的 Node 定义（注释块，由判题器提供），仅作参考。
"""
# Definition for a Node.
class Node:
    def __init__(self, val, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
"""


class Solution:  # LeetCode 题解类
    def treeToDoublyList(self, root: 'Optional[Node]') -> 'Optional[Node]':  # root：BST 的根节点；返回排序循环双向链表的头节点
        def dfs(root):  # 中序遍历，按升序把节点逐个串成双向链表
            if root is None:  # 递归边界：空节点
                return  # 直接返回
            nonlocal prev, head  # 声明要修改外层函数的 prev 与 head
            dfs(root.left)  # 先处理左子树，那里是更小的值
            if prev:  # 已经有前驱，说明当前节点不是最小节点
                prev.right = root  # 前驱的 right 指向当前节点
                root.left = prev  # 当前节点的 left 指回前驱，保持双向
            else:  # 没有前驱，说明当前节点是最小节点
                head = root  # 记录链表头
            prev = root  # 当前节点成为下一轮递归的前驱
            dfs(root.right)  # 最后处理右子树，那里是更大的值

        if root is None:  # 空树直接返回空
            return None  # 避免后面访问 None 的属性
        head = prev = None  # 初始化非局部状态：头节点与前驱
        dfs(root)  # 中序遍历建立链表，此时还不是循环链表
        prev.right = head  # 遍历结束后 prev 是最大值节点，让它指向头节点
        head.left = prev  # 头节点的 left 指向最大值节点，闭合成环
        return head  # 返回链表头，即最小值节点
