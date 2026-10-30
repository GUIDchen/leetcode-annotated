# 题目：1080. 根到叶路径上的不足节点（Insufficient Nodes in Root to Leaf Paths）
# 思路：自顶向下把 limit 递减为「经过当前结点后还需要的剩余目标」；叶子处若剩余目标仍大于 0 就删除该叶子，回溯时若某结点的两个孩子都被删光，它自己也不再通向合格叶子，同样删除。
# 时间复杂度：O(n)，每个结点只访问一次；空间复杂度：O(h)，h 为树高，递归栈开销。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def sufficientSubset(
        self, root: Optional[TreeNode], limit: int  # root 是子树根，limit 是当前路径还需要的剩余值
    ) -> Optional[TreeNode]:  # 返回处理后的子树根，被删光时返回 None
        if root is None:  # 空结点直接返回，作为递归的边界
            return None  # 空树没有可删的结点
        limit -= root.val  # 把当前结点值从剩余目标中扣掉，得到子结点还需达到的剩余值
        if root.left is None and root.right is None:  # 当前结点是叶子，路径和已经确定
            return None if limit > 0 else root  # 剩余目标仍大于 0 说明路径和不足，删除该叶子；否则保留
        root.left = self.sufficientSubset(root.left, limit)  # 递归处理左子树，并把可能被删除的 None 写回左孩子
        root.right = self.sufficientSubset(root.right, limit)  # 递归处理右子树，并把可能被删除的 None 写回右孩子
        return None if root.left is None and root.right is None else root  # 两个孩子都没了，本结点也不再通向合格叶子，删除；否则保留
