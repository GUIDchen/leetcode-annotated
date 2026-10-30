# 题目：98. 验证二叉搜索树（Validate Binary Search Tree）
# 思路：BST 的中序遍历序列严格递增，用 prev 记录前驱值，递归到中序位置时与 prev 比较，边遍历边校验。
# 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，h 为树高，递归栈的深度。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def isValidBST(self, root: Optional[TreeNode]) -> bool:  # root：待验证的树根，返回是否为合法 BST
        def dfs(root: Optional[TreeNode]) -> bool:  # 中序遍历校验以 root 为根的子树
            if root is None:  # 空节点没有键值可比
                return True  # 空子树满足 BST 性质
            if not dfs(root.left):  # 先递归校验左子树，左子树必须全部小于当前值
                return False  # 左子树不合法，直接向上返回失败
            nonlocal prev  # 声明 prev 来自外层函数作用域，递归过程中需要读取并改写它
            if prev >= root.val:  # 中序序列必须严格递增，等于同样不合法
                return False  # 出现逆序，说明不是 BST
            prev = root.val  # 把当前值记为前驱，供中序序列中的下一个节点比较
            return dfs(root.right)  # 右子树的校验结果就是本子树的结果

        prev = -inf  # 前驱初始化为负无穷，保证第一个被访问的节点不会误判失败
        return dfs(root)  # 从根开始做中序遍历校验
