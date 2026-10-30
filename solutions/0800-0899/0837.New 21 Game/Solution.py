# 题目：837. 新 21 点（New 21 Game）
# 思路：记 f(i) 为当前分数 i 时最终不超过 n 的概率。i≥k 时停止，答案直接是 0/1；i=k-1 时抽一次必然停止，可用闭式公式；其余情况用前缀和递推 f(i)=f(i+1)+(f(i+1)-f(i+maxPts+1))/maxPts，并做记忆化。
# 时间复杂度：O(k)，每个分数状态只算一次；空间复杂度：O(k)，记忆化缓存与递归栈。
class Solution:  # LeetCode 约定的题解类
    def new21Game(self, n: int, k: int, maxPts: int) -> float:  # n 为允许的最大得分，k 为停止阈值，maxPts 为每次可抽的最大点数；返回停止时得分不超过 n 的概率
        @cache  # 记忆化装饰器：同一个分数 i 的答案只计算一次
        def dfs(i: int) -> float:  # 当前分数为 i 时，最终得分不超过 n 的概率
            if i >= k:  # 分数已经达到停止阈值 k
                return int(i <= n)  # 此时不超过 n 返回 1，否则返回 0
            if i == k - 1:  # i == k-1 时再抽一次必然停止，可以不走递归直接算
                return min(n - k + 1, maxPts) / maxPts  # 在 k..k+maxPts-1 上均匀取值，其中落在 ≤n 的比例就是答案
            return dfs(i + 1) + (dfs(i + 1) - dfs(i + maxPts + 1)) / maxPts  # 前缀和递推：f(i) = f(i+1) + (f(i+1) - f(i+maxPts+1)) / maxPts

        return dfs(0)  # 从初始分数 0 开始计算
