# 题目：666. 路径总和 IV（Path Sum IV）
# 思路：三位数 num 按 num//10 与 num%10 拆成「深度+位置」和节点值存进字典，从根编码 11 开始 DFS，到叶子时累加整条路径和。
# 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(n)，字典与递归深度。
class Solution:  # LeetCode 约定的题解类
    def pathSum(self, nums: List[int]) -> int:  # nums 中每个三位数编码一个节点，返回所有根到叶子路径和的总和
        def dfs(node, t):  # node：当前节点编码；t：从根到当前节点（不含自身）的路径和
            if node not in mp:  # 该位置没有节点
                return  # 直接结束这一层递归
            t += mp[node]  # 把当前节点值累加进路径和
            d, p = divmod(node, 10)  # divmod 一次拆出深度 d 与层内位置 p
            l = (d + 1) * 10 + (p * 2) - 1  # 左孩子编码：深度加 1，位置 = 2p - 1
            r = l + 1  # 右孩子位置紧接左孩子
            nonlocal ans  # 声明 ans 来自外层函数，否则下面的 += 会把它当成新的局部变量
            if l not in mp and r not in mp:  # 左右孩子都不存在 → 当前是叶子节点
                ans += t  # 叶子：把整条路径和计入答案
                return  # 叶子无需继续递归
            dfs(l, t)  # 递归左子树
            dfs(r, t)  # 递归右子树

        ans = 0  # 答案初始化为 0
        mp = {num // 10: num % 10 for num in nums}  # 字典推导式：编码（num//10）→ 节点值（num%10）
        dfs(11, 0)  # 根节点编码为 11，路径和从 0 开始累加
        return ans  # 返回累加结果
