# 题目：2147. 分隔长廊的方案数（Number of Ways to Divide a Long Corridor）
# 思路：记忆化搜索 dfs(i, k)，i 是当前下标、k 是当前隔间已有座位数；k 满 2 时既可以不放隔板，也可以放隔板并把 k 归零。
# 时间复杂度：O(n)，共 3n 个状态且每个状态 O(1) 转移；空间复杂度：O(n)，缓存表与递归栈深度。
class Solution:  # LeetCode 约定的题解类
    def numberOfWays(self, corridor: str) -> int:  # corridor：只含 'S'（座位）与 'P'（植物）的长廊字符串
        @cache  # 记忆化装饰器：自动缓存 dfs 的返回值，避免重复计算
        def dfs(i: int, k: int) -> int:  # i：当前下标；k：当前隔间已累计的座位数
            if i >= len(corridor):  # 已经走到走廊末尾
                return int(k == 2)  # 恰好 2 个座位才算一种合法方案（True 转成 1，False 转成 0）
            k += int(corridor[i] == "S")  # 当前位置是座位就把计数加一（布尔值转成 0/1）
            if k > 2:  # 一个隔间超过 2 个座位，不合法
                return 0  # 该分支没有方案
            ans = dfs(i + 1, k)  # 选择不在此处放隔板，继续往后走
            if k == 2:  # 当前隔间正好 2 个座位，此处可以放一块隔板
                ans = (ans + dfs(i + 1, 0)) % mod  # 累加放隔板的方案，新隔间计数从 0 开始
            return ans  # 返回该状态的方案数

        mod = 10**9 + 7  # 结果需要对 1e9+7 取模
        ans = dfs(0, 0)  # 从下标 0、空隔间开始递归
        dfs.cache_clear()  # 清空缓存，避免多次调用同一实例时残留旧结果
        return ans  # 返回最终方案数
