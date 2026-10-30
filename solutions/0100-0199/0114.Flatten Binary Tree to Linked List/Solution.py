# 题目：114. 二叉树展开为链表（Flatten Binary Tree to Linked List）
# 思路：对每个节点，若存在左子树，就找到左子树最右节点作为前驱，把原右子树挂到前驱右侧，再把左子树搬到右边并清空左指针，然后沿右链前进。
# 时间复杂度：O(n)，每个节点最多被遍历常数次；空间复杂度：O(1)，只用了几个指针变量。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def flatten(self, root: Optional[TreeNode]) -> None:  # root 为树根；函数原地修改，返回 None
        # 下面这段文档字符串是题目模板自带的说明：不返回任何东西，只原地修改 root
        """
        Do not return anything, modify root in-place instead.
        """
        while root:  # 逐个节点处理，每轮把当前节点的左子树搬到右侧
            if root.left:  # 没有左子树就不用搬运
                pre = root.left  # pre 负责找左子树的最右节点
                while pre.right:  # 一直向右走到左子树最右端
                    pre = pre.right  # 前进一个右孩子
                pre.right = root.right  # 把原右子树挂到前驱右边，保持先序顺序
                root.right = root.left  # 整棵左子树移到右侧
                root.left = None  # 左指针置空，满足「只有右链」的要求
            root = root.right  # 沿右链前进到下一个待处理的节点
