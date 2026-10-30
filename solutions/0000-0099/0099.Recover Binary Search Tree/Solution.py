# 题目：99. 恢复二叉搜索树（Recover Binary Search Tree）
# 思路：中序遍历应严格递增，被交换的两个节点会产生一到两处逆序；记下逆序涉及的两个节点，最后交换它们的值。
# 时间复杂度：O(n)，中序遍历每个节点一次；空间复杂度：O(h)，h 为树高，递归栈开销。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def recoverTree(self, root: Optional[TreeNode]) -> None:  # 原地修改 root，函数不需要返回值
        """
        Do not return anything, modify root in-place instead.
        """

        def dfs(root):  # 中序遍历以 root 为根的子树，寻找被交换的两个节点
            if root is None:  # 空节点没有内容可访问
                return  # 直接结束本层递归
            nonlocal prev, first, second  # 三个状态变量定义在外层，递归中需要读改，故声明 nonlocal
            dfs(root.left)  # 先遍历左子树，保证按中序访问
            if prev and prev.val > root.val:  # 中序序列本应递增，出现逆序说明这两个节点被交换
                if first is None:  # 只在第一处逆序时记录第一个节点
                    first = prev  # 第一处逆序中的较大者是第一个错误节点
                second = root  # 较小者记为第二个错误节点；不断更新可兼容两节点不相邻的情况
            prev = root  # 更新前驱为当前节点
            dfs(root.right)  # 再遍历右子树

        prev = first = second = None  # 初始化三个状态变量：前驱与两个错误节点
        dfs(root)  # 中序遍历找出两个错误节点
        first.val, second.val = second.val, first.val  # 交换两个节点的值完成恢复
