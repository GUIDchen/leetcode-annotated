# 题目：2385. 感染二叉树需要的总时间（Amount of Time for Binary Tree to Be Infected）
# 核心思路：把二叉树转成无向图（父子双向加边），再从 start 节点出发做一次求「最远距离」的 DFS，步数就是感染全部节点所需的分钟数。
# 时间复杂度：O(n)，每个节点在两次 DFS 中各访问常数次；空间复杂度：O(n)，邻接表与递归栈均随节点数线性增长。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def amountOfTime(self, root: Optional[TreeNode], start: int) -> int:  # root 是二叉树根节点，start 是初始感染节点的值，返回感染整棵树所需分钟数
        def dfs(node: Optional[TreeNode], fa: Optional[TreeNode]):  # 第一个 DFS：按树的结构递归，把父子关系写成无向边
            if node is None:  # 空节点直接返回，作为递归出口
                return  # 什么都不做，结束当前递归分支
            if fa:  # fa 非空说明当前节点有父节点，需要建立双向连接
                g[node.val].append(fa.val)  # node 指向 fa 的边，使从子节点可以回到父节点
                g[fa.val].append(node.val)  # fa 指向 node 的边，使父子之间双向可达
            dfs(node.left, node)  # 递归左子树，把当前节点当作左孩子的父亲传入
            dfs(node.right, node)  # 递归右子树，把当前节点当作右孩子的父亲传入

        def dfs2(node: int, fa: int) -> int:  # 第二个 DFS：在无向图上从 node 出发求最远步数，fa 用来避免走回头路
            ans = 0  # ans 记录当前节点出发的最远距离，初始为 0
            for nxt in g[node]:  # 遍历与当前节点相邻的所有节点
                if nxt != fa:  # 跳过父节点，否则会在无向边上来回死循环
                    ans = max(ans, 1 + dfs2(nxt, node))  # 先走一步到 nxt，再递归求剩余距离，取所有分支中的最大值
            return ans  # 返回以当前节点为起点的最远距离

        g = defaultdict(list)  # 建图容器：节点值 -> 相邻节点值列表，默认空列表省去存在性判断
        dfs(root, None)  # 以根节点为起点、父节点为空开始建图
        return dfs2(start, -1)  # 从 start 出发求最远距离，父节点用 -1 占位（节点值不会是 -1）
