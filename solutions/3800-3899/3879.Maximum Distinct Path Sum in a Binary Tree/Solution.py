# 3879. 二叉树中的最大不同路径和 / Maximum Distinct Path Sum in a Binary Tree
# 核心思路：把二叉树建成无向图，从每个节点回溯搜索，保证路径上节点值互不相同，取最大和。
# 复杂度：时间 O(n^2)，空间 O(n)。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # 定义题解类
    def maxSum(self, root: Optional[TreeNode]) -> int:  # 返回节点值互不相同的最大路径和
        def dfs(node, p):  # 建图：把二叉树当成无向图
            if node is None:  # 空节点直接返回
                return  # 结束递归
            g[node].append(p)  # 记录父节点
            g[node].append(node.left)  # 记录左孩子
            g[node].append(node.right)  # 记录右孩子
            dfs(node.left, node)  # 递归处理左子树
            dfs(node.right, node)  # 递归处理右子树

        def dfs2(node):  # 回溯搜索：求以 node 为起点的最大不同路径和
            if node is None or node.val in vis:  # 空节点或该值已用过则不可继续
                return 0  # 此方向贡献为 0
            vis.add(node.val)  # 标记当前节点值已使用
            res = node.val  # 当前节点值先计入路径
            best = 0  # 记录最优子路径和
            for nxt in g[node]:  # 枚举所有邻居
                best = max(best, dfs2(nxt))  # 取各分支中的最大值
            vis.remove(node.val)  # 回溯：撤销当前节点值的标记
            res += best  # 加上最优子路径
            return res  # 返回以当前节点为起点的最大和

        g = defaultdict(list)  # 无向图邻接表
        dfs(root, None)  # 从根节点开始建图
        vis = set()  # 记录路径上已使用的节点值
        ans = -inf  # 答案初始化为负无穷
        for node in g:  # 枚举每个节点作为起点
            ans = max(ans, dfs2(node))  # 更新全局最大值
            vis.clear()  # 清空访问标记
        return ans  # 返回最大不同路径和
