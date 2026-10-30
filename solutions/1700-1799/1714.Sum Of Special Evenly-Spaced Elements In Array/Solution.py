# 题目：1714. 数组中特殊等间距元素的和（Sum Of Special Evenly-Spaced Elements In Array）
# 思路：根号分治。预处理步长 1..sqrt(n) 的后缀和表；查询时小步长 O(1) 查表，大步长按步长切片求和。
# 时间复杂度：O(n·sqrt(n) + q·sqrt(n))；空间复杂度：O(n·sqrt(n))。
class Solution:
    def solve(self, nums: List[int], queries: List[List[int]]) -> List[int]:
        mod = 10**9 + 7  # 取模常数（题目要求对 1e9+7 取模）
        n = len(nums)  # 数组长度
        m = int(sqrt(n))  # 分块阈值：约等于 sqrt(n)，决定预处理哪些步长
        suf = [[0] * (n + 1) for _ in range(m + 1)]  # suf[i][j]：从 j 开始、步长为 i 的后缀和（这里先不取模，最后统一取模）
        for i in range(1, m + 1):  # 只预处理步长 1..m
            for j in range(n - 1, -1, -1):  # 从后往前递推
                suf[i][j] = suf[i][min(n, j + i)] + nums[j]  # 当前位置的值 + 后一个同余位置；min(n, j+i) 处理越界
        ans = []  # 存放每个查询的答案
        for x, y in queries:  # 逐个处理查询
            if y <= m:  # 步长较小，直接用预处理结果 O(1) 回答
                ans.append(suf[y][x] % mod)  # 预处理时未取模（避免递推中反复取模），这里再统一取模
            else:  # 步长较大，按步长切片求和，切片长度不超过 sqrt(n)
                ans.append(sum(nums[x::y]) % mod)  # nums[x::y] 取 x, x+y, ... 这些位置的和，再取模
        return ans  # 返回所有查询的答案
