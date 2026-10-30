# 题目：199. 二叉树的右视图（Binary Tree Right Side View）
# 思路：层序遍历（BFS）。每层先入右孩子再入左孩子，队首就是该层最右节点，取走队首值后再把整层出队。
# 时间复杂度：O(n)，每个节点只进出队列一次；空间复杂度：O(n)，双端队列最坏保存一整层节点。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def rightSideView(self, root: Optional[TreeNode]) -> List[int]:  # root：二叉树根节点；返回自上而下每层最右侧节点的值
        ans = []  # 收集每层最右节点的值
        if root is None:  # 空树没有任何可见节点
            return ans  # 直接返回空列表
        q = deque([root])  # 双端队列做 BFS，初始只有根节点
        while q:  # 队列非空说明还有一层未处理
            ans.append(q[0].val)  # 入队顺序是先右后左，所以队首正是本层最右节点，先记录它的值
            for _ in range(len(q)):  # 先用 len(q) 锁定本层节点数，保证一次处理完整的一层
                node = q.popleft()  # 弹出当前层的队首节点
                if node.right:  # 右孩子优先入队，下一层它就会排在队首
                    q.append(node.right)  # 把右孩子追加到队尾
                if node.left:  # 左孩子随后入队
                    q.append(node.left)  # 把左孩子追加到队尾
        return ans  # 返回每层最右侧的值
