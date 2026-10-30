# 题目：133. 克隆图（Clone Graph）
# 思路：DFS 深拷贝。用字典记录“原节点 → 克隆节点”，每到一个节点先建副本并登记，再递归克隆它的邻居，环也不会死循环。
# 时间复杂度：O(V + E)，每个点和每条边各处理一次；空间复杂度：O(V)，字典与递归栈。
# 说明：下面这段三引号内容是 LeetCode 题面预先给出的 Node 定义。
"""
# Definition for a Node.
class Node:
    def __init__(self, val = 0, neighbors = None):
        self.val = val
        self.neighbors = neighbors if neighbors is not None else []
"""

from typing import Optional  # 只为了给下面的类型标注用 Optional，判题器环境已隐式提供 typing


class Solution:  # LeetCode 约定的题解类
    def cloneGraph(self, node: Optional["Node"]) -> Optional["Node"]:  # 返回 node 的深拷贝；node 为 None 时也返回 None
        def dfs(node):  # 内层 DFS：克隆以 node 为根的这一块连通图并返回克隆后的起点
            if node is None:  # 空节点直接返回
                return None  # 空图对应 None
            if node in g:  # 这个节点已经克隆过了（环上的边会重复走到它）
                return g[node]  # 直接复用已有的副本，保证同一节点在结果里只有一个对象
            cloned = Node(node.val)  # 新建一个值相同的节点
            g[node] = cloned  # 先登记再递归，防止自环 / 环导致无限递归
            for nxt in node.neighbors:  # 遍历原节点的邻居列表
                cloned.neighbors.append(dfs(nxt))  # 递归克隆邻居并挂到副本的 neighbors 上
            return cloned  # 返回当前节点对应的副本

        g = defaultdict()  # 映射 原节点 → 克隆节点；defaultdict 缺省为 None，这里只当普通字典用
        return dfs(node)  # 从入口节点开始克隆整张连通图
