# 题目：107. 二叉树的层序遍历 II（Binary Tree Level Order Traversal II）
# 思路：用 deque 做 BFS 逐层收集结点值，得到自顶向下的层序，最后用切片反转成自底向上。
# 时间复杂度：O(n)，每个结点进出队列一次；空间复杂度：O(n)，队列与结果列表。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def levelOrderBottom(self, root: Optional[TreeNode]) -> List[List[int]]:  # root 是树根，返回自底向上的层序遍历结果
        ans = []  # 结果列表：每个元素是某一层的值
        if root is None:  # 空树没有层可遍历
            return ans  # 直接返回空结果
        q = deque([root])  # 双端队列做 BFS，先把根放进去
        while q:  # 队列非空说明还有层没处理
            t = []  # 收集当前这一层的值
            for _ in range(len(q)):  # 先取本层结点数，循环这么多次就能把层分开
                node = q.popleft()  # 从队首取出结点，popleft 是 O(1)
                t.append(node.val)  # 记录当前结点值
                if node.left:  # 左孩子存在时
                    q.append(node.left)  # 左孩子入队，留到下一层
                if node.right:  # 右孩子存在时
                    q.append(node.right)  # 右孩子入队，留到下一层
            ans.append(t)  # 本层收集完毕，追加到结果
        return ans[::-1]  # 反转列表得到自底向上的顺序
