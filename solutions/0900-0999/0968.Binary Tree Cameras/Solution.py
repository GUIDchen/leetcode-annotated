# 题目：968. 监控二叉树（Binary Tree Cameras）
# 思路：树形 DP。每个节点返回三元组 (a, b, c)：a=放摄像头、b=被覆盖但没放、c=未被覆盖三种状态下的最少摄像头数。
# 时间复杂度：O(n)，每个节点只算一次；空间复杂度：O(h)，递归栈深度等于树的高度。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def minCameraCover(self, root: Optional[TreeNode]) -> int:  # root 是根节点，返回覆盖整棵树所需的最少摄像头数量
        def dfs(root):  # 内部 DFS：返回以 root 为根的子树在三种状态下的最少摄像头数 (a, b, c)
            if root is None:  # 空节点：放摄像头无意义（用 inf 表示不可行），不算被覆盖也不算未被覆盖
                return inf, 0, 0  # 对应 {a=inf, b=0, c=0}
            la, lb, lc = dfs(root.left)  # 左子树三种状态
            ra, rb, rc = dfs(root.right)  # 右子树三种状态
            a = min(la, lb, lc) + min(ra, rb, rc) + 1  # 状态 a：本节点放摄像头可覆盖孩子，孩子三态任取最小值，再加自身 1 个
            b = min(la + rb, lb + ra, la + ra)  # 状态 b：本节点没放但被覆盖，覆盖只能来自一个孩子放摄像头，三种组合取最小
            c = lb + rb  # 状态 c：本节点未被覆盖，两个子节点都必须处于「被覆盖」状态
            return a, b, c  # 返回本节点的三种状态

        a, b, _ = dfs(root)  # 根节点没有父节点，只能取「放摄像头」或「被覆盖」两种状态
        return min(a, b)  # 取两者较小值作为答案
