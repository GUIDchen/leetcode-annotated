# 题目：1469. 寻找所有的独生节点（Find All The Lonely Nodes）
# 核心思路：DFS 遍历整棵树，若某节点只有一个孩子，就把这个唯一孩子的值加入答案。
# 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，递归栈深度为树高。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def getLonelyNodes(self, root: Optional[TreeNode]) -> List[int]:  # root 是二叉树根节点，返回所有独生节点的值
        def dfs(root: Optional[TreeNode]):  # 内层递归函数，负责遍历以 root 为根的子树
            if root is None or root.left == root.right:  # 空节点返回；左右都为 None（叶子）时也没有独生节点
                return  # 结束本层递归
            if root.left is None:  # 只有右孩子
                ans.append(root.right.val)  # 右孩子是独生节点，记录它的值
            if root.right is None:  # 只有左孩子
                ans.append(root.left.val)  # 左孩子是独生节点，记录它的值
            dfs(root.left)  # 递归处理左子树
            dfs(root.right)  # 递归处理右子树

        ans = []  # 收集独生节点的值（在 dfs 之后定义，靠闭包被捕获）
        dfs(root)  # 从根开始遍历
        return ans  # 返回结果
