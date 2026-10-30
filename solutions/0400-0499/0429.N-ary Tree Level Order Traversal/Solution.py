# 题目：429. N 叉树的层序遍历（N-ary Tree Level Order Traversal）
# 思路：BFS 逐层处理，每次先固定当前队列长度（即本层节点数），一次弹出整层并把子节点入队，从而把每层结果单独成组。
# 时间复杂度：O(n)，每个节点进出队列各一次；空间复杂度：O(n)，队列最多同时存一层节点。
# 说明：下面是题目自带的 N 叉树 Node 定义（注释块，由判题器提供），仅作参考。
"""
# Definition for a Node.
class Node:
    def __init__(self, val=None, children=None):
        self.val = val
        self.children = children
"""


class Solution:  # LeetCode 题解类
    def levelOrder(self, root: 'Node') -> List[List[int]]:  # 返回按层分组后的节点值
        ans = []  # ans[k] 保存第 k 层的所有节点值
        if root is None:  # 空树
            return ans  # 直接返回空结果
        q = deque([root])  # BFS 队列，初始只有根节点
        while q:  # 只要还有节点没处理
            t = []  # 存放当前这一层的节点值
            for _ in range(len(q)):  # 先取出本层节点数，循环只处理这么多个
                root = q.popleft()  # 取出队首节点
                t.append(root.val)  # 记录该节点的值
                q.extend(root.children)  # 子节点入队，属于下一层
            ans.append(t)  # 把本层结果加入答案
        return ans  # 返回层序遍历结果
