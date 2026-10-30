# 题目：998. 最大二叉树 II（Maximum Binary Tree II）
# 思路：val 追加在构造序列末尾，所以只会出现在根或右链上：递归下行右子树，遇到空位或更小的节点就新建节点，并让原树整体作为左子树。
# 时间复杂度：O(h)，h 为树高（最坏 O(n)）；空间复杂度：O(h)，递归栈深度。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def insertIntoMaxTree(  # root：最大二叉树根节点；val：要插入的新值（在遍历序列末尾）
        self, root: Optional[TreeNode], val: int  # 参数：根节点与新加入的值
    ) -> Optional[TreeNode]:  # 返回插入后的新根节点
        if root is None or root.val < val:  # 空树或新值更大：新值成为根，原树整体作为它的左子树
            return TreeNode(val, root)  # TreeNode(val, root) 新建节点，left 指向原树，right 默认为空
        root.right = self.insertIntoMaxTree(root.right, val)  # val 更小，递归插入到右子树，并把新右子树接回
        return root  # 根节点不变，返回
