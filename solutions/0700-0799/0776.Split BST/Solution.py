# 题目：776. 拆分二叉搜索树（Split BST）
# 核心思路：按 target 递归拆树——根不大于 target 时它属于左半边，递归拆右子树并把其中较大的部分接回根的右侧；否则对称处理左子树。
# 时间复杂度 O(h)，h 为树高；空间复杂度 O(h)，递归栈深度。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def splitBST(  # 返回 [不大于 target 的树, 大于 target 的树]
        self, root: Optional[TreeNode], target: int  # 换行书写参数：root 为 BST 根，target 为分界值
    ) -> List[Optional[TreeNode]]:  # 返回列表：下标 0 是左半边根，下标 1 是右半边根
        def dfs(root):  # 递归拆分函数
            if root is None:  # 空节点拆成两个空树
                return [None, None]  # 返回 [None, None] 表示两边都为空
            if root.val <= target:  # 当前根不大于 target，它应归入左半边
                l, r = dfs(root.right)  # 拆开右子树：l 是其中仍不大于 target 的部分，r 是大于 target 的部分
                root.right = l  # 把 l 接回根的右边，保持 BST 性质
                return [root, r]  # 返回 [左半边根, 右半边根 r]
            else:  # 当前根大于 target，它应归入右半边
                l, r = dfs(root.left)  # 拆开左子树：l 是不大于 target 的部分，r 是大于 target 的部分
                root.left = r  # 把 r 接回根的左边，保持 BST 性质
                return [l, root]  # 返回 [左半边根 l, 右半边根]

        return dfs(root)  # 从整棵 BST 的根开始拆分
