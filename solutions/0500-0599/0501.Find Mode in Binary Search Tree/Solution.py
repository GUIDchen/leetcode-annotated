# 题目：501. 二叉搜索树中的众数（Find Mode in Binary Search Tree）
# 思路：对 BST 做中序遍历得到非递减序列，只用「前驱值」在线统计当前值的连续出现次数；超过历史最大值就替换答案，相等则追加。
# 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(n)，递归栈最坏 O(n)（结果列表另计）。
# 下面这段是 LeetCode 判题器提供的 TreeNode 定义，属于平台模板而非解题代码
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def findMode(self, root: TreeNode) -> List[int]:  # 返回 BST 中所有出现次数最多的值
        def dfs(root):  # 中序遍历的递归函数，顺带用闭包变量做在线统计
            if root is None:  # 空节点是递归出口
                return  # 直接返回，不再往下走
            nonlocal mx, prev, ans, cnt  # 声明要修改外层作用域的统计变量
            dfs(root.left)  # 先处理左子树（BST 中更小的值）
            cnt = cnt + 1 if prev == root.val else 1  # 与前驱值相同则次数加一，否则当前值从头计为 1
            if cnt > mx:  # 出现次数超过历史最大值
                ans = [root.val]  # 旧的众数全部失效，用当前值重新开始
                mx = cnt  # 更新历史最大次数
            elif cnt == mx:  # 次数与历史最大值相同，当前值也是众数
                ans.append(root.val)  # 把当前值追加到答案
            prev = root.val  # 记下当前值，作为下一个节点的前驱
            dfs(root.right)  # 最后处理右子树（BST 中更大的值）

        prev = None  # 中序遍历的前驱值，None 表示还没有前驱
        mx = cnt = 0  # mx 是最大出现次数，cnt 是当前值的连续出现次数，都从 0 开始
        ans = []  # 存放众数的列表
        dfs(root)  # 从根节点开始中序遍历
        return ans  # 返回统计结果
