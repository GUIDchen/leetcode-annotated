# 题目：2471. 逐层排序二叉树所需的最少操作数目（Minimum Number of Operations to Sort a Binary Tree by Level）
# 核心思路：BFS 逐层取出节点值，把每层的值替换成「排序后的名次」得到 0..n-1 的排列，再用置换环求最少交换次数，各层结果相加。
# 时间复杂度：O(n·log n)，每层排序并把值映射成名次；空间复杂度：O(n)，队列与每层的临时数组。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def minimumOperations(self, root: Optional[TreeNode]) -> int:  # root 是二叉树根节点，返回使每一层都升序所需的最少交换次数
        def swap(arr, i, j):  # 辅助函数：交换同一层数组里的两个位置
            arr[i], arr[j] = arr[j], arr[i]  # Python 元组赋值，不需要临时变量

        def f(t):  # f：把一层节点值换成排序后的名次，再用置换环统计最少交换次数
            n = len(t)  # 这一层的节点个数
            m = {v: i for i, v in enumerate(sorted(t))}  # 值 → 排序后的名次
            for i in range(n):  # 逐位把节点值替换成名次
                t[i] = m[t[i]]  # 替换后 t 变成 0..n-1 的一个排列
            ans = 0  # 本层的最少交换次数（与外层 ans 同名，但作用域更小）
            for i in range(n):  # 逐个位置归位
                while t[i] != i:  # 当前位置不对就一直交换，直到归位
                    swap(t, i, t[i])  # 把 i 位置上的元素换到它该去的名次位置
                    ans += 1  # 一次交换记一次操作
            return ans  # 返回本层的最少交换次数

        q = deque([root])  # BFS 队列，初始只放根节点
        ans = 0  # 累计每一层需要的最少交换次数
        while q:  # 按层 BFS，直到所有节点都处理完
            t = []  # 收集当前这一层的所有节点值
            for _ in range(len(q)):  # range 先把本层节点数固定下来，循环只处理本层
                node = q.popleft()  # 取出队首节点
                t.append(node.val)  # 记录本层的一个节点值
                if node.left:  # 有左孩子就入队，作为下一层
                    q.append(node.left)  # 左孩子入队
                if node.right:  # 有右孩子就入队，作为下一层
                    q.append(node.right)  # 右孩子入队
            ans += f(t)  # 累加本层的最少交换次数
        return ans  # 返回整棵树所需的交换总次数
