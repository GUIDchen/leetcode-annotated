# 题目：623. 在二叉树中增加一行（Add One Row to Tree）
# 思路：深度为 1 时新建根节点；否则 DFS 找到第 depth-1 层的节点，把新节点插在它和原孩子之间。
# 时间复杂度：O(n)，最坏要遍历整棵树；空间复杂度：O(h)，递归栈深度为树高。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def addOneRow(  # 在指定深度插入一行新节点，所有新节点的值都是 val
        self, root: Optional[TreeNode], val: int, depth: int  # root 为原树根，val 为插入值，depth 为目标深度
    ) -> Optional[TreeNode]:  # 返回处理后的树根
        def dfs(root, d):  # 内层递归函数：root 是当前节点，d 是它所在的深度
            if root is None:  # 空节点无需处理，直接回溯
                return  # 返回上层调用，避免对空节点取属性
            if d == depth - 1:  # 到达目标深度的上一层，新的一行就插在它的两个孩子位置
                root.left = TreeNode(val, root.left, None)  # 新左孩子：值为 val，原来的左子树挂到它的左孩子上
                root.right = TreeNode(val, None, root.right)  # 新右孩子：值为 val，原来的右子树挂到它的右孩子上
                return  # 本层已处理完，不再往下递归，避免重复插入
            dfs(root.left, d + 1)  # 继续处理左子树的下一层
            dfs(root.right, d + 1)  # 继续处理右子树的下一层

        if depth == 1:  # 深度为 1 属于特殊情况：新值成为新根
            return TreeNode(val, root)  # 原树整体挂到新根的左孩子上
        dfs(root, 1)  # 从第 1 层开始向下查找
        return root  # 走的不是换根分支，原根节点不变，直接返回
