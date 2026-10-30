# 题目：572. 另一棵树的子树（Subtree of Another Tree）
# 核心思路：枚举 root 的每个结点，用内部函数 same 判断以该结点为根的子树是否与 subRoot 完全相同。
# 时间复杂度：O(|root| * |subRoot|)，每个结点做一次匹配；空间复杂度：O(|root|) 递归栈。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def isSubtree(self, root: Optional[TreeNode], subRoot: Optional[TreeNode]) -> bool:  # root 为大树，subRoot 为待匹配子树
        def same(p: Optional[TreeNode], q: Optional[TreeNode]) -> bool:  # 判断以 p、q 为根的两棵树是否完全相同
            if p is None or q is None:  # 任意一边为空时不能再逐值比较
                return p is q  # 同时为空才算相同，一空一非空则不同
            return p.val == q.val and same(p.left, q.left) and same(p.right, q.right)  # 根值相等且左右子树分别相同，才是同一棵树

        if root is None:  # 大树遍历到空结点，该分支不可能再有匹配
            return False  # 空树里找不到非空子树
        return (  # 三选一：当前结点起完全相同，或答案在左子树，或答案在右子树
            same(root, subRoot)  # 以当前结点为根整棵匹配
            or self.isSubtree(root.left, subRoot)  # 递归到左子树继续找
            or self.isSubtree(root.right, subRoot)  # 递归到右子树继续找
        )  # 括号收尾，返回匹配结果
