# 题目：102. 二叉树的层序遍历（Binary Tree Level Order Traversal）
# 思路：BFS 分层。队列中保存待展开的节点，每轮先用 len(q) 固定本层节点数，弹完一层再收集下一层。
# 时间复杂度：O(n)，每个节点入队出队各一次；空间复杂度：O(w)，w 为最大层宽，即队列峰值。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def levelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:  # root：树根，返回自顶向下、每层自左向右的分层结果
        ans = []  # 答案列表：每个元素是某一层的值列表
        if root is None:  # 空树
            return ans  # 直接返回空答案
        q = deque([root])  # 双端队列作为 BFS 队列，先放入根节点
        while q:  # 队列非空，说明还有节点待展开
            t = []  # 收集当前这一层的节点值
            for _ in range(len(q)):  # 用当前队列长度锁定本层节点个数，循环中新增的节点属于下一层
                node = q.popleft()  # 从队首取出一个本层节点
                t.append(node.val)  # 记录它的值
                if node.left:  # 左孩子存在
                    q.append(node.left)  # 左孩子加入队尾，成为下一层节点
                if node.right:  # 右孩子存在
                    q.append(node.right)  # 右孩子随后入队，保证下一层仍然自左向右
            ans.append(t)  # 本层收集完毕，整层加入答案
        return ans  # 返回分层遍历结果
