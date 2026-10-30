# 题目：2415. 反转二叉树的奇数层（Reverse Odd Levels of Binary Tree）
# 思路：用队列做 BFS，当前队列恰好就是同一层的全部节点；层号为奇数时用双指针交换队列首尾节点的值，再把下一层节点依次入队。
# 时间复杂度：O(n)，每个节点只进出队列各一次；空间复杂度：O(n)，队列最多同时存放一层节点。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def reverseOddLevels(self, root: Optional[TreeNode]) -> Optional[TreeNode]:  # 返回反转奇数层后的树根（原地改值）
        q = deque([root])  # 双端队列作为 BFS 队列，初始只有根节点
        i = 0  # 当前层号，根节点算第 0 层
        while q:  # 队列非空就继续处理下一层
            if i & 1:  # 层号为奇数时才需要反转
                l, r = 0, len(q) - 1  # 双指针指向本层最左与最右的节点
                while l < r:  # 两端向中间收缩
                    q[l].val, q[r].val = q[r].val, q[l].val  # 交换两节点的值，实现该层反转
                    l, r = l + 1, r - 1  # 指针同时内移
            for _ in range(len(q)):  # len(q) 在循环开始前求值，因此本次只处理当前层
                node = q.popleft()  # 弹出队首节点
                if node.left:  # 有左孩子说明下面还有节点
                    q.append(node.left)  # 左孩子入队
                    q.append(node.right)  # 右孩子随之入队，保证层序从左到右
            i += 1  # 进入下一层
        return root  # 返回树根，结构不变、只是奇数层的值被反转
