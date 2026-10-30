# 题目：513. 找树左下角的值（Find Bottom Left Tree Value）
# 思路：BFS 逐层遍历，每层第一个出队的节点就是该行最左节点，逐层覆盖记录，最后一层记录的值就是答案。
# 时间复杂度：O(n)，每个节点进出队各一次；空间复杂度：O(n)，队列最多保存一层节点。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def findBottomLeftValue(self, root: Optional[TreeNode]) -> int:  # root 为根节点，返回最后一行最左边的值
        q = deque([root])  # 双端队列做 BFS，初始只有根节点
        ans = 0  # 记录每行最左值，最后一轮覆盖后即为答案
        while q:  # 队列非空表示还有层要遍历
            ans = q[0].val  # 队首必是本行最左节点，先记录它的值
            for _ in range(len(q)):  # 固定次数弹队首，正好处理完当前这一层
                node = q.popleft()  # 取出当前层的节点
                if node.left:  # 左孩子存在才入队
                    q.append(node.left)  # 左孩子加入下一层
                if node.right:  # 右孩子存在才入队
                    q.append(node.right)  # 右孩子加入下一层
        return ans  # 遍历到最后一层后 ans 就是答案
