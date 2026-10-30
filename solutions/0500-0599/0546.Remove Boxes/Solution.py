# 题目：546. 移除盒子（Remove Boxes）
# 思路：区间 DP + 记忆化搜索，dfs(i, j, k) 表示「区间 [i, j] 右侧还挂着 k 个与 boxes[j] 同色的盒子」时的最大得分；先把右端连续同色并进 k，再枚举区间内同色位置与之合并。
# 时间复杂度：O(n^4)，状态数 O(n^3)、每个状态枚举 O(n) 个合并点；空间复杂度：O(n^3)，缓存表大小。
class Solution:  # LeetCode 约定的题解类
    def removeBoxes(self, boxes: List[int]) -> int:  # boxes 是颜色序列，返回消除全部盒子能得到的最大得分
        @cache  # 用 @cache 做记忆化，避免同一状态被重复计算
        def dfs(i, j, k):  # i/j 是区间端点，k 是挂在右端的、与 boxes[j] 同色的盒子个数
            if i > j:  # 区间为空
                return 0  # 得分为 0
            while i < j and boxes[j] == boxes[j - 1]:  # 先把右端连续同色的盒子并入 k，减少状态数量
                j, k = j - 1, k + 1  # 右端点左移，同色计数加一
            ans = dfs(i, j - 1, 0) + (k + 1) * (k + 1)  # 方案一：立刻消掉右端这一组同色盒子，再处理左边
            for h in range(i, j):  # 方案二：枚举区间内与 boxes[j] 同色的位置 h
                if boxes[h] == boxes[j]:  # 只有颜色相同才有可能合并
                    ans = max(ans, dfs(h + 1, j - 1, 0) + dfs(i, h, k + 1))  # 先消掉 (h, j) 之间的部分，再把 h 与右端 k 个同色盒子一起处理
            return ans  # 返回该状态的最优解

        n = len(boxes)  # 盒子的数量 n
        ans = dfs(0, n - 1, 0)  # 从整个数组开始求解，右端没有额外同色盒子
        dfs.cache_clear()  # 清空缓存，避免多次调用之间互相污染
        return ans  # 返回最大得分
