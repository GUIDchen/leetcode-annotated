# 题目：701. 二叉搜索树中的插入操作（Insert into a Binary Search Tree）
# 思路：按二叉搜索树的规则递归下行，找到空位置后新建结点挂上去，再沿递归返回的路径把根指针接回父结点。
# 时间复杂度：O(h)，h 为树高，只走一条从根到叶的路径；空间复杂度：O(h)，递归调用栈的深度。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def insertIntoBST(self, root: Optional[TreeNode], val: int) -> Optional[TreeNode]:  # root 是二叉搜索树根，val 是要插入的值，返回插入后的根
        if root is None:  # 走到空位置，说明这里就是要插入的位置
            return TreeNode(val)  # 用新值创建叶子结点并返回给上层
        if root.val > val:  # 当前结点值更大，新值应落在左子树
            root.left = self.insertIntoBST(root.left, val)  # 递归插入左子树，并把新的左子树根接回来
        else:  # 当前结点值更小（题目保证值不重复）
            root.right = self.insertIntoBST(root.right, val)  # 递归插入右子树，并把新的右子树根接回来
        return root  # 本层子树处理完毕，把（可能更新的）根返回给上层
