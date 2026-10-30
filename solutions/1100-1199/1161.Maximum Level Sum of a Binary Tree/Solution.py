# 题目：1161. 最大层内元素和（Maximum Level Sum of a Binary Tree）
# 思路：BFS 逐层遍历二叉树，累计每层节点值之和，记录和最大的最小层号。
# 时间复杂度：O(n)，每个节点入队一次；空间复杂度：O(n)，队列最宽为最底层节点数。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def maxLevelSum(self, root: Optional[TreeNode]) -> int:  # 返回元素和最大的层号（从 1 开始，和相同取最小层号）
        q = deque([root])  # BFS 队列，初始只有根节点
        mx = -inf  # 历史最大层和，初始为负无穷
        i = 0  # 当前层号
        while q:  # 队列非空说明还有层
            i += 1  # 进入下一层，层号加一
            s = 0  # 当前层的元素和
            for _ in range(len(q)):  # 只处理当前层的节点，循环次数先固定
                node = q.popleft()  # 取出队首节点
                s += node.val  # 累加节点值
                if node.left:  # 有左孩子
                    q.append(node.left)  # 左孩子入队，留给下一层
                if node.right:  # 有右孩子
                    q.append(node.right)  # 右孩子入队
            if mx < s:  # 当前层和严格更大时才更新（相等保留更小层号）
                mx = s  # 更新最大层和
                ans = i  # 记录对应层号
        return ans  # 返回最大层和所在层号
