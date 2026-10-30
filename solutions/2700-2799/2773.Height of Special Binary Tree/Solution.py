# 题目：2773. 特殊二叉树的高度（Height of Special Binary Tree 🔒）
# 思路：特殊二叉树中叶子节点的 left / right 会分别指回它的中序前驱与后继，所以“孩子反过来指向父亲”的边不是真正的孩子边；从根做 DFS，跳过这类回指边并统计最大深度。
# 时间复杂度：O(n)，每个节点至多访问一次；空间复杂度：O(h)，h 为树高，即递归栈深度。
# 下面这段 TreeNode 定义由 LeetCode 判题器提供，这里以注释形式保留签名占位
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def heightOfTree(self, root: Optional[TreeNode]) -> int:  # root 是这棵特殊二叉树的根节点
        def dfs(root: Optional[TreeNode], d: int):  # 递归函数：root 是当前节点，d 是当前深度
            nonlocal ans  # 声明 ans 取自外层函数，否则这里会创建新的局部变量
            ans = max(ans, d)  # 用当前深度更新最大深度
            if root.left and root.left.right != root:  # 左孩子存在，且它的 right 不是指回当前节点（否则是叶子回指边）
                dfs(root.left, d + 1)  # 走真正的左孩子边继续下探，深度加一
            if root.right and root.right.left != root:  # 右孩子存在，且它的 left 不是指回当前节点（否则是叶子回指边）
                dfs(root.right, d + 1)  # 走真正的右孩子边继续下探，深度加一

        ans = 0  # 初始化最大深度（树高），根节点深度为 0
        dfs(root, 0)  # 从根节点、深度 0 开始深度优先搜索
        return ans  # 返回整棵特殊二叉树的高度
