# 题目：230. 二叉搜索树中第 K 小的元素（Kth Smallest Element in a BST）
# 思路：用列表当显式栈模拟中序遍历，二叉搜索树的中序序列升序，第 k 个出栈的结点就是答案。
# 时间复杂度：O(H + k)，H 为树高（最坏 O(n)）；空间复杂度：O(H)，即栈的最大深度。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def kthSmallest(self, root: Optional[TreeNode], k: int) -> int:  # root 是二叉搜索树根结点，k 是目标排名（从 1 开始），返回第 k 小的值
        stk = []  # 显式栈：保存一路向左时经过的结点，替代递归调用栈
        while root or stk:  # 还有未访问的结点，或栈里还有待回溯的结点，就继续遍历
            if root:  # 当前结点非空：一路向左深入，先把更小的结点走完
                stk.append(root)  # 把当前结点压栈，留待回溯时访问
                root = root.left  # 继续向左孩子走，直到没有左孩子
            else:  # 左边走到头了，该弹出栈顶结点访问了
                root = stk.pop()  # 弹出栈顶：它是当前最小的未访问结点
                k -= 1  # 访问一个结点就把计数减一
                if k == 0:  # 减到 0 说明刚访问的这个结点就是第 k 小
                    return root.val  # 返回答案
                root = root.right  # 转向右子树，右子树的值都比当前结点大
