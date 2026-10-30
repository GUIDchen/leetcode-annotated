# 题目：2792. 计算足够大的节点数（Count Nodes That Are Great Enough）
# 思路：后序 dfs 返回「子树中前 k 小的值」的小根堆（存相反数模拟大根堆），堆大小为 k 且第 k 小值小于当前节点值时当前节点足够大。
# 时间复杂度：O(n * k log k)，每个节点都要合并左右候选集合；空间复杂度：O(n + 递归深度 * k)，递归栈与堆存储的开销。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def countGreatEnoughNodes(self, root: Optional[TreeNode], k: int) -> int:  # root：二叉树根节点；k：题目要求的排名 k
        def push(pq, x):  # 辅助函数：把 x 放入堆 pq，并维持堆中最多 k 个元素
            heappush(pq, x)  # 入堆
            if len(pq) > k:  # 元素个数超过 k 时
                heappop(pq)  # 弹出堆顶（存的是相反数，堆顶对应最大的原值），只保留最小的 k 个

        def dfs(root):  # dfs 返回子树中前 k 小的值；存相反数是为了用 Python 的小根堆模拟大根堆
            if root is None:  # 空节点没有值
                return []  # 返回空列表
            l, r = dfs(root.left), dfs(root.right)  # 递归求左右子树的候选集合
            for x in r:  # 把右子树的候选值逐个并入左集合
                push(l, x)  # 合并时同样只保留最小的 k 个
            if len(l) == k and -l[0] < root.val:  # 堆中恰好 k 个值时，堆顶的相反数就是第 k 小的值
                nonlocal ans  # 声明 ans 来自外层作用域，函数内需要修改它
                ans += 1  # 第 k 小值小于当前节点值，说明当前节点足够大
            push(l, -root.val)  # 把当前节点值（取相反数）也放入集合，上传给父节点
            return l  # 返回集合供父节点合并

        ans = 0  # 答案计数器
        dfs(root)  # 从根节点开始后序遍历
        return ans  # 返回足够大的节点数
