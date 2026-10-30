# 题目：2458. 移除子树后的二叉树高度（Height of Binary Tree After Subtree Removal Queries）
# 思路：先用一次后序 DFS 自底向上求出每个节点的子树高度并缓存，再用一次 DFS 自顶向下把「祖先与其他分支贡献的最大深度」传给每个节点，得到删掉它之后的剩余高度。
# 时间复杂度：O(n + q)，n 是节点数、q 是查询数；空间复杂度：O(n)，字典与结果数组各存一份。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def treeQueries(self, root: Optional[TreeNode], queries: List[int]) -> List[int]:  # root：原树根节点；queries：要删除的节点值列表
        def f(root):  # 后序递归：求以 root 为根的子树高度
            if root is None:  # 空节点没有高度
                return 0  # 递归出口：空子树高度为 0
            l, r = f(root.left), f(root.right)  # 先递归求出左右子树的高度
            d[root] = 1 + max(l, r)  # 当前子树高度 = 1 + 左右较大者，并缓存进字典 d
            return d[root]  # 把当前子树高度返回给上一层

        def dfs(root, depth, rest):  # 自顶向下 DFS：depth 是父节点深度，rest 是祖先与其他分支给出的最大高度
            if root is None:  # 空节点不必继续
                return  # 递归出口
            depth += 1  # 当前节点深度 = 父节点深度 + 1
            res[root.val] = rest  # 删除当前节点后，剩余树高度只取决于当前路径之外的最大深度
            dfs(root.left, depth, max(rest, depth + d[root.right]))  # 进入左子树：候选高度取「祖先贡献」与「右兄弟子树提供的深度」
            dfs(root.right, depth, max(rest, depth + d[root.left]))  # 进入右子树：候选高度取「祖先贡献」与「左兄弟子树提供的深度」

        d = defaultdict(int)  # 字典：键是节点对象，值是它的子树高度；defaultdict 让缺失键默认返回 0
        f(root)  # 先算好整棵树的子树高度表
        res = [0] * (len(d) + 1)  # 答案表 res[v] 存删除值为 v 的节点后剩余树的高度，长度按节点数分配
        dfs(root, -1, 0)  # 从根开始自顶向下填表；传 -1 使根深度为 0
        return [res[v] for v in queries]  # 按查询顺序收集答案
