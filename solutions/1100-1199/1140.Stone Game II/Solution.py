# 题目：1140. 石子游戏 II（Stone Game II）
# 思路：@cache 记忆化博弈搜索：dfs(i,m) 返回从第 i 堆起、当前 M=m 时当前玩家的最优收获，值为剩余总和减去对手最优。
# 时间复杂度：O(n^3)；空间复杂度：O(n^2)，缓存表。
class Solution:  # LeetCode 约定的题解类
    def stoneGameII(self, piles: List[int]) -> int:  # piles 是石子堆，返回先手能拿到的最多石子数
        @cache  # 装饰器自动记忆化，同一 (i, m) 只计算一次
        def dfs(i, m):  # dfs(i, m)：从第 i 堆开始、当前 M=m 时当前玩家能拿到的最大值
            if m * 2 >= n - i:  # 一次能拿完剩余所有堆时，直接全拿
                return s[n] - s[i]  # 剩余区间和就是全部收获
            return max(  # 对所有可选取法取最大值：拿 x 堆后对手从 i+x 起以 max(m,x) 继续
                s[n] - s[i] - dfs(i + x, max(m, x)) for x in range(1, m << 1 | 1)  # 自己所得 = 剩余总和 - 对手最优结果（m<<1|1 即 2m+1，作 range 上界）
            )  # 取最大值的表达式结束

        n = len(piles)  # 注意 n、s 定义在 dfs 之后，靠闭包延迟绑定，调用时已就绪
        s = list(accumulate(piles, initial=0))  # 前缀和，initial=0 使 s[i] 表示前 i 堆之和
        return dfs(0, 1)  # 从第 0 堆、初始 M=1 开始求解
