# 题目：993. 二叉树的堂兄弟节点（Cousins in Binary Tree）
# 思路：BFS 分层遍历，记录 x、y 各自的深度与父结点；深度相同且父结点不同即为堂兄弟。
# 时间复杂度：O(n)，每个结点入队出队各一次；空间复杂度：O(n)，队列最多保存一层结点。
# 下面 6 行是题目给出的二叉树结点定义，实际判题时由 LeetCode 提供。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def isCousins(self, root: Optional[TreeNode], x: int, y: int) -> bool:  # root：二叉树根；x、y：要找的两个结点值；返回二者是否为堂兄弟
        q = deque([(root, None)])  # 双端队列，元素是 (当前结点, 它的父结点)，根的父亲记为 None
        depth = 0  # depth 记录当前层深度
        p1 = p2 = None  # p1、p2 保存 x、y 的父结点
        d1 = d2 = None  # d1、d2 保存 x、y 所在深度
        while q:  # 队列非空就一层层往下遍历
            for _ in range(len(q)):  # 只处理当前这一层的结点数，保证同层 depth 一致
                node, parent = q.popleft()  # 取出队首结点及其父结点
                if node.val == x:  # 命中 x：记下父结点与深度
                    p1, d1 = parent, depth  # 一次赋两个变量，保证父结点与深度来自同一个结点
                elif node.val == y:  # 否则再看是不是 y
                    p2, d2 = parent, depth  # 同样是成对赋值
                if node.left:  # 左孩子存在才入队
                    q.append((node.left, node))  # 入队时把当前结点记为左孩子的父亲
                if node.right:  # 右孩子存在才入队
                    q.append((node.right, node))  # 入队时把当前结点记为右孩子的父亲
            depth += 1  # 本层处理完，深度加一
        return p1 != p2 and d1 == d2  # 堂兄弟：父结点不同且深度相同
