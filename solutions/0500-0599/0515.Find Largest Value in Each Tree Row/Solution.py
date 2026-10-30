# 题目：515. 在每个树行中找最大值（Find Largest Value in Each Tree Row）
# 思路：BFS 逐层遍历，每层用一个变量维护最大值，处理完一层就把它加入答案列表。
# 时间复杂度：O(n)，每个节点进出队各一次；空间复杂度：O(n)，队列最多保存一层节点（答案列表另计）。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def largestValues(self, root: Optional[TreeNode]) -> List[int]:  # 返回每层最大值组成的列表
        ans = []  # 存放每一层的最大值
        if root is None:  # 空树直接返回空列表
            return ans  # 提前返回
        q = deque([root])  # BFS 队列，初始只有根节点
        while q:  # 队列非空表示还有层要处理
            x = -inf  # 本层最大值初值取负无穷，任何节点值都能更新它
            for _ in range(len(q)):  # 固定次数弹出，恰好处理完当前这一层
                node = q.popleft()  # 取出队首节点
                x = max(x, node.val)  # 刷新本层最大值
                if node.left:  # 左孩子存在才入队
                    q.append(node.left)  # 左孩子进入下一层
                if node.right:  # 右孩子存在才入队
                    q.append(node.right)  # 右孩子进入下一层
            ans.append(x)  # 记录本层最大值
        return ans  # 返回按层收集的结果
