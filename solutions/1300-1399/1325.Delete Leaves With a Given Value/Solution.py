# 题目：1325. 删除给定值的叶子节点（Delete Leaves With a Given Value）
# 思路：后序遍历。先递归清理左右子树，再判断当前节点是否已变成值为 target 的叶子，是则返回 None 让父节点摘掉它。
# 时间复杂度：O(N)，每个节点访问一次；空间复杂度：O(H)，递归栈深度为树高。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # 题解类
    def removeLeafNodes(  # 定义递归函数：返回清理后的子树根
        self, root: Optional[TreeNode], target: int  # self 是绑定的实例；root 为当前子树根，target 为要删的叶子值
    ) -> Optional[TreeNode]:  # 返回类型可为 None，表示整棵子树被删光
        if root is None:  # 递归边界：空节点
            return None  # 空节点没有可删的叶子
        root.left = self.removeLeafNodes(root.left, target)  # 先递归清理左子树，用返回的新根替换原来的左孩子
        root.right = self.removeLeafNodes(root.right, target)  # 再递归清理右子树，同样替换右孩子
        if root.left is None and root.right is None and root.val == target:  # 左右都空了且自己的值等于 target，说明自己刚变成需要删除的叶子
            return None  # 返回 None，告诉父节点把自己摘掉
        return root  # 否则保留自己，返回当前根
