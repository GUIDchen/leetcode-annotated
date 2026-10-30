# 题目：145. 二叉树的后序遍历（Binary Tree Postorder Traversal）
# 思路：递归 DFS，按「左 → 右 → 根」的次序访问节点，左右子树都处理完才记录根的值。
# 时间复杂度：O(n)，每个节点恰好访问一次；空间复杂度：O(h) 递归栈（h 为树高），结果列表另占 O(n)。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def postorderTraversal(self, root: Optional[TreeNode]) -> List[int]:  # root：树根；返回后序遍历得到的值列表
        def dfs(root):  # 内层递归函数，闭包引用外层的 ans
            if root is None:  # 空节点是递归终止条件
                return  # 直接返回上一层
            dfs(root.left)  # 先后序遍历左子树
            dfs(root.right)  # 再后序遍历右子树
            ans.append(root.val)  # 后序：左右都完成后，最后记录根的值

        ans = []  # 结果列表在 dfs 定义之后再创建，闭包运行时仍能访问到它
        dfs(root)  # 从根节点开始遍历
        return ans  # 返回后序序列
