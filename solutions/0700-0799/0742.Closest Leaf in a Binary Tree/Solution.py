# 题目：742. 二叉树最近的叶节点（Closest Leaf in a Binary Tree）
# 思路：把树看成无向图（父子之间双向连边），从值为 k 的节点出发做 BFS，第一次遇到的叶子就是离 k 最近的叶子。
# 时间复杂度：O(n)，每个节点在建图和 BFS 中各访问一次；空间复杂度：O(n)，邻接表、队列与访问集合都是 O(n)。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def findClosestLeaf(self, root: Optional[TreeNode], k: int) -> int:  # root：二叉树根节点；k：起点节点的值，返回离它最近的叶子节点值
        def dfs(root: Optional[TreeNode], fa: Optional[TreeNode]):  # 递归函数：把树转成无向图，fa 是当前节点的父节点
            if root:  # 空节点直接返回
                g[root].append(fa)  # 记录当前节点的父节点（根节点的父节点是 None）
                g[fa].append(root)  # 记录反向边，父节点也能走到当前节点，这样才能从 k 向上搜索
                dfs(root.left, root)  # 递归处理左子树
                dfs(root.right, root)  # 递归处理右子树

        g = defaultdict(list)  # 邻接表：节点 → 邻居列表；defaultdict 让未出现的键自动得到空列表
        dfs(root, None)  # 从根节点开始建图
        q = deque(node for node in g if node and node.val == k)  # 把所有值为 k 的节点作为 BFS 起点（题目保证只有一个）
        vis = set(q)  # 已访问集合，初始包含所有起点，防止重复入队
        while 1:  # BFS 循环：按距离从近到远逐层扩展
            node = q.popleft()  # 取出队首节点
            if node:  # None 是父节点的虚拟占位，直接忽略
                if node.left == node.right:  # 左右孩子同时为空 ⇔ 叶子节点
                    return node.val  # BFS 保证第一次遇到的叶子离 k 最近，直接返回它的值
                for nxt in g[node]:  # 遍历这个节点的所有邻居
                    if nxt not in vis:  # 未访问过才加入队列，避免走回头路
                        vis.add(nxt)  # 标记为已访问
                        q.append(nxt)  # 邻居入队，等待下一层扩展
