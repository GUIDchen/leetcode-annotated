# 题目：897. 递增顺序搜索树（Increasing Order Search Tree）
# 核心思路：中序遍历二叉搜索树得到升序序列，遍历时用 prev 指针把节点原地串成只有右孩子的链。
# 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，递归栈深度，h 为树高。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def increasingBST(self, root: TreeNode) -> TreeNode:  # root：原二叉搜索树的根
        def dfs(root):  # 中序遍历（左 → 根 → 右），同时把节点接到结果链上
            if root is None:  # 空节点直接返回，递归出口
                return  # 没有节点可处理
            nonlocal prev  # 声明 prev 是外层函数的变量，需要在 dfs 内修改
            dfs(root.left)  # 先递归处理左子树，更小的值先接链
            prev.right = root  # 当前节点接到链尾的右指针
            root.left = None  # 题目要求新树每个节点都不能有左孩子
            prev = root  # 链尾后移，指向刚接上的节点
            dfs(root.right)  # 最后递归处理右子树

        dummy = prev = TreeNode(right=root)  # 哑结点作为链头的前驱；prev 初始指向它
        dfs(root)  # 从根开始中序遍历并原地改链
        return dummy.right  # 哑结点的右孩子就是新树的根
