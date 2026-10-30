# 题目：2641. 二叉树的堂兄弟节点 II（Cousins in Binary Tree II）
# 思路：两次 DFS：dfs1 把每层节点值累加到 s；dfs2 把每个子节点改成「本层总和 - 它与它的兄弟之和」。
# 时间复杂度：O(n)，每个节点访问两次；空间复杂度：O(h)，递归栈深度（s 另占 O(h)）。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def replaceValueInTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:  # root：二叉树根节点
        def dfs1(root: Optional[TreeNode], depth: int):  # 内层函数：统计每一层的节点值之和
            if root is None:  # 空节点没有值可累加，直接返回
                return
            if len(s) <= depth:  # s 还没有记录到这一层
                s.append(0)  # 动态扩容，为新的一层补一个 0
            s[depth] += root.val  # 把当前节点值累加到它所在的层
            dfs1(root.left, depth + 1)  # 递归统计左子树，深度加 1
            dfs1(root.right, depth + 1)  # 递归统计右子树，深度加 1

        def dfs2(root: Optional[TreeNode], depth: int):  # 内层函数：改写每个子节点的值
            sub = (root.left.val if root.left else 0) + (  # 孩子值之和，左孩子缺失记 0
                root.right.val if root.right else 0  # 右孩子缺失也记 0
            )  # 兄弟俩的和，后面要从层和里整体减掉
            depth += 1  # 先下移一层，因为接下来处理的是孩子所在层
            if root.left:  # 有左孩子才需要改写
                root.left.val = s[depth] - sub  # 新值 = 本层总和 - 自己与兄弟之和 = 堂兄弟之和
                dfs2(root.left, depth)  # 继续递归处理左子树
            if root.right:  # 有右孩子才需要改写
                root.right.val = s[depth] - sub  # 右孩子同理：本层总和减去自身与兄弟
                dfs2(root.right, depth)  # 继续递归处理右子树

        s = []  # 按层统计的节点值之和，下标就是深度
        dfs1(root, 0)  # 第一遍：统计每一层的总和
        root.val = 0  # 根节点没有堂兄弟，置 0
        dfs2(root, 0)  # 第二遍：改写其余所有节点
        return root  # 返回原地修改后的根节点
