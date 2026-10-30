# 题目：450. 删除二叉搜索树中的节点（Delete Node in a BST）
# 思路：利用 BST 的有序性递归定位 key；命中后用「右子树最小值（中序后继）」顶替，并把原左子树挂到后继的左指针上。
# 时间复杂度：O(h)，h 为树高，最坏退化成链表为 O(n)；空间复杂度：O(h)，递归调用栈。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def deleteNode(self, root: Optional[TreeNode], key: int) -> Optional[TreeNode]:  # root：BST 根结点；key：要删除的值；返回删除后的子树根
        if root is None:  # 空树或没找到该值：递归终止
            return None  # 返回空指针
        if root.val > key:  # key 比当前值小，只可能位于左子树
            root.left = self.deleteNode(root.left, key)  # 递归删除左子树中的 key，并把新的左子树根接回来
            return root  # 当前根不受影响，直接返回
        if root.val < key:  # key 比当前值大，只可能位于右子树
            root.right = self.deleteNode(root.right, key)  # 递归删除右子树中的 key，并把新的右子树根接回来
            return root  # 当前根不受影响，直接返回
        if root.left is None:  # 命中结点且没有左孩子
            return root.right  # 用右孩子顶替（右孩子可能为 None）
        if root.right is None:  # 只有左孩子
            return root.left  # 用左孩子顶替
        node = root.right  # 两个孩子都存在：先去右子树找最小结点（中序后继）
        while node.left:  # 沿左链一路向下
            node = node.left  # 停下时 node 就是右子树的最小值
        node.left = root.left  # 把原左子树挂到后继的左指针上，保持 BST 有序性
        root = root.right  # 后继所在的右子树顶替被删结点，成为新的子树根
        return root  # 返回新的子树根
