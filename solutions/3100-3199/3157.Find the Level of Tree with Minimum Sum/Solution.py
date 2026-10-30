# 题目：3157. 找到具有最小和的树的层数（Find the Level of Tree with Minimum Sum）
# 核心思路：用 deque 做 BFS，每轮固定弹出当前队列长度个节点即为同一层，累加层和并记录最小层号；严格小于才更新，保证和相同时取最小层。
# 时间复杂度：O(n)，每个节点只入队出队一次；空间复杂度：O(n)，队列最多保存最宽一层的节点。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def minimumLevel(self, root: Optional[TreeNode]) -> int:  # root：二叉树根节点，返回和最小的层号（从 1 开始）
        q = deque([root])  # 双端队列，初始只有根节点；popleft 是 O(1)
        ans = 0  # 答案层号，初始为 0
        level, s = 1, inf  # 层号从 1 开始；s 用正无穷作最小层和的初值
        while q:  # 队列非空就还有下一层要处理
            t = 0  # 本层节点值之和
            for _ in range(len(q)):  # range(len(q)) 在进入本层前就确定节点个数，保证只处理一层
                node = q.popleft()  # 弹出队首节点
                t += node.val  # 把节点值累加到层和
                if node.left:  # 存在左孩子时
                    q.append(node.left)  # 左孩子入队，等下一层处理
                if node.right:  # 存在右孩子时
                    q.append(node.right)  # 右孩子入队，等下一层处理
            if s > t:  # 严格小于才更新，保证和相同时取更小的层号
                s = t  # 更新最小层和
                ans = level  # 更新答案层号
            level += 1  # 层号加一，进入下一层
        return ans  # 返回和最小的层号
