# 题目：103. 二叉树的锯齿形层序遍历（Binary Tree Zigzag Level Order Traversal）
# 思路：BFS 分层后按层号决定方向：奇数层原序输出，偶数层切片反转（t[::-1]），层号用 left ^= 1 翻转。
# 时间复杂度：O(n)，每个节点进出队一次，反转总代价线性；空间复杂度：O(w)，w 为最大层宽。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def zigzagLevelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:  # root：树根，返回锯齿形分层序列
        ans = []  # 预留答案变量（下一行若根为空就直接返回它）
        if root is None:  # 空树判断
            return ans  # 没有层可遍历，返回空答案
        q = deque([root])  # BFS 双端队列，初始放入根节点
        ans = []  # 正式的结果列表：每个元素是一层的值列表
        left = 1  # 方向标记：1 表示本层自左向右，0 表示自右向左
        while q:  # 队列非空说明还有层待处理
            t = []  # 暂存本层值，统一按自左向右收集
            for _ in range(len(q)):  # 先固定本层节点数，循环内新入队的节点属于下一层
                node = q.popleft()  # 弹出队首（本层最左未处理的节点）
                t.append(node.val)  # 记录节点值
                if node.left:  # 左孩子存在
                    q.append(node.left)  # 左孩子入队，供下一层处理
                if node.right:  # 右孩子存在
                    q.append(node.right)  # 右孩子入队，维持下一层自左向右的收集顺序
            ans.append(t if left else t[::-1])  # 方向为 1 时原序追加，否则用切片反转后再追加
            left ^= 1  # 0/1 翻转，切换下一层的输出方向
        return ans  # 返回锯齿形层序遍历结果
