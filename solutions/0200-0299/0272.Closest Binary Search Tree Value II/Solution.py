# 题目：272. 最接近的二叉搜索树值 II（Closest Binary Search Tree Value II）
# 思路：对 BST 做中序遍历得到递增序列，用双端队列维护当前最优的 k 个值；队列满时若新值不比队首更近，后面的值只会更远，直接剪枝。
# 时间复杂度：O(n)，每个结点访问一次；空间复杂度：O(k + h)，队列存 k 个值，递归栈深 h。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def closestKValues(self, root: TreeNode, target: float, k: int) -> List[int]:  # root：BST 根；target：目标值；k：需要返回的个数
        def dfs(root):  # 内层递归：中序遍历，维护保存最近 k 个值的队列 q
            if root is None:  # 空结点是递归边界
                return  # 直接返回上一层
            dfs(root.left)  # 先递归左子树（更小的值）
            if len(q) < k:  # 队列未满，直接加入
                q.append(root.val)  # 加入当前结点值
            else:  # 队列已满：与队首（最远的一个）比较
                if abs(root.val - target) >= abs(q[0] - target):  # 不比队首更近就剪枝返回（中序后面只会更远）
                    return  # 返回上一层
                q.popleft()  # 弹出最远的队首
                q.append(root.val)  # 加入更近的当前值
            dfs(root.right)  # 继续遍历右子树

        q = deque()  # 双端队列：左端出队、右端入队；dfs 定义在前，此处才创建，调用时已可见
        dfs(root)  # 从根开始中序遍历
        return list(q)  # 队列内容就是答案（中序递增且只保留 k 个）
